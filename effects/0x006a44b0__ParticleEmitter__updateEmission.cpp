// FUNC_NAME: ParticleEmitter::updateEmission
// Address: 0x006a44b0
// Purpose: Updates particle emission for a ParticleEmitter class. Handles both stopping emission (when flag at +0x50 is set) and emitting new particles based on timing and position. Uses random number generation for spread.

// Dependencies:
// - FUN_006a42c0: Creates a new particle instance, returns handle.
// - FUN_006a4310: Submits or updates particle (likely adds to render queue).
// - FUN_005e6580: Sets position of a particle object (via handle).
// - FUN_005e67c0: Sets visibility/active flag of a particle object (parameter: handle, flag).
// - Global random state: DAT_010c2678, DAT_012054b4 (index), DAT_00d5d70c (scale factor)
// - Random helper calls: FUN_00b99fcb(), FUN_00b99e20() (probably seed adjustments)

void __thiscall ParticleEmitter::updateEmission(int* outCount, void* context, int context2, float* position, float spread)
{
    // context is expected to be a pointer to a struct with int at offset +0x08 (e.g., distance threshold)
    int distanceThreshold = *(int*)((char*)context + 8);

    // Check if emitter is in "stopping" mode
    if (mFlags50 != 0) {
        // Clear "stop requested" sub-flag if set
        if (mFlags52 != 0) {
            mFlags52 = 0;
        }
        // For each emitter element, if it has a valid position (any of first 4 floats non-zero) and has not been deactivated (byte at +0x2c == 0), remove it
        for (int i = 0; i < mElementCount; i++) {
            ParticleEmitterElement* element = &mElements[i];
            // Check if position vector is non-zero (any component non-zero)
            if (element->mPosition[0] != 0.0f || element->mPosition[1] != 0.0f || 
                element->mPosition[2] != 0.0f || element->mPosition[3] != 0.0f) {
                // +0x2c: mActive flag (byte). If zero, the element should be cleaned up.
                if (element->mActive == 0) {
                    FUN_006a4310(i, context, context2);
                }
            }
        }
        mFlags50 = 0; // Clear stopping flag
        return;
    }

    // Emission mode: iterate over elements and emit new particles if conditions allow
    for (int i = 0; i < mElementCount; i++) {
        ParticleEmitterElement* element = &mElements[i];
        // Check if element has a valid position (non-zero vector) and is ready to emit (mEmitReady != 0) and no current particle (mParticleHandle == 0)
        if ((element->mPosition[0] != 0.0f || element->mPosition[1] != 0.0f || 
             element->mPosition[2] != 0.0f || element->mPosition[3] != 0.0f) &&
            element->mEmitReady != 0 && element->mParticleHandle == 0) {
            
            int emittime = element->mTimestamp1;  // +0x14
            int lifeTime = element->mTimestamp2;   // +0x18
            
            // Check if current distance threshold is within the emission window
            if (lifeTime < emittime) {
                if (distanceThreshold < emittime) {
                    // Inside emission window: proceed
                } else {
                    goto emit_particle;
                }
            } else if (emittime <= distanceThreshold) {
                // Further check: if distanceThreshold <= lifetime, emit
                if (distanceThreshold <= lifeTime) {
emit_particle:
                    // Reset emission flags
                    element->mEmitReady = 0;
                    element->mActive = 0;

                    // Create new particle instance
                    int newParticle = FUN_006a42c0(element);
                    element->mParticleHandle = newParticle;

                    if (newParticle != 0) {
                        (*outCount)++;

                        // Generate random value from table
                        // DAT_010c2678 & DAT_012054b4 index into a table, scaled by DAT_00d5d70c
                        float randomVal = *(float*)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4) * DAT_00d5d70c;
                        DAT_012054b4 = DAT_012054b4 + 1; // Advance index

                        // Use random value for position offset. Functions likely adjust RNG state.
                        double dRand = (double)randomVal;
                        FUN_00b99fcb();
                        float randXZ = (float)dRand; 

                        dRand = (double)randomVal;
                        FUN_00b99e20();

                        // Compute new position: spread * random on X and Z, Y unchanged
                        float newPos[3];
                        newPos[0] = (float)dRand * spread + position[0];
                        newPos[1] = position[1]; // Y remains at base position
                        newPos[2] = randXZ * spread + position[2];

                        // Set particle position and enable it
                        FUN_005e6580(element->mParticleHandle, newPos);
                        FUN_005e67c0(element->mParticleHandle, 0x80); // Activate/visible flag
                    }
                    // Submit particle for rendering/update
                    FUN_006a4310(i, context, context2);
                }
            }
        }
    }
}