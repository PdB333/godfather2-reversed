// FUNC_NAME: EntityDataManager::findEntityByID
// Address: 0x008b1d80
// Role: Searches an array of entity pointers (stored at this+0x10) for an entity with a specific ID (stored at entity+0x1c).
// Returns a pointer to the matching entity, or 0 if not found.

int __thiscall EntityDataManager::findEntityByID(int this, int id)
{
    int result = 0;
    uint index = 0;
    
    if (*(uint *)(this + 0x14) != 0) // count at this+0x14
    {
        int **arrayPtr = *(int ***)(this + 0x10); // pointer to array of entity pointers at this+0x10
        
        while (id != *(int *)(*arrayPtr + 0x1c)) // ID field at entity+0x1c
        {
            index++;
            arrayPtr++; // advance to next pointer in the array
            if (*(uint *)(this + 0x14) <= index) // check array bounds
            {
                return result; // 0 = not found
            }
        }
        result = *(int **)(this + 0x10)[index]; // found, get the entity pointer at that index
    }
    return result;
}