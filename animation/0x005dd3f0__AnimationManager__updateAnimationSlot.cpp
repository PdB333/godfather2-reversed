// FUNC_NAME: AnimationManager::updateAnimationSlot
void __thiscall AnimationManager::updateAnimationSlot(AnimationManager* this, void* pEntity)
{
    // unaff_ESI = this (AnimationManager)
    // unaff_EDI = pEntity (some entity with animation state)
    struct AnimationSlot {
        int field_0;      // +0x00: slot ID or state
        int field_4;      // +0x04: unknown
        int field_12;     // +0x0C: ? (piVar1[-3])
        int field_16;     // +0x10: anim hash part ? (piVar1[-2])
        int field_20;     // +0x14: anim hash part ? (piVar1[-1])
        int field_24;     // +0x18: anim hash part ? (piVar1[0])
        int field_28;     // +0x1C: anim hash part ? (piVar1[1])
        uint8_t flag_34;  // +0x22: transition flag? (byte at piVar1+10)
        int field_68;     // +0x44: timing or something (piVar1[0xb])
    };

    int* pSlotArray = nullptr;
    int slotCount = 0;

    if ((*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1C)) == 0) {
        // Normal blending: search for matching slot in first array (offset +0x18)
        int* piVar = reinterpret_cast<int*>(reinterpret_cast<char*>(pEntity) + 0x18);
        for (uint idx = 0; idx < 5; ++idx) {
            // Check conditions: slot id not -1, and all four anim identifiers match
            if ((piVar[-3] != -1) &&
                (piVar[-2] == *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x20)) &&
                (piVar[-1] == *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x24)) &&
                (*piVar  == *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x28)) &&
                (piVar[1] == *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2C)) ) {
                // Found matching slot
                char* bytePtr = reinterpret_cast<char*>(piVar) + 10; // offset +0x22 from base
                if (*bytePtr == '\0') {
                    // Already active, no transition needed
                    return 1; // success
                }
                // Mark as active, update timing fields
                *bytePtr = '\0';
                piVar[-5] = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10);
                piVar[-6] = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x0C);
                piVar[0xb] = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x34);
                return 1;
            }
            piVar += 0x1A; // 0x1A ints = 0x68 bytes per slot
        }
        // No matching slot found, look for an empty slot in second array (offset +0x0C)
        piVar = reinterpret_cast<int*>(reinterpret_cast<char*>(pEntity) + 0x0C);
        for (uint idx = 0; idx < 5; ++idx) {
            if (*piVar == -1) break;
            piVar += 0x1A;
        }
        if (idx < 5) {
            // Found empty slot, start a new blend
            FUN_005dd0d0(1.0f, 96000); // possibly start blend/transition
        }
    } else {
        // Other mode: use global defaults or custom values from entity
        float floatParam = reinterpret_cast<float*>(DAT_00e2b1a4)[0]; // global default
        int intParam = 96000;
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(pEntity) + 0x214) != -1) {
            floatParam = *reinterpret_cast<float*>(reinterpret_cast<char*>(pEntity) + 0x240);
            intParam   = *reinterpret_cast<int*>(reinterpret_cast<char*>(pEntity) + 0x254);
        }
        FUN_005dd0d0(floatParam, intParam);
        // Update entity's own parameter storage
        if ((*reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 4)) >= 0.0f) {
            *reinterpret_cast<float*>(reinterpret_cast<char*>(pEntity) + 0x27C) = 
                *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 4);
        }
        if ((*reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 8)) >= 0.0f) {
            *reinterpret_cast<float*>(reinterpret_cast<char*>(pEntity) + 0x280) = 
                *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 8);
        }
    }
    return 1;
}