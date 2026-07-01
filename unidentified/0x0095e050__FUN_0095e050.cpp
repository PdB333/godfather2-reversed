// FUNC_NAME: SomeClass::~SomeClass (scalar deleting destructor)

int* __thiscall SomeClass::~SomeClass(int* this, byte deleteFlag)
{
    // Clean up sub-object at offset +0x10 (second member pointer)
    if (this[4] != 0) {
        // Call destructor function stored at offset +0x1C
        ((void (__thiscall*)(int*))this[7])((int*)this[4]);
    }
    // Clean up sub-object at offset +0x00 (first member pointer)
    if (this[0] != 0) {
        // Call destructor function stored at offset +0x0C
        ((void (__thiscall*)(int*))this[3])((int*)this[0]);
    }
    // If deleteFlag indicates memory should be freed (bit 0 set)
    if ((deleteFlag & 1) != 0) {
        // Deallocate the object itself (operator delete)
        FUN_009c8eb0(this);
    }
    return this;
}
// Note: this[0] = m_pSubObject1 (pointer to first owned object)
//       this[3] = m_deleteSub1 (function pointer to delete m_pSubObject1)
//       this[4] = m_pSubObject2 (pointer to second owned object)
//       this[7] = m_deleteSub2 (function pointer to delete m_pSubObject2)