// FUNC_NAME: NodeList::insertNodeBefore
// Address: 0x00463560
// This function inserts a new node before a given node in a doubly linked list.
// It uses a custom allocator stored in the list object.
// The list structure: 
//   +0x00: Node* head
//   +0x04: Node* tail (unused in this function)
//   +0x08: int count
//   +0x0C: void* allocBuffer
//   +0x10: AllocFunc allocFunc (function pointer taking size and buffer)
// Node layout (12 bytes):
//   +0x00: void* data
//   +0x04: Node* prev
//   +0x08: Node* next

class NodeList {
public:
    struct Node {
        void* data;       // +0x00
        Node* prev;       // +0x04
        Node* next;       // +0x08
    };

    Node* head;           // +0x00
    Node* tail;           // +0x04
    int count;            // +0x08
    void* allocBuffer;    // +0x0C
    // AllocFunc is a pointer to a function with signature: Node* (int size, void* buffer)
    Node* (*allocFunc)(int, void*); // +0x10

    // This method corresponds to the decompiled function.
    // ECM: this pointer in ESI, nodeToInsertBefore pointer in EAX (dereferenced to get node)
    // Data to store in new node is on stack (unaff_retaddr in decompilation)
    // Returns the new node through outParam.
    __thiscall void insertNodeBefore(Node* node, void* data, Node** outNewNode);
};

void __thiscall NodeList::insertNodeBefore(Node* node, void* data, Node** outNewNode) {
    Node* head = this->head;              // Dereference this (ESI[0] in asm)
    Node* previous = node->prev;          // Not used directly in this function, but for linking
    Node* allocBuffer = this->allocBuffer;// ESI[3]
    if (allocBuffer == nullptr) {
        allocBuffer = &staticAllocBuffer; // Global fallback buffer (DAT_01218a14)
    }
    Node* newNode = this->allocFunc(0xC, allocBuffer); // Allocate 12 bytes
    if (newNode != nullptr) {
        newNode->data = data;             // *puVar3 = *unaff_retaddr
        newNode->prev = nullptr;          // +0x04 = 0
        newNode->next = nullptr;          // +0x08 = 0
    }
    if (node == head) {
        // Insert at head
        newNode->prev = nullptr;          // new node's prev = null
        this->head = newNode;             // head = new node
        newNode->next = node;             // link new -> old head
        if (node != nullptr) node->prev = newNode; // old head's prev = new node
        this->count++;                    // increment count
        *outNewNode = newNode;
        return;
    }
    // Insert before node (not head)
Node* nodePrev = node->prev;              // iVar2 = node->next? Wait, careful: code uses iVar1+8 which is node->next? Actually in code: iVar2 = *(int *)(iVar1 + 8); iVar1 is the node pointer (from *in_EAX). So node->next? But that would be linking wrong. Let's re-evaluate:

// Actually the decompiled code:
// iVar2 = *(int *)(iVar1 + 8);
// puVar3[2] = iVar2;
// *(undefined4 **)(iVar2 + 4) = puVar3;
// puVar3[1] = iVar1;
// *(undefined4 **)(iVar1 + 8) = puVar3;

// So node->next (offset 8) is saved. Then newNode->next = node->next; then node->next->prev = newNode; then newNode->prev = node; then node->next = newNode.
// This inserts newNode AFTER node, not before. The condition "if (node == head)" does insert at head (newNode becomes head, link to node as next). So the function actually inserts AFTER the given node, except when node is head in which case it inserts at head? That's inconsistent.

// The comparison (node == head) leading to head insertion where newNode becomes head and node becomes its next makes newNode inserted BEFORE the original head (i.e., at front). That is insertion before the head. For non-head case, it inserts after node. So the function name should be "insertBefore" only when node is head? That seems buggy.

// To match exactly, we'll replicate the logic as in original, even if odd.

    Node* nodeNext = node->next;          // offset 8 = next
    newNode->next = nodeNext;             // puVar3[2] = iVar2
    nodeNext->prev = newNode;             // nodeNext->prev = newNode
    newNode->prev = node;                 // puVar3[1] = node
    node->next = newNode;                 // node->next = newNode
    this->count++;                        // increment count
    *outNewNode = newNode;                // store output
    return;
}
// Note: The original code also set newNode->prev = iVar1 (node) and newNode->next = iVar2 (nodeNext), then linked both ways.
// The initialization block sets newNode->data = data, newNode->prev = 0, newNode->next = 0. These are set before insertion logic, then overwritten appropriately.
// The allocator call is: this->allocFunc(0xC, allocBuffer). The first argument is size (12), second is buffer.
// The decompiler used unaff_retaddr for the data pointer, which we've reinterpreted as the second function parameter.
// We assume the function is __thiscall with this in ESI, node parameter in EAX (dereferenced), data on stack.
// Since Ghidra didn't capture the full signature, we adjust.