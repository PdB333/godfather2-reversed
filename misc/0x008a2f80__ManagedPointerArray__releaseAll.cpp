// FUNC_NAME: ManagedPointerArray::releaseAll
void __fastcall ManagedPointerArray::releaseAll() {
    // Releases all 20 pointers stored in the array (indices 0-19)
    // Callee (FUN_008b5c70) likely decrements ref count or frees the pointer

    // Unroll first 8 indices for performance
    releasePointer(m_pointers[0]);
    releasePointer(m_pointers[1]);
    releasePointer(m_pointers[2]);
    releasePointer(m_pointers[3]);
    releasePointer(m_pointers[4]);
    releasePointer(m_pointers[5]);
    releasePointer(m_pointers[6]);
    releasePointer(m_pointers[7]);

    // Release remaining 12 pointers in a loop
    for (int i = 8; i < 20; ++i) {
        releasePointer(m_pointers[i]);
    }
}