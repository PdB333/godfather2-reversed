// FUNC_NAME: updateEntityLinkedList
// Function at 0x005313a0: Iterates over a global linked list of entities, calling a process function on each.
// Global DAT_01194a6c is head pointer. Each node has a next pointer at offset +0x10.

// Assume node structure with a next pointer at +0x10.
struct ListNode {
    // ... other data ...
    ListNode* next; // offset +0x10
};

// Global head of list
extern ListNode* g_pEntityListHead; // formerly DAT_01194a6c

// External process function called on each node
void processEntityNode(ListNode* node); // formerly FUN_005326c0

void updateEntityLinkedList(void)
{
    ListNode* current = g_pEntityListHead; // iVar1 initialized from global
    if (current != 0) {
        do {
            processEntityNode(current);
            current = current->next; // iVar1 = *(int *)(iVar1 + 0x10)
        } while (current != 0);
    }
    return;
}