// FUNC_NAME: SomeManager::destroy
void __fastcall SomeManager::destroy(void* this_ptr) {
    int i;
    int j;
    int k;
    int elementPtr;
    SomeManager* self = (SomeManager*)this_ptr;

    // Set vtable pointers for multiple inheritance (three bases)
    self->vtable1 = &PTR_FUN_00d5d724; // primary vtable
    self->vtable2 = &PTR_LAB_00d5d714; // second base at offset 0x3C
    self->vtable3 = &PTR_LAB_00d5d710; // third base at offset 0x48

    // Clean up global singletons (likely Debug subsystem)
    FUN_004086d0(&DAT_0112a534);
    FUN_00408310(&DAT_0112a534);
    FUN_004086d0(&DAT_0112db74);

    // Destroy used elements (indices 0..m_nCount-1)
    if (self->m_nCount > 0) {
        k = 0;
        j = 0;
        do {
            // Each element is 0x30 bytes; child pointer at offset 0x10
            elementPtr = *(int*)(self->m_pElements + 0x10 + k);
            if (elementPtr != 0) {
                FUN_005e6820(elementPtr, 0, 0);  // releaseResource
                FUN_006a5690(elementPtr, 0, 0);  // stopResource
                FUN_005e6660(elementPtr);        // destroyResource
            }
            j = j + 1;
            k = k + 0x30;
        } while (j < self->m_nCount);
    }

    // Reset vtable pointers for all slots (indices 0..m_nCapacity-1)
    i = self->m_nCapacity - 1;
    if (i >= 0) {
        k = i * 0x30;
        do {
            *(void***)(self->m_pElements + 0x24 + k) = &PTR_LAB_00e2f0c0; // clear sub-object vtable
            i = i - 1;
            k = k - 0x30;
        } while (i >= 0);
    }

    // Free the element array
    if (self->m_pElements != 0) {
        FUN_009c8f10(self->m_pElements); // operator delete[]
    }

    // Final global cleanup
    FUN_0046c640();
}

// Offset layout for SomeManager:
// +0x00: vtable1
// +0x3C: vtable2
// +0x48: vtable3
// +0x54: m_nCount (int)
// +0x58: m_pElements (byte*)
// +0x5C: m_nCapacity (int)
//
// Element (0x30 bytes):
// +0x00: ? (not used here)
// +0x10: child pointer (0 if empty)
// +0x24: sub-object vtable