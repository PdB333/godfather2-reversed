// FUNC_NAME: NodeList::pushFront
void __fastcall NodeList::pushFront(int thisPtr) {
    // this object: NodeList manager
    // offset +0x18: pointer to list control block (ListControl)
    ListControl* listCtrl = *(ListControl**)(thisPtr + 0x18);

    // listCtrl->head is at offset +0x04 (current head node)
    Node* oldHead = listCtrl->head;

    // Allocate/initialize a new node. Parameters: listCtrl, oldHead, and an implicit EAX register value.
    // (in_EAX is likely an additional parameter such as a creation flag or node type)
    Node* newNode = (Node*)FUN_004cf1f0(listCtrl, oldHead, in_EAX);

    // Post-init hook (e.g., debug trace or synchronization)
    FUN_004cf240();

    // Update list head to point to new node
    listCtrl->head = newNode;

    // The new node's field at offset +0x04 stores a pointer to &listCtrl->head (set by FUN_004cf1f0).
    // Dereference and set the head pointer to newNode (redundant but enforces correct state).
    *newNode->pHead = newNode;
}

// Supporting types (hypothetical layout)
struct ListControl {
    /* +0x00: unknown */
    Node* head; // +0x04
};

struct Node {
    /* +0x00: data (size unknown) */
    Node** pHead; // +0x04 – points to the head pointer of the owning list
};