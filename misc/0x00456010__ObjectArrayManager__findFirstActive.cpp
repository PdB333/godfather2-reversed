// FUNC_NAME: ObjectArrayManager::findFirstActive
int __fastcall ObjectArrayManager::findFirstActive(int this, int shouldAllocate) // this +0x00, shouldAllocate in EAX
{
    uint count;
    int result;
    uint i;
    int *element; // pointer to current element (each element is 9 ints = 36 bytes)
    int handle;

    i = 0;
    result = 0;
    if (shouldAllocate != 0) {
        handle = FUN_004dafd0(); // Allocate or obtain a temporary handle
    } else {
        handle = 0;
    }
    count = *(uint *)(this + 0x38); // Number of elements in the array
    if (count != 0) {
        element = *(int **)(this + 0x34); // Pointer to array of elements (each 36 bytes)
        do {
            if ((*element != 0) && (result = FUN_004cbec0(handle), result != 0)) {
                return result;
            }
            i = i + 1;
            element = element + 9; // Move to next element (9 ints)
        } while (i < count);
    }
    return result;
}