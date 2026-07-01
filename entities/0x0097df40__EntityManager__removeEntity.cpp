//FUNC_NAME: EntityManager::removeEntity
void __thiscall EntityManager::removeEntity(int thisPtr, int entityId)
{
    uint count = *(uint *)(thisPtr + 0x54); // number of entities in the array
    uint index = 0;

    if (count != 0)
    {
        int *array = (int *)(thisPtr + 0x34); // array of entity IDs (or pointers)
        while (*array != entityId)
        {
            index++;
            array++;
            if (count <= index)
            {
                return; // entity not found
            }
        }

        // Found the entity at index
        count--;
        *(uint *)(thisPtr + 0x54) = count;

        if (index != count)
        {
            // Move the last element into the removed slot (swap removal)
            *(int *)(thisPtr + 0x34 + index * 4) = *(int *)(thisPtr + 0x34 + count * 4);
        }

        // Check if all sub-containers are empty
        int totalCount = *(int *)(thisPtr + 0x9c) + *(int *)(thisPtr + 0x78) + *(int *)(thisPtr + 0x30) + count;
        if (totalCount == 0)
        {
            FUN_0097c5d0(); // likely cleanup/destroy function
        }
    }
}