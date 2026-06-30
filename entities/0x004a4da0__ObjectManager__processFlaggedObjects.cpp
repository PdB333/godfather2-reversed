// FUNC_NAME: ObjectManager::processFlaggedObjects
void __thiscall ObjectManager::processFlaggedObjects(int this, uint arg)
{
    // this+0x68: pointer to array of 16-byte entries
    // this+0x6c: count of entries
    if (*(int *)(this + 0x6c) != 0)
    {
        int entryOffset = 0; // offset into entry array
        for (uint i = 0; i < *(uint *)(this + 0x6c); i++)
        {
            // entry structure: +0x00: pointer to object (vtable), +0x04: flags (ushort)
            ushort flags = *(ushort *)(*(int *)(this + 0x68) + 4 + entryOffset);
            // Check if object has both kActive (0x2) and kReady (0x200) flags set
            if (((flags & 2) != 0) && ((flags & 0x200) != 0))
            {
                // Get object pointer from entry
                void *object = *(void **)(*(int *)(this + 0x68) + entryOffset);
                // Call virtual method at vtable offset 0x50 (index 20)
                void (*func)(void *) = (void (*)(void *))(**(int **)(object) + 0x50);
                func((void *)arg);
            }
            entryOffset += 0x10; // each entry is 16 bytes
        }
    }
}