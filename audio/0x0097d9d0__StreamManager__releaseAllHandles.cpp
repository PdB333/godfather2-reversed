// FUNC_NAME: StreamManager::releaseAllHandles
void __thiscall StreamManager::releaseAllHandles(void)
{
    // +0xB8: count of stream entries
    int entryCount = *(int*)(this + 0xB8);
    if (entryCount != 0) {
        // +0xB4: pointer to array of 0x10-byte entries
        int entryArray = *(int*)(this + 0xB4);
        for (uint i = 0; i < entryCount; i++) {
            int* entry = (int*)(entryArray + i * 0x10);
            // entry[2] (+0x08): resource handle (int)
            if (entry[2] != 0) {
                char temp; // temporary for release call
                releaseHandle(&temp, entry[2]); // FUN_009e71f0
                afterRelease();                // FUN_009f01a0 – e.g., cleanup after release
                entry[2] = 0;
            }
            // entry[1] (+0x04): pointer to object with vtable (e.g., stream buffer)
            if ((void*)entry[1] != 0) {
                (*(void(__thiscall**)(int))entry[1])(1); // virtual release/destructor with arg 1
                entry[1] = 0;
            }
            // entry[0] (+0x00): another pointer (e.g., stream source or metadata)
            if ((void*)entry[0] != 0) {
                (*(void(__thiscall**)(int))entry[0])(1);
                entry[0] = 0;
            }
        }
    }
    // Reset count and free the entry array
    *(int*)(this + 0xB8) = 0;
    freeArray(*(void**)(this + 0xB4)); // FUN_009c8f10 – deallocates array memory
    *(int*)(this + 0xB4) = 0;
    // +0xBC: some other counter or pointer, cleared
    *(int*)(this + 0xBC) = 0;
}