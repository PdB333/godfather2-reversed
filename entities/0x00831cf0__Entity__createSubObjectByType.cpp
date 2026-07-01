// FUNC_NAME: Entity::createSubObjectByType
void __thiscall Entity::createSubObjectByType(Entity* this, undefined4 param2) {
    // this+0x24 is the type field (0, 1, or other)
    if (*(int*)((char*)this + 0x24) == 0) {
        // Type 0: construct a specific sub-object
        undefined4 result = FUN_0082e6b0(local_80, param2); // construct into buffer local_80
        FUN_0082a8f0(result); // initialize
        local_80[0] = &PTR_FUN_00d7343c; // set vtable
        if (local_24[0] != 0) {
            FUN_004daf90(local_24); // cleanup if flag set
        }
    } else if (*(int*)((char*)this + 0x24) == 1) {
        // Type 1: construct a different sub-object
        undefined4 result = FUN_00824a50(local_160, param2, 0);
        FUN_0082a8f0(result);
        local_160[0] = &PTR_FUN_00d7343c;
        if (local_104[0] != 0) {
            FUN_004daf90(local_104);
            return;
        }
    } else {
        // Default type: construct another sub-object
        undefined4 result = FUN_00824a50(local_f0, param2, 0);
        FUN_0082a8f0(result);
        local_f0[0] = &PTR_FUN_00d7343c;
        if (local_94[0] != 0) {
            FUN_004daf90(local_94);
            return;
        }
    }
    return;
}