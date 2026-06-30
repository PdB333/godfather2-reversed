// FUNC_NAME: EARS::Util::HashTable::insertNode
// Address: 0x006e6ed0
// Role: Insert a node into a chained hash table, possibly growing the table if threshold is exceeded
// Structure offsets:
//   +0x00: m_buckets (uint*) - pointer to array of bucket heads
//   +0x04: m_capacity (uint) - number of bucket slots
//   +0x08: m_count (uint) - number of elements currently stored
//   +0x0C: m_autoGrow (bool) - flag to enable automatic growth when load factor exceeds 2.0

uint * __thiscall HashTable::insertNode(uint *this, uint *node, uint hash)
{
    // If auto-grow is enabled and count >= capacity*2, grow the table
    if (((char)this[3] != '\0') && ((uint)(this[1] * 2) <= (uint)this[2])) {
        grow();
        // Recompute bucket index using the node's key (stored at offset 0 of node)
        hash = node[0] % (uint)this[1];
    }

    // Link node to the head of the bucket chain
    uint **buckets = (uint **)this[0];

    // Save the previous head of the bucket
    node[4] = (uint)buckets[hash];
    // Insert node at the head of the bucket
    buckets[hash] = node;
    // Increment element count
    this[2] = this[2] + 1;

    return node;
}