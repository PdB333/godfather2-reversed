// FUNC_NAME: EntityDataManager::findEntityByID
int __thiscall EntityDataManager::findEntityByID(int this, int entityId)
{
    int result = 0;
    uint index = 0;

    // +0x28: count of entries in the array
    if (*(uint *)(this + 0x28) != 0)
    {
        // +0x24: pointer to an array of entity pointers
        int **arrayBase = *(int ***)(this + 0x24);
        int **currentEntry = arrayBase;

        // Linear search by +0x54 (entity ID field)
        while (*(int *)(*currentEntry + 0x54) != entityId)
        {
            index++;
            currentEntry++;

            if (index >= *(uint *)(this + 0x28))
            {
                return result; // not found
            }
        }

        // Found – return the matching entity pointer
        result = arrayBase[index];
    }

    return result;
}