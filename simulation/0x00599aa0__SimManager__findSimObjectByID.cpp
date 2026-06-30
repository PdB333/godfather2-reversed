// FUNC_NAME: SimManager::findSimObjectByID
// Function at address 0x00599aa0
// Iterates over active sim objects, calling a virtual ID getter, returns the object matching param_2.
// Offsets:
// +0x58 : count of active entries (byte)
// +0x59 : array of byte indices into the handle table
// +0x1bc: pointer to HandleTable structure
// HandleTable+0x14: array of object pointers
// HandleTable+0x18: array of entry state ints

int* SimManager::findSimObjectByID(int targetId)
{
    int idx = 0;
    if (*(char *)(this + 0x58) != '\0')
    {
        do
        {
            uint entryIndex = (uint)*(byte *)(this + 0x59 + idx);
            int handleTable = *(int *)(this + 0x1bc);
            // If the entry state is not -2 (invalid/unused), log a debug message
            if (*(int *)(*(int *)(handleTable + 0x18) + entryIndex * 4) != -2)
            {
                (**(code **)(*DAT_01205590 + 4))(); // debugPrintWarning
            }
            int* pObject = *(int **)(*(int *)(handleTable + 0x14) + entryIndex * 4);
            int objectId = (**(code **)(*pObject + 0xc))(); // virtual: getObjectID()
            if (objectId == targetId)
            {
                return pObject;
            }
            idx = idx + 1;
        } while (idx < (int)(uint)*(byte *)(this + 0x58));
    }
    return (int *)0x0;
}