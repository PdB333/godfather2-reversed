// FUNC_NAME: moveListNodeAfter
// Function at 0x004ca4f0: Moves a node to be immediately after another node in a doubly-linked list.
// The node is first detached from its current position, then inserted after the specified 'afterNode'.
// The list is intrusive (nodes contain next/prev pointers). The list container holds a sentinel or head reference at offs +0x1c.
// Node layout:
// +0x00: next pointer
// +0x04: prev pointer
// +0x08: pointer to another list (child list or alternate chain)
// +0x15: flag byte (if 0, the node is not in the list? Used to update prev of the next node)
// Container layout:
// +0x1c: pointer to a struct that has at +0x04 a node pointer (likely head/sentinel)

struct ListNode {
    ListNode* next;      // +0x00
    ListNode* prev;      // +0x04
    ListNode* childList; // +0x08  (secondary list pointer)
    char     unknown[0x15 - 0x0C]; // padding? Actually offset 0x15 is inside unknown area
    char     flag;       // +0x15
};

struct ListContainer {
    char unknown[0x1c];
    void* headOrSentinel; // +0x1c, points to a struct that has a node pointer at +0x04
};

struct HeadNode {
    ListNode* node; // +0x04
};

void __thiscall moveListNodeAfter(ListNode* node, ListContainer* list) {
    ListNode* afterNode = node->childList;  // +0x08
    ListNode* nextAfter = afterNode->next;  // +0x00 from afterNode

    // Remove node from child list? Update node's childList to skip afterNode?
    node->childList = nextAfter; // +0x08

    // If the flag in afterNode's child list? Actually checks flag of the node that afterNode points to?
    if (afterNode->next->flag == 0) {
        afterNode->next->prev = node;
    }

    afterNode->prev = node->prev; // +0x04 of afterNode receives node's prev

    // Check if node is the head of the list (compare node with head->node)
    // headOrSentinel is at list+0x1c, then deref to get node pointer at +0x04
    ListNode* headNode = ((HeadNode*)list->headOrSentinel)->node;
    if (node == headNode) {
        // Update head to afterNode
        ((HeadNode*)list->headOrSentinel)->node = afterNode;
        afterNode->next = node;
        node->prev = afterNode;
        return;
    }

    // General case: check if node is the first node in its list? 
    // Actually node->prev points to the previous node; if node->prev->next == node, then node is not head
    // But the code checks: if (node == *node->prev) ??? That seems odd.
    // Actually piVar2 = *(int**)(param_1+4) -> prev of node.
    // Then if (param_1 == *piVar2) -> if node == node->prev->next? No, *piVar2 is the value at node->prev which is the next pointer of prev? Confusing.
    // Let's reinterpret: In a doubly linked list, node->prev points to the previous node.
    // The condition (node == *node->prev) would be checking if node->prev's next pointer is itself? Actually *node->prev dereferences the prev pointer to get the first field (next). So it checks if node == node->prev->next. That is true when node is the first node after the head?? 
    // Better to trust the decompiled logic and just write equivalent code with proper types.
    ListNode* prevNode = node->prev;
    if (node == prevNode->next) {
        // Then update prevNode's next to afterNode, i.e., replace node with afterNode in the list
        prevNode->next = afterNode;
        afterNode->next = node;
        node->prev = afterNode;
        return;
    }

    // General case: node is not at the beginning of its list, and not the head
    // Update prevNode's childList? Actually piVar2[2] = (int)piVar1 -> prevNode->childList = afterNode
    prevNode->childList = afterNode;
    afterNode->next = node;
    node->prev = afterNode;
    return;
}