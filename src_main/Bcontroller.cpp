#include "Bcontroller.h"
#include <ps4Controller.h>
#include "arm.h"

BluetoothController::BluetoothController() {
    commandSent = true;
    armMode = false;
    LastLJoyStickX = 0;
    LastLJoyStickY = 0;
    LastRJoyStickX = 0;
    LastRJoyStickY = 0;
}

void BluetoothController::connect() {
    ps4.begin("00:1f:e2:a0:04:32");
    ps4.attachOnConnect(onConnect);
    ps4.attachOnDisconnect(onDisconnect);
    ps4.attach(onEvent);
}

void BluetoothController::onConnect() {
}

void BluetoothController::onDisconnect() {
}

void BluetoothController::onEvent() {
    BC.handleEvent();
}

void BluetoothController::handleEvent() {
    if (ps4.event.button_down.cross) {
        armMode = !armMode;
    }
    if (ps4.event.button_down.triangle) {
        if (arm.hasArrived()) {
            static bool gripped = false;
            gripped = !gripped;
            if (gripped) arm.grip();
            else arm.release();
        }
    }

    if (ps4.L2()) {
        arm.relativeMove(500, 0, 0);
    }
    if (ps4.R2()) {
        arm.relativeMove(-500, 0, 0);
    }
    if (ps4.Left()) {
        arm.relativeMove(0, -10.0, 0);
    }
    if (ps4.Right()) {
        arm.relativeMove(0, 10.0, 0);
    }
    if (ps4.Up()) {
        arm.relativeMove(0, 0, 10);
    }
    if (ps4.Down()) {
        arm.relativeMove(0, 0, -10);
    }

    int currentLStickX = ps4.LStickX();
    int currentLStickY = ps4.LStickY();
    int currentRStickX = ps4.RStickX();
    int currentRStickY = ps4.RStickY();

    if (abs(currentLStickX - LastLJoyStickX) > 0 || abs(currentLStickY - LastLJoyStickY) > 0) {
        int LprocessedX = (abs(currentLStickX) < 30) ? 0 : currentLStickX;
        int LprocessedY = (abs(currentLStickY) < 30) ? 0 : currentLStickY;

        if (LastLJoyStickX != LprocessedX || LastLJoyStickY != LprocessedY) {
            LastLJoyStickX = LprocessedX;
            LastLJoyStickY = LprocessedY;
            commandSent = false;
        }
    }

    if (abs(currentRStickX - LastRJoyStickX) > 0 || abs(currentRStickY - LastRJoyStickY) > 0) {
        int RprocessedX = (abs(currentRStickX) < 30) ? 0 : currentRStickX;
        int RprocessedY = (abs(currentRStickY) < 30) ? 0 : currentRStickY;

        if (LastRJoyStickX != RprocessedX || LastRJoyStickY != RprocessedY) {
            LastRJoyStickX = RprocessedX;
            LastRJoyStickY = RprocessedY;
            commandSent = false;
        }
    }
}

void BluetoothController::setErrorState() {
    ps4.setLed(250, 0, 0);
    ps4.sendToController();
}

void BluetoothController::setNormalState() {
    ps4.setLed(0, 250, 0);
    ps4.sendToController();
}

void BluetoothController::setObjectDetectedState() {
    ps4.setLed(250, 250, 0);
    ps4.sendToController();
}
