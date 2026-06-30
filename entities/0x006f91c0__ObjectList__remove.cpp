// FUNC_NAME: ObjectList::remove
/**
 * Function: ObjectList::remove
 * Address: 0x006f91c0
 * Role: Remove an object from the internal pointer list by comparing the pointer value.
 *       Calls FUN_006f8ff0 with the index of the removed element.
 * 
 * Offsets:
 *   +0x1c: Pointer to array of object pointers (int**)
 *   +0x20: Number of elements in the array (uint)
 */
bool __thiscall ObjectList::remove(void* objectToRemove)
{
    bool found = false;
    uint count = *(uint*)(this + 0x20);
    if (count != 0)
    {
        int** array = *(int***)(this + 0x1c);
        uint index = 0;
        while (*array != (int*)objectToRemove)
        {
            index++;
            array++;
            if (index >= count)
            {
                return found; // not found
            }
        }
        found = true;
        FUN_006f8ff0(index); // process removal at index (e.g., shift elements, notify)
    }
    return found;
}