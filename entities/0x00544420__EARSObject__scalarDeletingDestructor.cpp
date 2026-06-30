// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Address: 0x00544420
undefined4 __thiscall EARSObject::scalarDeletingDestructor(EARSObject* this, byte deleteFlag)
{
    // Call the actual destructor body (cleanup logic)
    FUN_00544450();

    // If the delete flag (bit 0) is set, deallocate the object
    if ((deleteFlag & 1) != 0) {
        // Global pointer at DAT_01223410 + 0x2d4 points to a memory manager vtable
        // Offset +4 in that table is the scalar deallocation function
        (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
    }

    return (undefined4)this;
}