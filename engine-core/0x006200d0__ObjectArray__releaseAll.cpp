// FUNC_NAME: ObjectArray::releaseAll
void __thiscall ObjectArray::releaseAll( ObjectArray *this )
{
    uint count;
    int idx;
    // this points to an object with count at offset 0 and array pointer at offset 0x14 (this[5])
    // array points to a structure with an 8-byte header followed by elements of size 0x10
    // edi holds a vtable pointer for the element destructor at offset +0xc
    uint *arrayPtr;
    uint *destructorVTable;

    // assume these registers are set before call (compiler optimization)
    // normally these would be class members
    // Here we simulate with local variables for reconstruction
    // In reality, this->array and this->count are used directly.

    count = this->count;
    arrayPtr = this->array; // +0x14
    destructorVTable = this->something; // not stored in this, comes from global/register

    if ((count != 0) && (destructorVTable != (uint *)0x0)) {
        // iterate over each element in the array (each 0x10 bytes, starting at array+8)
        for (idx = 0; idx < count; idx++) {
            uint *element = arrayPtr + 2 + idx * 4; // +8 bytes header, then idx*0x10 bytes (4 dwords)
            // call element destructor vtable+0xc with element and flag 0
            ((void (__thiscall *)(void *, int))destructorVTable[3])(element, 0);
        }
        // also destroy the array container itself
        ((void (__thiscall *)(void *, int))destructorVTable[3])(arrayPtr, 0);
        // clear references
        this->array = 0;
        this->count = 0;
    }
}