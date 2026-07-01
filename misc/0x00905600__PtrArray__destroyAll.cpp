//FUNC_NAME: PtrArray::destroyAll
// Address: 0x00905600
// Iterates backwards over an array of elements (each 0x1c bytes), calls destructor function pointer at +0x0c on the object pointer at +0x00 if non-null, then frees the array.

struct PtrArrayElement {
    void* object;           // +0x00
    char pad_04[0x8];       // +0x04 (unused in this function)
    void (*destructor)(void*); // +0x0c
    char pad_10[0x10];      // +0x10 (rest of 0x1c)
};

struct PtrArray {
    PtrArrayElement* elements; // +0x00
    int count;                 // +0x04
};

void __fastcall PtrArray::destroyAll(PtrArray* this) {
    int i = this->count - 1;
    if (i >= 0) {
        int offset = i * sizeof(PtrArrayElement); // 0x1c
        do {
            PtrArrayElement* elem = reinterpret_cast<PtrArrayElement*>(reinterpret_cast<char*>(this->elements) + offset);
            if (elem->object != nullptr) {
                elem->destructor(elem->object);
            }
            i--;
            offset -= sizeof(PtrArrayElement);
        } while (i >= 0);
    }
    if (this->elements != nullptr) {
        FUN_009c8f10(this->elements); // deallocate array memory
    }
}