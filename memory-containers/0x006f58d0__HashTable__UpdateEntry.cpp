// FUNC_NAME: HashTable::UpdateEntry
// Address: 0x006f58d0
// Description: Looks up an entry in a hash table by key, updates a timestamp and global flags if conditions are met.
// Hash table structure: each bucket is a linked list of nodes; node[0]=key, node[1]=?, node[2]=value (float), node[3]=next pointer.

void HashTable::UpdateEntry(uint* entry) // entry points to a struct with key, value, flags, etc.
{
    // Global hash table: first pointer is bucket array base, second element is bucket count.
    // DAT_0112aa04 is a pointer to a struct { uint* base; uint count; }
    uint bucketIndex = entry[0] % ((uint*)DAT_0112aa04)[1]; // entry[0] is key
    uint* node = *(uint**)(*(uint*)DAT_0112aa04 + bucketIndex * 4); // pointer to first node in bucket

    if (node == nullptr)
        return;

    // Walk linked list (node[3] is next)
    while (node[0] != entry[0])
    {
        node = (uint*)node[3];
        if (node == nullptr)
            return;
    }

    // Node found; check valid and not special sentinel (0xfffffffc)
    if (node == nullptr || node == (uint*)0xfffffffc)
        return;

    // Update global flags from entry's flags byte 1 (bits 8-19)
    // DAT_0112aa08 is a global bitmask.
    uint32_t flagsMask = entry[7] & 0x0000FF00; // extract bits 8..15? Actually 0xff000 covers bits 12-19? Wait: 0xff000 = 0x00FF0000? No, 0xff000 = 0x000FF000? Let's be precise:
    // 0xff000 = 0x000FF000 in 32-bit? Actually 0xff000 is 0x000FF000? Let's calculate: 0xff000 = (0xFF << 12) = 0x000FF000. So bits 12-19.
    // But param_1[7] & 0xff000 extracts bits 12-19. The global DAT_0112aa08 is ORed with that.
    DAT_0112aa08 |= (entry[7] & 0x000FF000);

    // If bit 7 of entry[7] is not set (i.e., not a certain flag), update node's float value with a global delta.
    if ((entry[7] & 0x80) == 0)
    {
        // Add global time delta (DAT_01205214) to node's stored float (node[2]).
        node[2] = (uint)((float)entry[2] + DAT_01205214);
    }
}