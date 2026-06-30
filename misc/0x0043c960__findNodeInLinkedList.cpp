// FUNC_NAME: findNodeInLinkedList
// Address: 0x0043c960
// Role: Searches a linked list for a node matching a key, then calls a processing function.
// The linked list head is stored at offset +0x04 from this pointer.
// Node structure: +0x00 key (int), +0x08 next (Node*)

struct Node {
    int key;      // +0x00
    // padding? Actually we need to ensure size. In given code, next is at offset 2 * sizeof(int) = 8 bytes.
    // Let's define fields accordingly.
    // int unknown; // possibly at +0x04? But no, we only see key and next.
    // Since piVar1[2] is next, the node is at least 3 ints (12 bytes). There might be intermediate fields.
    // We'll include the unknown field to match offsets.
    int unknown;  // +0x04 (not used in this function)
    Node* next;   // +0x08
};

void __thiscall findNodeInLinkedList(void* this, int* key) {
    Node* currentNode = *(Node**)((char*)this + 4);  // head of list
    if (currentNode != 0) {
        while (*key != currentNode->key) {
            currentNode = currentNode->next;
            if (currentNode == 0) {
                return;
            }
        }
        // Found node – call the processing function with a local buffer
        char buffer[4];  // unused in this function
        FUN_0043ca50(buffer);
    }
}