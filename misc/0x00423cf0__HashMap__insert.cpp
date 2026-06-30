// FUNC_NAME: HashMap::insert

// Reconstructed from 0x00423cf0
// Insert a key-value pair into the hash map.
// Structure layout (this):
//   +0x00: uint** buckets          - array of bucket head pointers
//   +0x04: uint  bucketCount       - number of buckets
//   +0x0C: uint  elementCount      - number of stored elements (index 3 in param_1)
//   +0x14: bool  autoResizeEnabled - flag to trigger resize on threshold (index 5, byte)
// Node layout:
//   +0x00: uint key
//   +0x04: uint value
//   +0x08: Node* next

void __thiscall HashMap::insert(uint** this, uint* keyPtr, uint* valuePtr, uint bucketIndexDummy)
{
    Node* newNode;
    uint bucketIndex;

    // Auto-resize check: if autoResizeEnabled and elementCount*2 <= bucketCount
    if ( ((char)this[5] != '\0') && ((uint)(this[1] * 2) <= (uint)this[3]) )
    {
        hashMapRehash();                // FUN_00423fa0 - rehash/resize
        bucketIndex = *keyPtr % (uint)this[1];
    }
    else
    {
        bucketIndex = *keyPtr % (uint)this[1];
    }

    // Allocate a new node
    newNode = (Node*)allocateNode();    // FUN_00423f20 - allocates a Node

    // Fill node
    newNode->value = *valuePtr;
    newNode->key   = *keyPtr;
    // Insert at head of bucket
    newNode->next = (Node*)(*this[bucketIndex]);

    // Update bucket head
    *this[bucketIndex] = (uint*)(uint)newNode;
}