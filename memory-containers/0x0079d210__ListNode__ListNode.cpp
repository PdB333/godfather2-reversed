// FUNC_NAME: ListNode::ListNode
// Address: 0x0079d210
// Role: Constructor for a list node that copies data from a source node and inserts itself into two linked lists.
// The insertion logic updates only the "prev" pointer of the next node, suggesting a singly linked list or a special list structure.

void __thiscall ListNode::ListNode(ListNode* thisNode, const ListNode* sourceNode)
{
    // Set vtable pointer
    thisNode->vtable = &PTR_FUN_00d6a7a8;

    // First list insertion: copy next pointer from source, then adjust prev
    ListNode* next1 = sourceNode->next1;
    thisNode->next1 = next1;
    thisNode->prev1 = 0;
    if (next1 != 0) {
        thisNode->prev1 = next1->prev1;          // Save old prev of next node
        next1->prev1 = &thisNode->next1;         // Update next node's prev to point to this node's next field
    }

    // Second list insertion: similar logic
    ListNode* next2 = sourceNode->next2;
    thisNode->next2 = next2;
    thisNode->prev2 = 0;
    if (next2 != 0) {
        thisNode->prev2 = next2->prev2;
        next2->prev2 = &thisNode->next2;
    }

    // Copy data fields from source (offsets relative to sourceNode)
    // Offsets: +0x14 (double), +0x1c (int), +0x20 (double), +0x28 (int), +0x2c..+0x44 (ints)
    thisNode->dataDouble1 = sourceNode->dataDouble1;   // +0x14
    thisNode->dataInt1    = sourceNode->dataInt1;       // +0x1c
    thisNode->dataDouble2 = sourceNode->dataDouble2;   // +0x20
    thisNode->dataInt2    = sourceNode->dataInt2;       // +0x28
    thisNode->dataInt3    = sourceNode->dataInt3;       // +0x2c
    thisNode->dataInt4    = sourceNode->dataInt4;       // +0x30
    thisNode->dataInt5    = sourceNode->dataInt5;       // +0x34
    thisNode->dataInt6    = sourceNode->dataInt6;       // +0x38
    thisNode->dataInt7    = sourceNode->dataInt7;       // +0x3c
    thisNode->dataInt8    = sourceNode->dataInt8;       // +0x40
    thisNode->dataInt9    = sourceNode->dataInt9;       // +0x44
}