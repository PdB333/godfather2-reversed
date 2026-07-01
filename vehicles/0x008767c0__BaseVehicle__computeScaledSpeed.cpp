// FUNC_NAME: BaseVehicle::computeScaledSpeed
void __thiscall BaseVehicle::computeScaledSpeed(int this, int param2, float* outScaled, float* outBase)
{
    float baseValue = (float)FUN_00875220(this, param2); // Get base speed/force value
    *outBase = baseValue;

    float globalMaxSpeed = _DAT_00d5780c; // Global max speed limit
    float globalMinSpeed = DAT_00d5ccf8; // Global min speed limit

    // Access vehicle data at offset 0x380 (likely m_pVehicleData or m_pPhysicsConfig)
    int* vehicleDataPtr = *(int**)(this + 0x380);
    float vehicleMaxSpeed = *(float*)(vehicleDataPtr + 2); // +8 bytes from vehicleDataPtr (offset 8)

    float scaledValue = (globalMaxSpeed / vehicleMaxSpeed) * baseValue;
    *outScaled = scaledValue;

    // Clamp scaled value between global min and max
    if (globalMaxSpeed < scaledValue) {
        *outScaled = globalMaxSpeed;
        return;
    }
    if (scaledValue < globalMinSpeed) {
        *outScaled = globalMinSpeed;
        return;
    }
    // Otherwise keep the computed value (already assigned)
}