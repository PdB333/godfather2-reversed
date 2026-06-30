// FUNC_NAME: EntityHandleArray::addUnique
void EntityHandleArray::addUnique(int handle)
{
    uint count = *(uint *)(this + 0x19c);
    uint index = 0;
    if (count != 0) {
        int *arr = *(int **)(this + 0x198);
        do {
            if (*arr == handle) {
                // Already present – do not add duplicate
                if (index != 0xFFFFFFFF) {
                    return;
                }
                break;
            }
            index++;
            arr++;
        } while (index < count);
    }
    // Not found – add element
    uint capacity = *(uint *)(this + 0x1a0);
    if (count == capacity) {
        // Need to grow the array
        int newCapacity = (count == 0) ? 1 : count * 2;
        // FUN_006ad8a0 expands the array to newCapacity
        EntityHandleArray::expandArray(newCapacity);
    }
    int *dest = *(int **)(this + 0x198) + count; // +0x198 array pointer
    *(uint *)(this + 0x19c) = count + 1;          // increment count
    if (dest != nullptr) {
        *dest = handle;
    }
}