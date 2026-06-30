// FUNC_NAME: InputMappingManager::findAndExecuteAction
uint __thiscall InputMappingManager::findAndExecuteAction(int *this, uint actionId, uint param3)
{
    uint index = 0;
    int *mappingEntry;

    if (this[0xaf] != 0) // number of mappings (count at offset +0x2bc)
    {
        mappingEntry = (int *)this[0xae]; // pointer to mapping array at offset +0x2b8
        do
        {
            int mappedId;
            if (*mappingEntry == 0)
            {
                mappedId = 0;
            }
            else
            {
                mappedId = *mappingEntry - 0x48; // raw key code to action ID conversion
            }

            if (mappedId == actionId)
            {
                // Found matching mapping – invoke virtual function at vtable+0x218 with index and param3
                return (**(code **)(*this + 0x218))(index, param3);
            }

            index = index + 1;
            mappingEntry = mappingEntry + 2; // each entry is 2 ints (mappedId, something else)
        } while (index < (uint)this[0xaf]);
    }

    // No match found – return a masked error/status
    return (mappedId & 0xffffff00); // last computed mappedId (may be from final iteration)
}