#include "Arduino.h"
#include "arm.h"
#include <math.h>
#include "AccelStepper.h"

#define PRIMARY_DIR 17
#define SECONDARY_DIR 18
#define TURRET_DIR 21

#define PRIMARY_STEP 16
#define SECONDARY_STEP 5
#define TURRET_STEP 19

#define ARM_LENGTH 30.0

#define DRIVER_INTERFACE AccelStepper::DRIVER

AccelStepper STEPPER_P(DRIVER_INTERFACE, PRIMARY_STEP, PRIMARY_DIR);
AccelStepper STEPPER_S(DRIVER_INTERFACE, SECONDARY_STEP, SECONDARY_DIR);
AccelStepper STEPPER_T(DRIVER_INTERFACE, TURRET_STEP, TURRET_DIR);

const float ratio1 = 4;
const float ratio2 = 30.0 / 12.0;

void Arm::setup() {
    pinMode(PRIMARY_DIR, OUTPUT);
    pinMode(SECONDARY_DIR, OUTPUT);
    pinMode(TURRET_DIR, OUTPUT);

    pinMode(PRIMARY_STEP, OUTPUT);
    pinMode(SECONDARY_STEP, OUTPUT);
    pinMode(TURRET_STEP, OUTPUT);

    STEPPER_P.setMaxSpeed(500);
    STEPPER_P.setAcceleration(200);
    STEPPER_S.setMaxSpeed(500);
    STEPPER_S.setAcceleration(200);
    STEPPER_T.setMaxSpeed(500);
    STEPPER_T.setAcceleration(200);

    gripper.attach(GRIPPER_PIN);
    gripper.write(GRIPPER_OPEN);
    gripping = false;
}

void Arm::goTo(const float rho, const float phi, const float r) {
    this->targetRho = rho;
    this->targetPhi = phi;
    this->targetR = r;

    float primaryAngle = acos(r / (2.0 * ARM_LENGTH)) + rho / 2.0;
    float secondaryAngle = acos(r / (2.0 * ARM_LENGTH)) - rho / 2.0;
    float turretAngle = phi;

    this->targetPosPrimary = static_cast<int>(primaryAngle / 360.0 * 200.0);
    this->targetPosSecondary = static_cast<int>(secondaryAngle / 360.0 * 200.0);
    this->targetPosTurret = static_cast<int>(turretAngle / 360.0 * 200.0);

    STEPPER_P.moveTo(targetPosPrimary * ratio1);
    STEPPER_S.moveTo(targetPosSecondary * ratio2);
    STEPPER_T.moveTo(targetPosTurret * ratio2);
}

void Arm::relativeMove(const float drho, const float dphi, const float dr) {
    float primaryAngle = acos(dr / (2.0 * ARM_LENGTH)) + drho / 2.0;
    float secondaryAngle = acos(dr / (2.0 * ARM_LENGTH)) - drho / 2.0;
    float turretAngle = dphi;

    this->targetPosPrimary = static_cast<int>(primaryAngle / 360.0 * 200.0);
    this->targetPosSecondary = static_cast<int>(secondaryAngle / 360.0 * 200.0);
    this->targetPosTurret = static_cast<int>(turretAngle / 360.0 * 200.0);

    STEPPER_P.moveTo(STEPPER_P.currentPosition() + targetPosPrimary * ratio1);
    STEPPER_S.moveTo(STEPPER_S.currentPosition() + targetPosSecondary * ratio2);
    STEPPER_T.moveTo(STEPPER_T.currentPosition() + targetPosTurret * ratio2);
}

bool Arm::hasArrived() {
    return STEPPER_P.distanceToGo() == 0
        && STEPPER_S.distanceToGo() == 0
        && STEPPER_T.distanceToGo() == 0;
}

void Arm::update() {
    STEPPER_P.run();
    STEPPER_S.run();
    STEPPER_T.run();
}

void Arm::grip() {
    gripper.write(GRIPPER_CLOSED);
    gripping = true;
}

void Arm::release() {
    gripper.write(GRIPPER_OPEN);
    gripping = false;
}

void Arm::pause() {
    STEPPER_P.disableOutputs();
    STEPPER_S.disableOutputs();
    STEPPER_T.disableOutputs();
}

void Arm::unpause() {
    STEPPER_P.enableOutputs();
    STEPPER_S.enableOutputs();
    STEPPER_T.enableOutputs();
}
