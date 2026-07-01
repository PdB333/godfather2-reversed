// FUNC_NAME: ObjectListManager::findAndExecute
// Function address: 0x0090e110
// This method searches through an array of object pointers (each with an ID at offset +0xC)
// When a matching ID is found, it calls a callback function (FUN_004d3d90) with the given data (param_3).
// The intended use might be to notify or process an object identified by param_2.

void __thiscall ObjectListManager::findAndExecute(int param_2, uint param_3)
{
    uint index = 0;
    // Object count at this+0x1C
    if (*(uint *)(this + 0x1C) != 0) {
        // Pointer to array of object pointers at this+0x18
        int **objectPtrArray = *(int ***)(this + 0x18);
        // Iterate until we find an object with matching ID at +0xC
        while (*(int *)(*(objectPtrArray[index]) + 0xC) != param_2) {
            index++;
            if (*(uint *)(this + 0x1C) <= index) {
                return; // Not found
            }
        }
        // Found valid index
        if ((int)index >= 0) {
            // Call the callback function with param_3
            FUN_004d3d90(param_3);
        }
    }
    return;
}