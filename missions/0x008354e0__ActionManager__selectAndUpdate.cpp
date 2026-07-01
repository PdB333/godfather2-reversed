// FUNC_NAME: ActionManager::selectAndUpdate
// Function at 0x008354e0: Finds an object by ID from a list, updates its stored values from offset 0x60/0x70, and triggers an action via FUN_00834bb0.
// Class layout (offsets relative to this):
// +0xD0: int* m_objectList (array of pointers to objects)
// +0xD4: int m_objectCount
// Each object in the list has:
// +0x00: vtable
// +0xDC: int m_id
// +0x60: int m_valueA (source for copy)
// +0x70: int m_valueB (source for copy)
// +0x80: int m_cachedValueA (destination)
// +0x84: int m_cachedValueB (destination)
// vtable+0x1c: bool isActive() virtual method

void __thiscall ActionManager::selectAndUpdate(int thisPtr, int *idPtr)
{
    int *objectPtr;
    char isValid;
    int newValueA;
    int newValueB;
    int index;

    index = *(int *)(thisPtr + 0xd4) - 1;
    if (index >= 0)
    {
        do
        {
            objectPtr = *(int **)(*(int *)(thisPtr + 0xd0) + index * 4);
            // Check if object's ID matches the given ID and if it is still active
            if (objectPtr[0x37] == *idPtr)
            {
                // Virtual call to check if object is active
                isValid = (**(code **)(*objectPtr + 0x1c))();
                if (isValid != '\0')
                {
                    break;
                }
            }
            index--;
            if (index < 0)
            {
                return;
            }
        } while (true);

        // Found matching object; retrieve values from offset 0x70 and 0x60
        int matchedObject = *(int *)(*(int *)(thisPtr + 0xd0) + index * 4);
        newValueA = FUN_00834f80(matchedObject + 0x70);   // get value at offset 0x70
        newValueB = FUN_00834f80(matchedObject + 0x60);   // get value at offset 0x60
        // Store them at offset 0x80 and 0x84
        *(int *)(matchedObject + 0x80) = newValueB;
        *(int *)(matchedObject + 0x84) = newValueA;
        // Trigger update/action on the object
        FUN_00834bb0(matchedObject);
    }
    return;
}