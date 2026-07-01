// FUNC_NAME: ResourceManager::releaseAllWithCallbacks
void __fastcall ResourceManager::releaseAllWithCallbacks(ResourceManager* this)
{
    // Check if the "dirty" flag (bit 1) is set at offset 0x10
    if ((this->flags & 0x2) != 0)
    {
        // Array of 27 callback entries starting at offset 0x20b8
        // Each entry is 16 bytes: [objectPtr, field4, field8, callback]
        // The loop pointer starts at the third field (offset 8) of each entry
        int* entryField8 = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x20b8);
        int count = 27; // 0x1B entries

        do
        {
            // entryField8[-2] is the object pointer (offset 0 of the entry)
            int* objectPtr = reinterpret_cast<int*>(entryField8[-2]);
            if (objectPtr != nullptr)
            {
                // entryField8[1] is the callback function pointer (offset 12 of the entry)
                void (*callback)(int*) = reinterpret_cast<void (*)(int*)>(entryField8[1]);
                callback(objectPtr);
            }

            // Zero out the three fields: objectPtr, field4, field8
            entryField8[-2] = 0; // object pointer
            entryField8[-1] = 0; // field at offset 4
            entryField8[0] = 0;  // field at offset 8 (current)

            // Move to the next entry (16 bytes forward)
            entryField8 += 4; // 4 * sizeof(int) = 16 bytes
            count--;
        } while (count != 0);

        // Clear the dirty flag (bit 1)
        this->flags &= ~0x2;
    }
}