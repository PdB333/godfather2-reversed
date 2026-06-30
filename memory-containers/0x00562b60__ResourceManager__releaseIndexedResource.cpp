// FUNC_NAME: ResourceManager::releaseIndexedResource
extern int DAT_01139810; // TLS index

void __fastcall ResourceManager::releaseIndexedResource(int* thisPtr)
{
    int index = thisPtr[2]; // offset +0x08: resource index
    if (index >= 0)
    {
        // Fetch per-thread data (TLS value unused, likely for side effect)
        (void)TlsGetValue(DAT_01139810);
        // Deallocate block: handle = thisPtr[0], offset = index * 16, type = 0x17
        deallocateBlock(thisPtr[0], index << 4, 0x17);
    }
}