// FUNC_NAME: ListManager::moveNodeToFront
// Address: 0x004ca5a0
// This function moves a node to the front of a doubly linked list managed by a list descriptor.
// param_1: pointer to the node (this) - Node structure
// param_2: pointer to a ListDescriptor (int*)
// Node fields:
//   +0x00: next pointer (or some linked list pointer)
//   +0x04: prev pointer (or back pointer)
//   +0x08: some auxiliary pointer (possibly parent list link)
// ListDescriptor fields:
//   +0x1c: pointer to a ListHead structure with:
//       +0x00: first node?
//       +0x04: last node? (compared to node)
// The byte @0x15 in the structure pointed to by node->field_8 is a flag.

struct Node {
    int* field_0;   // +0x00
    int* field_4;   // +0x04
    int* field_8;   // +0x08 (often points to a list or container)
    // ... other fields not used here
};

struct ListHead {
    int* first; // +0x00
    int* last;  // +0x04 (or vice versa)
};

struct ListDescriptor {
    // many fields...
    ListHead* head; // +0x1c
};

void __thiscall ListManager::moveNodeToFront(Node* node, ListDescriptor* list) {
    Node* someNode;      // iVar1
    Node** prevPtr;      // piVar2

    // Save the node's field_0 (the current "next" or "link")
    someNode = node->field_0;

    // Replace node->field_0 with whatever someNode->field_8 points to
    // (effectively removing node from its current chain?)
    node->field_0 = someNode->field_8;

    // If the byte at offset 0x15 of the object pointed to by someNode->field_8 is zero
    if (((char*)(someNode->field_8))[0x15] == '\0') {
        // Then set that object's offset +0x04 to point back to node
        // (maybe restoring a parent/child link)
        *((Node***)(someNode->field_8) + 1) = &node;
    }

    // Update someNode->field_4 to be node->field_4 (the previous node)
    someNode->field_4 = node->field_4;

    // Check if node is the head of the list (compared to list->head->last)
    if (node == list->head->last) {
        // Update list head to point to someNode
        list->head->last = someNode;

        // Link someNode->field_8 to node
        someNode->field_8 = node;

        // Set node's back pointer to someNode
        node->field_4 = someNode;
        return;
    }

    // Otherwise, get node's previous node
    prevPtr = (Node**)node->field_4;

    // If node is the "next" of its previous (i.e., prevPtr[2] == node)
    if (node == prevPtr[2]) {
        // Update previous's field_8 to someNode
        prevPtr[2] = someNode;
    } else {
        // Otherwise update previous's first field to someNode
        *prevPtr = someNode;
    }

    // Common tail: link someNode->field_8 to node and node's back pointer to someNode
    someNode->field_8 = node;
    node->field_4 = someNode;
}