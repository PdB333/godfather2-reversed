// FUNC_NAME: Node::moveToFront
// Function address: 0x006223e0
// This function removes the current node (this) from its current list and reinserts it at the front of the list specified by param_2.
// The node structure has fields: next (+0x00), prev (+0x04), listParent (+0x08), and a flag at +0x25.
// param_2 is a pointer to a ListManager which contains a pointer to a List object at +0x1c.
// The List object has a head pointer at +0x04.

struct Node {
    Node* next;          // +0x00
    Node* prev;          // +0x04
    Node* listParent;    // +0x08 (pointer to the list this node belongs to, or some other node)
    char field_0x25;     // +0x25 (flag indicating if node is active/in list)
};

struct List {
    char pad_0x00[4];    // +0x00 (unknown)
    Node* head;          // +0x04
};

struct ListManager {
    char pad_0x00[0x1C]; // +0x00 to +0x1B
    List* listPtr;       // +0x1C (pointer to a List)
};

void __thiscall Node::moveToFront(Node* this, ListManager* listMgr) {
    Node* oldNext = this->next;          // iVar1 = *param_1
    this->next = oldNext->listParent;    // *param_1 = *(int *)(iVar1 + 8)

    // If the node after oldNext's listParent has its flag cleared, update its prev pointer
    if (oldNext->listParent->field_0x25 == '\0') {
        oldNext->listParent->prev = this; // *(int **)(*(int *)(iVar1 + 8) + 4) = param_1
    }

    oldNext->prev = this->prev;          // *(int *)(iVar1 + 4) = param_1[1]

    // Check if this node is the head of the list pointed by listMgr->listPtr
    if (this == listMgr->listPtr->head) {
        listMgr->listPtr->head = oldNext; // *(int *)(*(int *)(param_2 + 0x1c) + 4) = iVar1
        oldNext->listParent = this;       // *(int **)(iVar1 + 8) = param_1
        this->prev = oldNext;             // param_1[1] = iVar1
        return;
    }

    Node* prevNode = this->prev;          // piVar2 = (int *)param_1[1]
    if (this == prevNode->listParent) {   // if this is the listParent of the previous node
        prevNode->listParent = oldNext;   // piVar2[2] = iVar1
        oldNext->listParent = this;       // *(int **)(iVar1 + 8) = param_1
        this->prev = oldNext;             // param_1[1] = iVar1
        return;
    }

    // Otherwise, update the previous node's next pointer
    prevNode->next = oldNext;             // *piVar2 = iVar1
    oldNext->listParent = this;           // *(int **)(iVar1 + 8) = param_1
    this->prev = oldNext;                 // param_1[1] = iVar1
    return;
}