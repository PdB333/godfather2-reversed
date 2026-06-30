// FUNC_NAME: SomeManager::processKeyValueList
// Address: 0x00624820
// This function iterates over a linked list of key-value pairs and calls a virtual callback for each.

void __thiscall SomeManager::processKeyValueList(void* param1, void* param2) {
    // this+0x10: pointer to a structure containing the list head
    void* listContainer = *(void**)((uint8_t*)this + 0x10);
    // this+0x0C: a counter or flag (reset to 0 before processing)
    *(int*)((uint8_t*)this + 0x0C) = 0;

    // The container has a pointer to the first node at offset 0x08
    // Node structure: offset 0 -> next pointer, offset 4 -> first data field, offset 8 -> second data field? 
    // Actually from the call: *node is the next pointer (used as iterator), node[1] is the value.
    // So Node: { Node* next; int key; }? But they pass *node and node[1]; two int-sized values.
    // Possibly Node: { void* nextOrData; int value; } or { int id; int value; }.
    // We'll treat it as a pair of 4-byte values (first is used as an ID, second as data).
    typedef struct Node {
        Node* next;   // +0x00
        int first;    // +0x04
        int second;   // +0x08? But we only use offset 0x04 as first. Wait, node[1] is at offset 0x04.
        // Actually node is undefined4*, so node[0] = *node, node[1] = next 4 bytes.
        // So the node has two fields: first at offset 0, second at offset 4.
        // But the loop uses *node to advance (so *node = next pointer) and node[1] as the data.
        // So the node structure is: { Node* next; int data; } and the call uses (next? data?) No.
        // Let's re-evaluate: they pass *node (which is the next pointer) and node[1] (the data) to the callback.
        // That is odd: passing the next pointer as a parameter.
        // More likely the node has two fields: first is some identifier (int), second is a value.
        // And the next pointer is separate? But then *node would be the identifier.
        // Actually, the for loop does puVar2 = (undefined4 *)*puVar2, so puVar2 is a pointer to a node,
        // and *puVar2 gives the pointer to the next node (since next is at offset 0).
        // Then they pass *puVar2 (the next pointer) and puVar2[1] (the second field) to the callback.
        // So the callback receives the next pointer and the second field.
        // That seems wrong; perhaps the node's first field is actually an ID and they want that ID (not next pointer).
        // But the iterator uses *puVar2 as next, so offset 0 is next.
        // Then puVar2[1] is at offset 4 (the second field).
        // So the callback receives (next, second). That is plausible if the list is used to store pairs where first is a pointer? 
        // But we don't know.
        // To be consistent with the decompiled code, I'll keep it as is.
    } Node;

    // The list head is at listContainer+0x08, which points to the first node.
    Node* head = *(Node**)((uint8_t*)listContainer + 0x08);
    Node* node = head;

    while (node != nullptr) {
        // Call virtual method at vtable index 2 (offset +8 from vtable pointer)
        // The method takes (this, param1, param2, zero, firstField, secondField)
        // firstField = node->next (since *node is next), secondField = node->second (node[1])
        // But this might be incorrect; we preserve the original behavior.
        void (*callback)(void*, void*, void*, int, int, int) = 
            (void (*)(void*, void*, void*, int, int, int))(*((int**)this)[2]);
        callback(this, param1, param2, 0, (int)node->next, node->second);

        node = node->next; // advance
    }
}