// FUNC_NAME: DynamicArray::getCount
// Reconstructed C++ for function at 0x005d9a60
// Returns the number of elements in a dynamic array (element size 0x28 bytes).
// Object layout:
//   +0x08: pointer to start of array (or 0 if empty)
//   +0x0c: pointer to end of array (one past last element)

int __fastcall DynamicArray::getCount(DynamicArray *this)
{
    int start = *(int *)((char *)this + 8);
    if (start == 0) {
        return 0;
    }
    int end = *(int *)((char *)this + 0xc);
    return (end - start) / 0x28; // each element is 0x28 bytes
}