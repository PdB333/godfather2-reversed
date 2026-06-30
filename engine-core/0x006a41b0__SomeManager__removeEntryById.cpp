// FUNC_NAME: SomeManager::removeEntryById
void __thiscall SomeManager::removeEntryById(int thisPtr, int id, int flag, int extraParam)
{
    // +0x54: count of entries
    // +0x58: pointer to array of entries (each 0x30 bytes)
    // Each entry: offset 0x10 is the ID field (int)
    if (flag == 0)
    {
        int count = *(int*)(thisPtr + 0x54);
        if (count > 0)
        {
            int* entryPtr = (int*)(*(int*)(thisPtr + 0x58) + 0x10); // start at first entry's ID field
            int index = 0;
            while (*entryPtr != id)
            {
                index++;
                entryPtr = (int*)((char*)entryPtr + 0x30); // step to next entry's ID (correct stride)
                if (index >= count)
                {
                    return;
                }
            }
            // Found, call function to handle removal
            FUN_006a5690(id, 0, extraParam);
            // Clear the ID field to mark entry as empty/free
            *(int*)(*(int*)(thisPtr + 0x58) + index * 0x30 + 0x10) = 0;
        }
    }
}