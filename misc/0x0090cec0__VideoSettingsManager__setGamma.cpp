//FUNC_NAME: VideoSettingsManager::setGamma
void __thiscall VideoSettingsManager::setGamma(float gamma)
{
    // Clamp gamma to valid range (global min/max constants)
    float clampedGamma = gamma;
    float minGamma = DAT_00d5f378; // Minimum gamma value
    float maxGamma = DAT_00e445a0; // Maximum gamma value
    if (gamma <= minGamma) {
        clampedGamma = minGamma;
    } else if (maxGamma <= gamma) {
        clampedGamma = maxGamma;
    }

    // Store clamped gamma at offset +0x2C
    *(float *)(this + 0x2C) = clampedGamma;

    // Set dirty flag at offset +0x30
    *(uint8_t *)(this + 0x30) = 1;

    // Update the configuration system with the new gamma value
    FUN_0069c010("Window.Gamma", clampedGamma);

    // Stack manipulation (likely debug/allocator hook) - not relevant to logic
    int *stackPtr = (int *)(DAT_01206880 + 0x14);
    *(undefined ***)*stackPtr = &PTR_LAB_00e549f0;
    *stackPtr = *stackPtr + 4;

    // Unused locals (likely artifacts from decompilation)
    // float local_4 = (float)*(int *)(this + 0x38) * _DAT_00d83544;
    // undefined4 local_8 = _DAT_00d5780c;
    // float local_c = clampedGamma;
    // FUN_0049c430(&local_c, 0x10, 0x10); // Possibly a memcpy or debug call
}