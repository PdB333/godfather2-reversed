// FUNC_NAME: VehicleBrain::computeSteeringVelocity
void __thiscall VehicleBrain::computeSteeringVelocity(int thisPtr, float *outVelocity)
{
    int *componentPtr;
    float velocityScale;
    undefined8 targetDir64;
    float targetDirZ;
    int singletonPtr;
    float stackDirX;
    float stackDirY;
    float stackDirZ;
    float stackDirW;
    undefined4 stackPad;

    // Extract target direction from some component (likely AI or input target)
    // +0x8c and +0x90 are fields: +0x8c might be a matrix, +0x90 a speed scalar
    getTargetDirection(thisPtr + 0x8c, (float *)(thisPtr + 0x90));

    // Access a sub-object via pointer chain: thisPtr+0x50 -> +0x70
    componentPtr = *(int **)(*(int *)(thisPtr + 0x50) + 0x70);
    if (componentPtr != (int *)0x0) {
        // Adjust pointer to base of the component (offset -0x48)
        componentPtr = componentPtr - 0x12; // equivalent to (int *)((int)componentPtr - 0x48)
        singletonPtr = getSingleton(); // returns pointer to some global manager
        // Copy target position/direction from manager's data (+0x30)
        *(undefined8 *)outVelocity = *(undefined8 *)(singletonPtr + 0x30);
        outVelocity[2] = *(float *)(singletonPtr + 0x38);

        // Call virtual function on the component (offset 0x4c) to transform target into local space
        (**(code **)(*componentPtr + 0x4c))((int)&stackDirX + 4); // passes address of stack variable

        // Now stackDirX/Y/Z hold local target direction
        stackDirX = *(float *)((int)&stackDirX + 4); // due to weird CONCAT44, but this is approximate
        uint64_t temp = targetDir64;
        stackDirY = *(float *)((int)&temp + 4);
        stackDirZ = targetDirZ;

        // Check if target direction is nearly zero
        if (stackDirX * stackDirX + stackDirY * stackDirY + stackDirZ * stackDirZ < gTargetThreshold) {
            // Use a fallback direction from the manager (+0x20)
            singletonPtr = getSingleton();
            targetDir64 = *(undefined8 *)(singletonPtr + 0x20);
            stackDirZ = *(float *)(singletonPtr + 0x28);
            stackDirX = (float)((ulonglong)targetDir64 >> 0x20);
            stackDirY = (float)targetDir64;
        }

        // Normalize the direction vector
        normalizeVector(&stackDirY, &stackDirY); // normalize (stackDirX, stackDirY, stackDirZ)

        velocityScale = *(float *)(thisPtr + 0x90); // speed from earlier
        // Combine with velocity from target direction
        outVelocity[1] = stackDirY * velocityScale + outVelocity[1];
        outVelocity[2] = outVelocity[2] + stackDirZ * velocityScale;

        // Blend with additional component: use gBlendFactor (likely gravity or terrain adaptation)
        float blendFactor = gBlendFactor; // 0x00e44564
        outVelocity[0] = *outVelocity + stackDirX * velocityScale;
        outVelocity[0] = *outVelocity + stackDirX * (blendFactor - stackDirZ); // adjust by up direction
        outVelocity[1] = stackDirY * stackDirX + outVelocity[1]; // reinterpretation? Actually stackDirX used again
        outVelocity[2] = outVelocity[2] + stackDirX * stackDirX; // likely another cross term
        return;
    }
    // No component: zero velocity
    *outVelocity = 0.0f;
    outVelocity[1] = 0.0f;
    outVelocity[2] = 0.0f;
}