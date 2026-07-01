// FUNC_NAME: BaseVehicle::computeDriveForce
float __thiscall BaseVehicle::computeDriveForce(float inputThrottle, VehiclePhysicsData* vehicleData, float deltaTime, float* outLateralForce) {
    float engineForce = *(float*)((int)vehicleData + 0x100); // max engine torque
    float gearRatio = *(float*)((int)vehicleData + 0x10c);   // gearing/scaling factor

    // Reverse throttle adjustment
    if (inputThrottle < 0.0f) {
        engineForce *= DAT_00e445a0;  // reverse force multiplier
    }

    float driveForce = engineForce * inputThrottle;

    // Check handbrake and onGround flags (+0x5e2, +0x5e0 are likely bools)
    if ((*(char*)(this + 0x5e2) == '\0') && (*(char*)(this + 0x5e0) == '\0')) {
        driveForce = 0.0f;  // no drive if handbrake or not grounded
    }

    // Add slope compensation (+0xe4 is gravity/ incline correction)
    driveForce += *(float*)((int)vehicleData + 0xe4);

    // Compute acceleration : (driveForce - resistance) * dt
    float resistance = *(float*)((int)vehicleData + 0xe8);  // aerodynamic/rolling resistance
    float acceleration = (driveForce - resistance) * deltaTime;

    // Compute lateral force (spring-damper like)
    float dampingStart = *(float*)((int)vehicleData + 0xec);
    float dampingEnd = *(float*)((int)vehicleData + 0xf0);
    float lateralDamping = dampingStart - (dampingStart - dampingEnd) * deltaTime;
    *outLateralForce = lateralDamping * gearRatio;

    // If braking/not grounded, nullify outputs
    if ((*(char*)(this + 0x5e2) == '\0') && (*(char*)(this + 0x5e0) == '\0')) {
        acceleration = 0.0f;
        *outLateralForce = 0.0f;
    }

    // Return final torque = (driveForce - acceleration) * gearRatio
    return ((float)driveForce - (float)acceleration) * (float)gearRatio;
}