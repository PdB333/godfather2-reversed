// FUNC_NAME: HashTable::find
void __thiscall HashTable::find(void *this, Node **outNode, uint *keyPtr)
// Hash table with chaining: struct { int unknown; Node** buckets; uint numBuckets; }
// Node struct: { uint key; /* value? */ Node* next; }
{
    uint bucketIndex = *keyPtr % *(uint *)((int)this + 8);  // +8: numBuckets
    Node **bucketSlot = (Node **)(*(int *)((int)this + 4) + bucketIndex * 4); // +4: buckets array
    Node *node = *bucketSlot;

    while (node != (Node *)0x0) {
        if (*keyPtr == node->key) {
            goto found;
        }
        node = node->next;  // +8: next
    }

    // Not found: point to sentinel bucket (buckets[numBuckets])
    bucketSlot = (Node **)(*(int *)((int)this + 4) + *(uint *)((int)this + 8) * 4);
    node = (Node *)*bucketSlot;

found:
    outNode[0] = node;          // Node pointer (null if not found)
    outNode[1] = bucketSlot;   // Bucket slot address (for insertion/removal)
    return;
}