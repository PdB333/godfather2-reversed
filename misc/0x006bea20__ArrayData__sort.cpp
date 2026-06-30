// FUNC_NAME: ArrayData::sort
// Address: 0x006bea20
// Role: Sort an array of 4-byte elements (pointers) using qsort if more than 1 element.
// Struct offsets: +0x00 = pointer to array data, +0x04 = element count

struct ArrayData {
    void* data;       // +0x00
    unsigned int count; // +0x04
};

void __thiscall ArrayData::sort(int (__cdecl *compar)(const void*, const void*))
{
    if (this->count > 1) {
        qsort(this->data, this->count, 4, compar);
    }
}