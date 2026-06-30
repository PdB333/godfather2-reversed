// FUNC_NAME: HashTable::insertOrdered
void __fastcall HashTable::insertOrdered(Node* node, uint key)
{
    uint bucketIndex;
    Node* nextNode;
    Node* prevNode;

    if (key < 0x200) {
        // Direct bucket index for small keys
        bucketIndex = key >> 3;
        nextNode = (Node*)((uint)this + 0x28 + bucketIndex * 8); // head sentinel pointer address
        prevNode = *(Node**)((uint)this + 0x34 + bucketIndex * 8); // tail pointer
    } else {
        // Use hash function for larger keys
        bucketIndex = FUN_00644820();
        Node* tail = *(Node**)((uint)this + 0x34 + bucketIndex * 8);
        Node* head = (Node*)((uint)this + 0x28 + bucketIndex * 8);
        nextNode = head;
        prevNode = tail;

        if (head != tail) {
            // Search backwards from tail to find insertion point
            nextNode = *(Node**)((uint)head + 8); // first real node after sentinel
            prevNode = head;
            uint currKey = *(uint*)((uint)tail + 4) & 0x7ffffff8;
            while (key < currKey) {
                tail = *(Node**)((uint)tail + 0xc); // prev pointer
                currKey = *(uint*)((uint)tail + 4) & 0x7ffffff8;
            }
            nextNode = *(Node**)((uint)tail + 8);
            prevNode = tail;
        }
    }

    // Mark the bucket as used in the bitmap at offset 0x430
    *(uint*)((uint)this + 0x430 + ((bucketIndex >> 5) << 2)) |= (1 << (bucketIndex & 0x1f));

    // Insert node between prevNode and nextNode
    node->next = nextNode;
    node->prev = prevNode;
    prevNode->next = node;
    nextNode->prev = node;
}