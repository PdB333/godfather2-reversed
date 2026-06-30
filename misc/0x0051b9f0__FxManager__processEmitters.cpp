// FUNC_NAME: FxManager::processEmitters
// Function address: 0x0051b9f0
// This function iterates over a list of effect emitters, checks conditions,
// and calls a processing function for each active emitter.

void FxManager::processEmitters(void* param2, float deltaTime) {
    // Check global flags: if bitmask 0x20300000 is set, skip all
    if ((*(uint32_t*)((uint8_t*)this + 0x0C) & 0x20300000) != 0) {
        return;
    }

    // Get a scaling factor from global variable multiplied by a field from a transform array
    float scaleFactor = *(float*)(*(int*)((uint8_t*)this + 0x10) + 0x20) * _DAT_00e44878;

    int count = *(int16_t*)((uint8_t*)this + 0x80); // number of emitters
    int index = 0;
    // Offset into the transform array (stride 0x24)
    int transformOffset = 0;

    // Emitter array starts at +0xF0, each entry is 20 bytes (5 uint32s)
    uint32_t* emitterEntry = (uint32_t*)((uint8_t*)this + 0xF0);

    while (index < count) {
        // piVar1 = object pointer from emitter entry
        int* objectPtr = (int*)emitterEntry[1];
        if (objectPtr != nullptr &&
            // Check emitter flags: bit 26 (0x4000000) must be clear
            (*emitterEntry & 0x4000000) == 0 &&
            // Access a per-thread global and check a status flag
            (*(uint32_t*)(objectPtr[4] + *(int*)(*(int*)(__readfsdword(0x2C)) + 8)) & 0x20000000) == 0 &&
            // Emitter flags: bit 21 (0x200000) must be clear
            (*emitterEntry & 0x200000) == 0 &&
            // Data pointer byte at +0xC must be even (bit0 clear)
            ((~*(uint8_t*)(emitterEntry[2] + 0xC) & 1) != 0) &&
            // Call a virtual function on the object (at vtable+0xC) – returns non-zero
            ((char (*)())(*(uint32_t*)(*objectPtr) + 0xC))() != '\0')
        {
            // Retrieve additional data
            uint32_t emitterFlags = *emitterEntry;
            uint32_t statusFromObject = *(uint32_t*)(objectPtr[4] + *(int*)(*(int*)(__readfsdword(0x2C)) + 8));
            int16_t objectInt16 = (int16_t)objectPtr[3]; // short from object
            int transformedShort = (int)(int16_t)objectPtr[3]; // sign-extended

            // Compute combined flags
            uint32_t combinedFlags =
                (statusFromObject >> 8 & 0x40000) |
                (transformedShort + ((uint32_t)emitterFlags >> 2 & 0x700)) |
                ((uint32_t)emitterFlags >> 1 & 0x1000) |
                (emitterFlags & 0x120000);

            // Position from transform array (stride 0x24) plus deltaTime
            float position = *(float*)((uint8_t*)objectPtr[3] /* Actually using iVar2? Wait, careful */);
            // Actually the code uses iVar2 which is from this->+0x10, and local_1c index.
            // Let's correctly access the float array:
            // float* pTransforms = *(float**)((uint8_t*)this + 0x10);
            // position = pTransforms[transformOffset/4 + 0x10]? No, stride 0x24 implies 9 floats.
            // We'll just use the computed offset.
            float pos = *(float*)(*(int*)((uint8_t*)this + 0x10) + transformOffset + 0x40) + deltaTime;

            // Call pre-processing function (maybe push state)
            FUN_00533c90();

            // Call main processing function
            FUN_0051b930(param2, /* output from previous call? */, combinedFlags, pos, (int)(*(int16_t*)((uint8_t*)objectPtr + 0x0E)));
        }

        index++;
        transformOffset += 0x24; // stride to next transform entry
        emitterEntry += 5; // each emitter entry is 20 bytes (5 uint32s)
    }
}