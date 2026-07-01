// FUNC_NAME: ObjectManager::findObjectByID
// Function address: 0x008bf2f0
// Searches a linear array of objects for a matching ID and returns the associated data pointer.
// The object array is stored as a pointer at offset 0x1a4 with count at offset 0x1a8.
// Each array element is a pointer to an Entry structure:
//   +0x00: (unknown, likely vtable or padding)
//   +0x04: data pointer (return value)
//   +0x08: object ID (search key)
int* __thiscall ObjectManager::findObjectByID(int thisPtr, int targetID)
{
    int* result = nullptr; // uVar1
    uint index = 0;        // uVar3

    if (*(uint*)(thisPtr + 0x1a8) != 0) // m_objectCount
    {
        int** arrayPtr = *(int***)(thisPtr + 0x1a4); // m_objectArray (array of pointers to entries)

        // Linear search for matching ID
        while (*(int*)(arrayPtr[index] + 8) != targetID) // entry->id
        {
            index++;
            if (*(uint*)(thisPtr + 0x1a8) <= index) // past array end
            {
                return result; // nullptr (not found)
            }
        }

        // Found – return entry->data (offset 0x04)
        if ((int)index >= 0) // always true, but preserved from original
        {
            result = *(int**)(arrayPtr[index] + 4);
        }
    }
    return result;
}