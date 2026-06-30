// FUNC_NAME: GameObjectManager::findEntryByGroup
int __thiscall GameObjectManager::findEntryByGroup(int this, void* pBucket, int value)
{
    int adjustedValue = value - *(int*)(this + 0x20); // subtract base offset
    unsigned char bucketCount = *(unsigned char*)((char*)pBucket + 0x14);
    if (bucketCount == 0)
    {
        return 0;
    }
    unsigned short baseIndex = *(unsigned short*)((char*)pBucket + 0x10);
    int entryArrayBase = *(int*)(this + 0x24); // pointer to start of 16-byte entries
    int groupId = adjustedValue / 36; // signed division, truncating toward zero

    for (int i = 0; i < bucketCount; i++)
    {
        int entryOffset = ((baseIndex + i) & 0xFFFF) * 16;
        int entryAddr = entryArrayBase + entryOffset;
        short entryGroupId = *(short*)(entryAddr + 4);
        if (entryGroupId == (short)groupId)
        {
            return entryAddr;
        }
    }
    return 0;
}