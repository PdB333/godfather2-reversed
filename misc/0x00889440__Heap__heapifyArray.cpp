// FUNC_NAME: Heap::heapifyArray
void Heap::heapifyArray(int* arrayBase, int* arrayEnd, void* userData)
{
    uint size = (arrayEnd - arrayBase) >> 2; // number of 4-byte elements (1-indexed)
    if (size <= 1)
        return;

    int* base = arrayBase;
    // start from last non-leaf node in a 1-indexed heap
    uint rootIndex = size / 2; // 1-based index
    do
    {
        int tempValue = base[rootIndex - 1]; // element at 1-based index
        // sift down from this root
        FUN_00888940(base, rootIndex, size, rootIndex, &tempValue, userData);
        rootIndex--;
    } while (rootIndex != 0);
}