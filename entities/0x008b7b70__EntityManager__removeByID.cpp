// FUNC_NAME: EntityManager::removeByID
// Function address: 0x008b7b70
// Removes all elements with matching ID from a manager list (stored at this+0x508 count, array at this+0x08, each element 0x14 bytes)

void __thiscall EntityManager::removeByID(int id)
{
    int count = *(int *)(this + 0x508); // count of stored elements
    for (int i = count - 1; i >= 0; i--)
    {
        int *entry = (int *)(this + 0x08 + i * 0x14); // +0x00: ID, rest unknown
        if (*entry == id)
        {
            // Remove or handle the element at index i (function at 0x008b7a40)
            removeAtIndex(i);
        }
    }
}