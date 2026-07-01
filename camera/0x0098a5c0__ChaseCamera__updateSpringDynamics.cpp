// FUNC_NAME: ChaseCamera::updateSpringDynamics
void __thiscall ChaseCamera::updateSpringDynamics(int thisPtr, float* outForce, float* outError, float* outVelocity)
{
    // Read spring state from this object
    float currentPositionZ = *(float*)(thisPtr + 0x4c);   // current z position
    float targetZ           = *(float*)(thisPtr + 0x50);   // target z position
    float currentPositionX = *(float*)(thisPtr + 0x44);   // current x position
    float targetX           = *(float*)(thisPtr + 0x48);   // target x position
    int integer1            = *(int*)(thisPtr + 0x2c);    // some counter (e.g., frame index)
    int integer2            = *(int*)(thisPtr + 0x30);    // some base value
    float springFactor      = *(float*)(thisPtr + 0x90);  // spring constant or damping factor

    // Initialize a small array for a random seed or state
    int seed[3] = {0, 0, 0};
    FUN_0098a350(seed, 1);  // likely initRandomState or setSeed

    // Compute noise or perturbation using the spring factor and the difference of integers
    float noise = (float)FUN_0098a2a0(*(int*)&springFactor, seed, 0, integer1 - integer2);

    // Time step derived from global constant and difference in target/current positions
    float timeStep = _DAT_00d5780c / (targetZ - targetX);

    // Output spring force (noise divided by position difference)
    *outForce = noise / (currentPositionZ - currentPositionX);

    // Output error term (target‑current minus spring factor, scaled by global and time step)
    *outError = ((targetZ - targetX) - springFactor) * _DAT_00d5c458 * timeStep;

    // Output velocity term (spring factor times time step)
    *outVelocity = springFactor * timeStep;

    // Cleanup if the seed array was dynamically allocated (decompiler shows an uninitialized function pointer,
    // likely an oversight; this is the standard EARS memory‑free pattern)
    if (seed[0] != 0) {
        // (*cleanupFuncPtr)(seed[0]);  // cleanup function pointer is not captured by Ghidra
    }
}