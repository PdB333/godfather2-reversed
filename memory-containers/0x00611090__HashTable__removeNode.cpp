// FUNC_NAME: HashTable::removeNode
int __thiscall HashTable::removeNode(Node* node)
{
    // Calculate bucket index from node's stored hash (12-bit mask)
    uint bucketIndex = *(uint*)((int)node + 0x34) & 0xfff;
    Node* current = *(Node**)((int)this + bucketIndex * 4);  // bucket head
    Node* previous = 0;
    int result = 1;  // failure default

    if (current != 0) {
        // Traverse the singly linked chain
        Node* walker = current;
        while (walker != node) {
            previous = walker;
            walker = *(Node**)((int)walker + 0x38);  // next pointer
            if (walker == 0) {
                return result;  // node not found
            }
        }
        // Found the node: unlink it
        if (previous != 0) {
            *(Node**)((int)previous + 0x38) = *(Node**)((int)walker + 0x38);
        } else {
            *(Node**)((int)this + bucketIndex * 4) = *(Node**)((int)walker + 0x38);
        }
        // Decrement total element count (stored after bucket array at +0x4000)
        *(int*)((int)this + 0x4000) = *(int*)((int)this + 0x4000) - 1;
        result = 0;  // success
    }
    return result;
}