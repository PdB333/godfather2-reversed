// FUNC_NAME: HashTable4Int::containsKey
void __thiscall HashTable4Int::containsKey(int *this, int *key)
{
    int data;
    uint hash;
    int *node;
    int keyParts[4]; // local_10, local_c, local_8, local_4

    // Copy the 4 integers from the key (16 bytes)
    keyParts[0] = key[0];
    keyParts[1] = key[1];
    keyParts[2] = key[2];
    keyParts[3] = key[3];

    // Call some initialization or lock? (FUN_004d9af0)
    FUN_004d9af0();

    // Hash the 16-byte key (0x10 = 16)
    hash = FUN_004db320(keyParts, 0x10);

    // Get the bucket index: hash % bucketCount (this[1] is number of buckets)
    int bucketIndex = hash % (uint)this[1];

    // Get the head of the linked list for this bucket
    node = *(int **)(*this + bucketIndex * 4);

    // Traverse the linked list
    while (node != (int *)0x0) {
        data = *node; // data pointer is first field of node
        // Compare the 4 integers at offsets +0x10, +0x14, +0x18, +0x1c of data
        if (*(int *)(data + 0x10) == key[0] &&
            *(int *)(data + 0x14) == key[1] &&
            *(int *)(data + 0x18) == key[2] &&
            *(int *)(data + 0x1c) == key[3]) {
            return; // Found, exit
        }
        node = (int *)node[1]; // next node pointer at offset 4
    }
    return; // Not found
}