// FUNC_NAME: SortedArray::insert
// 0x00832420 - Insert element into sorted dynamic array (4-byte elements)
// Structure at param_1:
//   +0x08: data (pointer to array of uint32)
//   +0x0c: size (number of elements)
//   +0x10: capacity (allocated slots)

void __thiscall SortedArray::insert(int thisPtr, uint32 value)
{
    int capacity = *(int*)(thisPtr + 0x10);
    int size = *(int*)(thisPtr + 0x0c);

    if (size == capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;

        FUN_0082b640(capacity); // reallocate capacity
    }

    uint32* slot = (uint32*)(*(int*)(thisPtr + 8) + size * 4);
    *(int*)(thisPtr + 0x0c) = size + 1;

    if (slot != nullptr)
        *slot = value;

    if (*(uint32*)(thisPtr + 0x0c) > 1)
    {
        _qsort(*(void**)(thisPtr + 8), *(uint32*)(thisPtr + 0x0c), 4,
            (_PtFuncCompare*)&sortedArrayCompare); // comparator at 0x00833690
    }
}