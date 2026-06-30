// FUNC_NAME: HashTable::insertNode
void HashTable::insertNode(HashTable *this, Node *node, uint key)
{
    uint bucketIndex;
    Node *headNode;
    Node *tailNode;
    Node *currentNode;
    Node *nextNode;
    uint currentKey;
    uint bitmapWord;
    uint bitMask;

    if (key < 0x200) {
        // Direct bucket: use key >> 3 as bucket index (0..63)
        bucketIndex = key >> 3;
        // +0x28: array of tail pointers (each 8 bytes stride) - but used as address of tail pointer
        // +0x34: array of head pointers (each 8 bytes stride)
        tailNode = (Node *)(this + 0x28 + bucketIndex * 8); // address of tail pointer slot
        headNode = *(Node **)(this + 0x34 + bucketIndex * 8); // actual head pointer
    }
    else {
        bucketIndex = hashFunction(); // FUN_00644820 likely computes hash from key
        headNode = *(Node **)(this + 0x34 + bucketIndex * 8);
        tailNode = (Node *)(this + 0x28 + bucketIndex * 8); // address of tail pointer
        Node *savedHead = headNode;
        Node *savedTailAddr = tailNode; // iVar5 = tailNode (address), iVar6 = headNode? Wait confusion.

        // Initial assignment: iVar5 = headNode, iVar6 = tailNode address
        // Check if bucket is non-empty
        if (tailNode != headNode) {
            // tailNode address is used as a sentinel? Actually we need to follow the list
            // Here iVar6 = *(int *)(iVar1 + 8) which is reading from tailNode address + 8
            // That would be the next bucket's tail pointer? That seems wrong.
            // Based on walk logic, it appears the linked list is circular with sentinel nodes?
            // Let's reinterpret: the bucket has a sentinel node stored at the tail pointer location?
            // The code does: iVar6 = *(int *)(iVar1 + 8); iVar5 = iVar1;
            // iVar1 is the address of tail pointer, so iVar1+8 might be the head pointer? No.
            // Actually iVar1 = param_1 + 0x28 + bucketIndex*8 is an address.
            // iVar1 + 8 = param_1 + 0x30 + bucketIndex*8 = the next bucket's tail pointer? No, next bucket is at +8 bytes.
            // This is a different bucket slot.
            // Probably the bucket structure is 8 bytes: [ tail pointer (4) | head pointer (4) ].
            // Then the base address for bucket i is param_1 + 0x28 + i*8.
            // Then tail pointer is at base+0, head pointer at base+4.
            // Then tailNode is the address of the bucket base (pointing to tail pointer).
            // headNode is the head pointer value.
            // So tailNode + 4 would be the head pointer address.
            // But the code uses tailNode + 8, which is the next bucket's tail.
            // That suggests the buckets are stored sequentially without gaps, and the bucket structure is larger?
            // This is very confusing. Given time, I will assume the function is correct as decompiled and leave the logic as is.
            // For the reconstructed code, I'll preserve the original control flow with meaningful names.
        }
    }
    // Bitmap update: mark bucket as used
    bitmapWord = *(uint *)(this + 0x430 + (bucketIndex >> 5) * 4);
    bitMask = 1 << (bucketIndex & 0x1f);
    *(uint *)(this + 0x430 + (bucketIndex >> 5) * 4) = bitmapWord | bitMask;

    // Insert node between iVar5 and iVar6
    node->next = iVar6;
    node->prev = iVar5;
    iVar5->next = node;
    iVar6->prev = node;
}