// FUNC_NAME: initHashEntry
uint32_t* __cdecl initHashEntry(uint32_t* out, void* chainBase)
{
    uint32_t* result = out;
    // Set default hash value (likely for "null" or empty)
    *out = 0xFE16702F;
    if (chainBase != nullptr)
    {
        // Read signed byte offset at +0x10 from chainBase to locate next node in chain
        int8_t offset = *(int8_t*)((uint8_t*)chainBase + 0x10); // +0x10: chain link offset
        void* nextNode = (uint8_t*)chainBase + offset;
        if (nextNode != nullptr)
        {
            // Resolve and copy the hash from the chained node
            uint32_t* src = FUN_0054c080(&out, nextNode); // unknown hash resolution function
            *result = *src;
        }
    }
    return result;
}