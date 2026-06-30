// FUNC_NAME: SomeManager::setFlagOnNthItem
// Address: 0x005727f0
// Role: Sets a flag (bit 28) on the index-th item in a linked list. The list head is stored at this+0x124,
// each node has a 'next' pointer at +0x124 and a flags field at +0x10.

bool __thiscall SomeManager::setFlagOnNthItem(int index)
{
    if (!this || index < 0)
        return false;

    // +0x124: pointer to head of linked list
    int* node = *(int**)((char*)this + 0x124);
    int i = 0;

    if (index > 0)
    {
        do
        {
            // +0x124: next pointer in each node
            node = *(int**)((char*)node + 0x124);
            if (!node)
                return false;
            i++;
        } while (i < index);
    }

    if (node)
    {
        // +0x10: flags bitfield
        *(uint32_t*)((char*)node + 0x10) |= 0x10000000;
        return true;
    }

    return false;
}