// FUNC_NAME: VehicleBrain::computeThrottleInput
float VehicleBrain::computeThrottleInput()
{
    // +0xe8: pointer to velocity provider (e.g., physics body)
    // Get vtable pointer from sub-object (offset adjusted by -0x48)
    int* vtablePtr;
    if (*(int*)(this + 0xe8) == 0) {
        vtablePtr = (int*)0x0;
    } else {
        vtablePtr = (int*)(*(int*)(this + 0xe8) - 0x48);
    }

    // Virtual function at vtable+0x4c: get a vector (e.g., getVelocity)
    // Outputs three floats on stack: localVec[0], localVec[1], localVec[2]
    float localVec[3];
    (**(code**)(*vtablePtr + 0x4c))(&localVec);

    // Compute magnitude of the vector (speed)
    float speed = sqrt(localVec[0]*localVec[0] + localVec[1]*localVec[1] + localVec[2]*localVec[2]);

    float interpolatedOutput;
    // Constants from globals:
    // DAT_0112a6ec = minSpeedThreshold
    // _DAT_00e50e68 = maxSpeedThreshold
    // DAT_00e50e64 = output when speed <= min
    // DAT_00e50e60 = output when speed >= max
    if (speed <= g_minSpeedThreshold) {
        interpolatedOutput = g_minOutputValue;
    } else if (speed >= g_maxSpeedThreshold) {
        interpolatedOutput = g_maxOutputValue;
    } else {
        // FUN_006c91c0 performs linear interpolation
        interpolatedOutput = linearInterpolate(speed, g_minSpeedThreshold, g_maxSpeedThreshold, g_minOutputValue, g_maxOutputValue);
    }

    // Blend with stored input (+0x2c4) and scale by global weights
    // DAT_00d58cbc = weightA
    // DAT_00d5efd0 = weightB
    return interpolatedOutput * g_weightA + *(float*)(this + 0x2c4) * g_weightB;
}