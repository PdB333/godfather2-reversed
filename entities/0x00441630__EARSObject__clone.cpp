// FUNC_NAME: EARSObject::clone
void __thiscall EARSObject::clone(EARSObject* prototype, int flags) {
    EARSObject* original = prototype;
    // +0x00: vtable pointer, +0x08: virtual method at offset 8 (likely "preClone" or "allocate")
    (*(void (__thiscall**)(EARSObject*))(*prototype + 8))(prototype);

    int allocHandle;
    if (flags == 0) {
        allocHandle = 0;
    } else {
        allocHandle = FUN_004265d0(flags, original); // allocate memory, using prototype as type info
    }

    EARSObject* newObject = (EARSObject*)FUN_00441810(original, allocHandle); // placement construct or assign
    // +0x08: backlink to original prototype
    newObject->field_8 = original;
    (*(void (__thiscall**)(EARSObject*))(*prototype + 8))(); // second call to same vfunc (no args, possibly erroneous)

    if (flags != 0) {
        allocHandle = FUN_004265d0(flags, newObject->field_8); // re-allocate for some sub-object
        newObject->field_C = allocHandle;
        // +0x04: virtual method at offset 4 (likely "setup" or "attach")
        (*(void (__thiscall**)(EARSObject*, int, int))(*prototype + 4))(prototype, flags, 0);
        // +0x0C: virtual method at offset 0xC (likely "finishClone")
        (*(void (__thiscall**)(EARSObject*))(*prototype + 0xC))();
        return;
    }
    newObject->field_C = 0;
    // +0x0C: virtual method at offset 0xC (likely "finishClone")
    (*(void (__thiscall**)(EARSObject*))(*prototype + 0xC))();
}