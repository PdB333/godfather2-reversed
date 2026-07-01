// FUNC_NAME: GameDataManager::applyConfigurationPreset
void __fastcall GameDataManager::applyConfigurationPreset(int this) {
    int iVar1;
    int iVar2;
    undefined *puVar3;
    int iVar4;
    undefined4 uStack_21c; // uninitialized in decompiled output
    undefined *local_218;
    undefined *local_214;
    undefined1 auStack_210[524]; // buffer for element retrieval

    // Choose configuration data based on flag at +0x1c0 (bit 0)
    puVar3 = &DAT_00e54038; // default data pointer
    local_214 = &DAT_00e54024;
    local_218 = &DAT_00e54038;
    if ((*(byte*)(this + 0x1c0) & 1) != 0) {
        // Alternate configuration when flag is set
        local_218 = &DAT_00e54060;
        puVar3 = &DAT_00e54060;
        local_214 = &DAT_00e5404c;
    }

    iVar1 = FUN_005466a0(); // returns some manager singleton (likely EARS::InputDeviceManager or similar)
    if (iVar1 != 0) {
        iVar1 = *(int*)(iVar1 + 0x10); // offset 0x10: pointer to a container/array
        *(undefined**)(iVar1 + 8) = local_214; // store pointer at +8 of that container

        if (*(int*)(iVar1 + 0xc) == 10) { // container has 10 slots
            iVar4 = 0;
            iVar2 = (**(code**)(*(int*)(iVar1 + 0x10) + 4))(); // vtable call: getCount()
            puVar3 = local_218; // restore after call
            if (0 < iVar2) {
                do {
                    // vtable call: getElement(index, buffer) -> returns pointer to element
                    iVar2 = (**(code**)(*(int*)(iVar1 + 0x10) + 0x14))(iVar4, auStack_210);
                    *(undefined4*)(iVar2 + 8) = uStack_21c; // copy value to element's offset +8
                    iVar4 = iVar4 + 1;
                    iVar2 = (**(code**)(*(int*)(iVar1 + 0x10) + 4))(); // re-query count
                } while (iVar4 < iVar2);
            }
        }
    }

    // Apply the selected configuration to a series of sub-objects at fixed offsets
    // Offsets: 0x128, 0x12c (300), 0x130, 0x134, 0x138, 0x13c, 0x140, 0x144
    // Each non-zero pointer +0x10 points to a structure with a vtable; offset +0x8 is set to puVar3
    if (*(int*)(this + 0x128) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x128) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 300) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 300) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 0x130) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x130) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 0x134) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x134) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 0x138) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x138) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 0x13c) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x13c) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 0x140) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x140) + 0x10) + 8) = puVar3;
    }
    if (*(int*)(this + 0x144) != 0) {
        *(undefined**)(*(int*)(*(int*)(this + 0x144) + 0x10) + 8) = puVar3;
    }
}