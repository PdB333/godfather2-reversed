//FUNC_NAME: ObjectList::findAndProcess
void __thiscall ObjectList::findAndProcess(int thisPtr, int searchKey)
{
    uint index = 0;
    // +0x3c: count of elements in the array
    if (*(uint *)(thisPtr + 0x3c) != 0) {
        // +0x38: pointer to array of ints (object IDs or pointers)
        int *array = *(int **)(thisPtr + 0x38);
        do {
            if (array[index] == searchKey) {
                // Note: The original decompiled code includes a check (int)index < 0,
                // which is always false for unsigned index; likely a decompiler artifact.
                // Call the processing function (FUN_008e5de0)
                processFoundItem();
                return;
            }
            index++;
        } while (index < *(uint *)(thisPtr + 0x3c));
    }
    return;
}