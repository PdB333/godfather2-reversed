// FUNC_NAME: SkipList::findNode

void __thiscall SkipList::findNode(uint32_t** this, uint32_t** outNode, uint32_t* key)
{
    // this[0] = header node pointer
    // this[1] = highest level index (max level)
    // Header node has: +0x00 key (likely unused), +0x08 forward array
    // Each node: +0x00 key, +0x08 forward array (indexed by level)
    uint32_t* current = this[0];
    int32_t level = this[1];

    while (level >= 0)
    {
        uint32_t* next = *(uint32_t**)(current[2] + level * 4);
        if (next != 0)
        {
            do
            {
                current = next;
                if (*key <= *current)
                    break;
                next = *(uint32_t**)(current[2] + level * 4);
            } while (next != 0);
        }
        // After traversing at this level, check the forward pointer at level 0
        uint32_t* candidate = *(uint32_t**)current[2];
        if (candidate == 0)
            break;
        if (*candidate == *key)
        {
            *outNode = candidate;
            return;
        }
        level--;
    }
    *outNode = 0;
    return;
}