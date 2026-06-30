// FUNC_NAME: Entity::computeSmoothedMotion
// Function address: 0x0053f390
// Role: Computes a smoothed motion vector (position/velocity) using iterative interpolation and damping.
// The function takes an output pointer (likely passed in EDI) and writes a 4-component vector.
// It uses a random factor for noise and integrates over multiple steps based on a count.

void __fastcall Entity::computeSmoothedMotion(int param_1, int this, int param_3, float* outVec)
{
    // param_1 is unused (likely ECX, but not used in this function)
    // this is the main object pointer (EDX)
    // param_3 is a pointer to a time/step structure (stack)
    // outVec is the output vector (passed in EDI)

    float* statePtr = *(float**)(this + 8); // +0x8: pointer to physics state (e.g., velocity/position)
    if (statePtr == nullptr) {
        outVec[0] = 0.0f;
        outVec[1] = 0.0f;
        outVec[2] = 0.0f;
        outVec[3] = 0.0f;
        return;
    }

    int* timerPtr = *(int**)(this + 0xb8); // +0xb8: pointer to a timer/counter structure
    if (*(int*)(timerPtr + 0xc) < 1) { // +0x0c: step count or elapsed frames
        // If no steps, compute a random noise vector scaled by state values
        float random = (float)FUN_009efd10(); // returns random float in [0,1]
        random = -random; // negate
        outVec[0] = (float)((float10)statePtr[0x10] * (float10)random); // statePtr+0x10 = some component
        outVec[1] = (float)((float10)statePtr[0x14] * (float10)random);
        outVec[2] = (float)((float10)statePtr[0x18] * (float10)random);
        outVec[3] = (float)((float10)statePtr[0x1c] * (float10)random);
        return;
    }

    // Main integration path
    float timeStep = *(float*)(param_3 + 8); // +0x08: time step (dt)
    float scale = *(float*)(statePtr + 0x2c0); // +0x2c0: scale factor (e.g., stiffness)
    float dtScale = timeStep * scale;

    float baseX = statePtr[0x10] * dtScale; // statePtr+0x10: base velocity/position X
    float baseY = statePtr[0x14] * dtScale; // Y
    float baseZ = statePtr[0x18] * dtScale; // Z
    float baseW = statePtr[0x1c] * dtScale; // W (scalar)

    int iterationCount = *(int*)(statePtr + 0x2b4); // +0x2b4: number of iterations
    float currentX = 0.0f;
    float currentY = 0.0f;
    float currentZ = 0.0f;
    float currentW = 0.0f;

    float prevX = 0.0f;
    float prevY = 0.0f;
    float prevZ = 0.0f;
    float prevW = 0.0f;

    float baseOffset = *(float*)(this + 0x1a4); // +0x1a4: some base offset (e.g., target position)
    float offsetY = baseOffset + baseY; // combine with base

    float interpFactor = *(float*)(statePtr + 0x1d0); // +0x1d0: interpolation factor (e.g., damping)

    // Local accumulators for the iterative loop
    float localX = 0.0f, localY = 0.0f, localZ = 0.0f, localW = 0.0f;

    // Process iterations in chunks of 4
    int i = 0;
    if (iterationCount > 3) {
        int chunkCount = (iterationCount - 4) / 4 + 1;
        i = chunkCount * 4;
        do {
            // Perform 4 steps of interpolation per chunk
            float tempX = interpFactor * (baseX - prevX) + prevX;
            float tempY = interpFactor * (offsetY - currentY) + currentY;
            offsetY = ((offsetY - currentY) + tempY + baseY) - tempY;
            float tempZ = interpFactor * (baseZ - localZ) + localZ;
            prevX = ((baseX - prevX) + tempX + baseX) - tempX;
            baseX = ((baseZ - localZ) + tempZ + baseZ) - tempZ;
            float tempW = interpFactor * (baseW - localW) + localW;
            baseW = ((baseW - localW) + tempW + baseW) - tempW;

            float newY = offsetY * interpFactor + tempY;
            float newZ = baseX * interpFactor + tempZ;
            float newX = interpFactor * prevX + tempX;
            float newW = baseW * interpFactor + tempW;

            baseX = (baseX + newZ + baseZ) - newZ;
            prevX = (prevX + newX + baseX) - newX;
            baseW = (baseW + newW + baseW) - newW;
            currentY = (offsetY + newY + baseY) - newY;

            float nextX = interpFactor * prevX + newX;
            float nextY = currentY * interpFactor + newY;
            float nextZ = baseX * interpFactor + newZ;
            float nextW = baseW * interpFactor + newW;

            chunkCount--;
            offsetY = (prevX + nextX + baseX) - nextX;
            float tempY2 = (currentY + nextY + baseY) - nextY;
            float tempZ2 = (baseX + nextZ + baseZ) - nextZ;
            baseX = (baseW + nextW + baseW) - nextW;

            prevX = interpFactor * offsetY + nextX;
            currentY = tempY2 * interpFactor + nextY;
            localZ = tempZ2 * interpFactor + nextZ;
            localW = baseX * interpFactor + nextW;

            baseW = baseX + localW + baseW;
            baseX = offsetY + prevX + baseX;
            baseZ = tempZ2 + localZ + baseZ;
            offsetY = tempY2 + currentY + baseY;

            localX = prevX;
            localY = currentY;
        } while (chunkCount != 0);
    }

    // Process remaining iterations
    if (i < iterationCount) {
        float factor = *(float*)(statePtr + 0x1d0);
        int remaining = iterationCount - i;
        do {
            remaining--;
            baseW = baseW - localW;
            baseX = baseX - localX;
            localX = factor * baseX + localX;
            offsetY = offsetY - localY;
            localY = offsetY * factor + localY;
            baseZ = baseZ - localZ;
            localZ = baseZ * factor + localZ;
            localW = baseW * factor + localW;
            baseW = baseW + localW + baseW;
            baseX = baseX + localX + baseX;
            offsetY = offsetY + localY + baseY;
            baseZ = baseZ + localZ + baseZ;
        } while (remaining != 0);
    }

    // Final scaling with damping and random noise
    float random = (float)FUN_009efd10();
    float damping = *(float*)(statePtr + 0x1e0); // +0x1e0: damping factor
    float timeFactor = *(float*)(param_3 + 0xc); // +0x0c: another time-related factor
    float scaleFactor = *(float*)(statePtr + 0x2c0);
    float finalScale = 1.0f - damping * timeFactor * scaleFactor * random; // DAT_00e44564 = 1.0f

    outVec[0] = finalScale * localX;
    outVec[1] = localY * finalScale;
    outVec[2] = localZ * finalScale;
    outVec[3] = finalScale * localW;
}