// FUNC_NAME: EARSBase::~EARSBase
void __thiscall EARSBase::~EARSBase(EARSBase *this) {
    int *deferredFreeBuffer; // pointer to current position in global deallocation list
    int ptr1; // first owned pointer at +0x18
    int ptr2; // second owned pointer at +0x1C

    // Set vtable to the most derived class (this class's vtable)
    this->vtable = (void **)&PTR_FUN_00e37798;

    ptr1 = this->field_0x18;
    if (ptr1 != 0) {
        // Use global memory manager (DAT_012068e8) to schedule deferred free
        // +0x14 points to a buffer where deallocation records are appended
        deferredFreeBuffer = *(int **)(gMemoryManager + 0x14);
        *(void **)deferredFreeBuffer = (void *)&PTR_LAB_01124ba8; // marker for deferred free
        deferredFreeBuffer++;
        *deferredFreeBuffer = (int)ptr1;                         // pointer to free
        deferredFreeBuffer++;
        *(int **)(gMemoryManager + 0x14) = deferredFreeBuffer;   // update buffer pointer
        this->field_0x18 = 0;                                    // clear owned pointer
    }

    ptr2 = this->field_0x1C;
    if (ptr2 != 0) {
        deferredFreeBuffer = *(int **)(gMemoryManager + 0x14);
        *(void **)deferredFreeBuffer = (void *)&PTR_LAB_01124ba8;
        deferredFreeBuffer++;
        *deferredFreeBuffer = (int)ptr2;
        deferredFreeBuffer++;
        *(int **)(gMemoryManager + 0x14) = deferredFreeBuffer;
        this->field_0x1C = 0;
    }

    // Change vtable to base class vtable (after own destructor logic)
    this->vtable = (void **)&PTR_LAB_00e37304;
}