// FUNC_NAME: attachObjectToParent

void attachObjectToParent(void* obj, int arg)
{
    int* objAsInt = (int*)obj;
    void* parent;

    // vtable+8: returns a parent structure pointer
    parent = (*(void* (__thiscall**)(void*))(*(int*)obj + 8))(obj);

    // Determine a handle based on arg
    int handle;
    if (arg == 0) {
        handle = 0;
    } else {
        handle = FUN_004265d0(arg, obj);
    }

    // Store handle in parent structure
    FUN_004cf4e0(obj, handle);

    // Store object pointer at parent+0x8
    *(void**)((int)parent + 8) = obj;

    // Call vtable+8 again (no arguments – likely a different overload or side effect)
    (*(void (__thiscall**)(void))(*(int*)obj + 8))();

    if (arg != 0) {
        // Recalculate handle using the stored pointer
        handle = FUN_004265d0(arg, *(void**)((int)parent + 8));
        *(int*)((int)parent + 0xc) = handle;

        // vtable+4: set child reference
        (*(void (__thiscall**)(void*, int, int))(*(int*)obj + 4))(obj, arg, 0);

        // vtable+12: finalize
        (*(void (__thiscall**)(void))(*(int*)obj + 12))();
    } else {
        *(int*)((int)parent + 0xc) = 0;

        // vtable+12: finalize
        (*(void (__thiscall**)(void))(*(int*)obj + 12))();
    }
}