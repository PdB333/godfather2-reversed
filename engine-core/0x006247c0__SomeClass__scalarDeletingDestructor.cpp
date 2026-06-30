// FUNC_NAME: SomeClass::scalarDeletingDestructor
undefined4 * __thiscall SomeClass::scalarDeletingDestructor(SomeClass *this, byte deletingFlag)
{
    int *subObjectPtr;
    SomeClass *returnedThis;

    // Set vtable pointer to base class vtable (in case of virtual destructor chain)
    this->vtable = (SomeClassVTable *)&PTR_LAB_00e414e0;  // +0x00

    // Release a sub-object (likely a reference counted structure)
    // param_1[2] is a pointer at offset +0x08 in this object
    subObjectPtr = (int *)sub_00621530(this->field_0x08);  // FUN_00621530

    // Decrement a short reference counter at offset 0x12 in the sub-object
    *(short *)((char *)subObjectPtr + 0x12) -= 1;

    // If the deleting flag is set, call operator delete via a global allocator
    if ((deletingFlag & 1) != 0) {
        // DAT_012234ac is a pointer to an allocator (e.g., global memory manager)
        // (**(code **)(**(int **)(DAT_012234ac + 4) + 4)) is a delete function pointer
        // Call allocator's delete with (this, 0) – size parameter 0 indicates unknown size?
        ((void (*)(SomeClass *, int))*(*(int **)(*(int *)DAT_012234ac + 4) + 4))(this, 0);
    }

    return this;  // Return the pointer (common in some destructor conventions)
}