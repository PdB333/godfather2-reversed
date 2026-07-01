// FUNC_NAME: SelectionManager::selectByID
// Address: 0x008bf3d0
// Iterates over an array of objects (pointers at this+0x1a4, count at this+0x1a8),
// compares each object's integer field at offset +0x08 against targetID.
// If match found, calls the selection handler FUN_008bd890.

void __thiscall SelectionManager::selectByID(int targetID)
{
    uint idx = 0;
    // this->count at offset 0x1a8
    if (*(uint *)((int)this + 0x1a8) != 0)
    {
        // this->array at offset 0x1a4 (array of pointers to objects)
        int **array = *(int ***)((int)this + 0x1a4);
        do
        {
            // Object's ID field at offset 0x08
            if (*(int *)(*array + 8) == targetID)
            {
                // Safety check for negative index (always false in practice)
                if ((int)idx < 0)
                {
                    return;
                }
                FUN_008bd890(); // Handle selection (e.g., activate or highlight)
                return;
            }
            idx++;
            array++;
        } while (idx < *(uint *)((int)this + 0x1a8));
    }
    return;
}