// FUNC_NAME: VFXManager::spawnParticleEffect
void __thiscall VFXManager::spawnParticleEffect(void *this, uint effectID, vec3_t *position, EffectExtraData *extraData) {
    int *coords;
    int x, y, z, w;
    uint *defaultData;
    uint templateData[16];
    EffectInitData initData;
    uint64_t extraParam; // 8 bytes
    uint extraParam2; // 4 bytes
    int newInstance; // output from createEffect

    // Get the effect origin coordinates (likely from some lookup based on ID)
    coords = (int *)getEffectCoordinates(effectID, position, 0);
    x = coords[0];
    y = coords[1];
    z = coords[2];
    w = coords[3]; // extra component (could be rotation or scale)

    if ((x != 0) || (y != 0) || (z != 0) || (w != 0)) {
        // Load the default particle template data (16 uint32s)
        defaultData = (uint *)getDefaultParticleTemplate();
        for (int i = 0; i < 16; i++) {
            templateData[i] = defaultData[i];
        }

        // Read the extra data pointer (assume it's a struct with 12 bytes)
        extraParam = *(uint64_t *)extraData;                // first 8 bytes
        extraParam2 = *(uint32_t *)((char *)extraData + 8); // next 4 bytes

        // Build the effect initialization data from template and extra data
        buildEffectInitData(&initData, templateData);
        initData.param1 = extraParam;   // embed into init data
        initData.param2 = extraParam2;

        // Get a global effect slot (virtual function on some manager at this+0xf8)
        uint effectSlot = (*(code **)(**(int **)((char *)this + 0xf8) + 0x58))(0, 0, 0xffffffff, 0);

        // Create the effect instance
        newInstance = createEffectInstance(&newInstance, &x, &initData, effectSlot);
        if (newInstance != 0) {
            *(int *)(newInstance + 8) = 0; // clear some field
        }
    }
}