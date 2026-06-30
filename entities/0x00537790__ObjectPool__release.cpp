// FUNC_NAME: ObjectPool::release
void __cdecl ObjectPool::release(unsigned int objectIndex)
{
    unsigned int savedValue;
    struct ObjectPoolEntry* entry;

    if (objectIndex != 0)
    {
        if (objectIndex < 0x1000)
        {
            entry = &g_objectPool[objectIndex];  // g_objectPool[objectIndex] = base + objectIndex * 0x38
        }
        else
        {
            entry = NULL;
        }
        savedValue = entry->field_c;  // +0x0C: some stored value (maybe reference count or data handle)
        if ((objectIndex != 0xFFFFFFFF) && (objectIndex < 0x1000))
        {
            if ((entry != NULL) && (entry->state < 4))  // +0x00: state byte, <4 means active/valid
            {
                if (entry->dataPtr != 0)  // +0x10? Actually +0x44? Wait, the code uses &DAT_011a0f44 + iVar2, so offset +0x1C? Let's recalc: base 0x011a0f28, stride 0x38. The address used for the pointer is &DAT_011a0f44 + iVar2. &DAT_011a0f44 is 0x011a0f44, which is base +0x1C. So entry->dataPtr at +0x1C.
                {
                    memoryFree(entry->dataPtr, 0x200000);  // Free with flag
                }
                entry->flags = (entry->flags & 0xFCAC8FFF) | 0x200000;  // +0x34: set bit 21, clear others
                notifyPoolChanged();
            }
        }
        if (*(int*)(g_poolManager + 4) != 0)  // g_poolManager is at 0x0121b0ac, dereference +4
        {
            performGarbageCollect();
        }
        memoryFree(objectIndex, savedValue);  // Final cleanup with original index and saved value
    }
    else
    {
        if (*(int*)(g_poolManager + 4) != 0)
        {
            performGarbageCollect();
        }
    }
}