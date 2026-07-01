// FUNC_NAME: DataTable::getEntryData
// Function address: 0x00815d60
// Retrieves 14 dwords (56 bytes) from an entry identified by key1 and key2.
// The class has two possible data pointer offsets (4 or 0x10) depending on global flags.
void __thiscall DataTable::getEntryData(int this, unsigned int* outBuffer, unsigned int key1, unsigned int key2)
{
    // Determine which data pointer to use: offset +4 normally, or +0x10 if globals match
    int* dataPtr = (int*)(this + 4 + (uint)(g_globalA == g_globalB) * 0xC);
    // dataPtr points to a member that holds a pointer to an array of entry pointers

    int index = findEntryIndex(dataPtr, key1, key2); // FUN_00815c30 - lookup function
    if (index >= 0)
    {
        // Entry pointer is at dataPtr[index], then copy 14 dwords from offset 0x68
        unsigned int* src = (unsigned int*)(*(int*)(*dataPtr + index * 4) + 0x68);
        for (int i = 0; i < 14; i++)
        {
            *outBuffer++ = *src++;
        }
    }
}