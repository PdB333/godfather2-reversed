// FUNC_NAME: ListNode::insertBefore
// Address: 0x006e9170
// Purpose: Inserts this node before the node embedded at offset 0x48 in targetObj.
// If targetObj is null, the node is unlinked and its next pointer cleared.
// Node memory layout:
//   +0x00: next (ListNode*)
//   +0x04: prev (ListNode*)

struct ListNode {
    ListNode* next;
    ListNode* prev;
};

// External helper: removes a node from its current linked list
extern void listUnlink(ListNode* node); // called at 0x004daf90

ListNode* __thiscall ListNode::insertBefore(ListNode** thisPtr, ListNode* targetObj) {
    // Parameter ordering: param_1 = this (as pointer to the object's first field)
    // param_2 = targetObj (pointer to an object that contains a ListNode at offset 0x48)
    // We cast thisPtr to ListNode* for clarity.
    ListNode* self = (ListNode*)thisPtr;
    ListNode* targetNode = nullptr;

    if (targetObj != nullptr) {
        // Advance to the embedded node at offset 0x48 (72 bytes = 18 int slots)
        // Because targetObj is a pointer to an object that has a ListNode member at this offset.
        // In the decompiled code, param_2 = targetObj + 0x48 (bytes), so cast accordingly.
        targetNode = reinterpret_cast<ListNode*>(reinterpret_cast<char*>(targetObj) + 0x48);
    }

    // Only update if the node is not already before the target
    if (self->next != targetNode) {
        if (self->next != nullptr) {
            // Remove self from its current list
            listUnlink(self);
        }
        // Set new next pointer
        self->next = targetNode;

        if (targetNode != nullptr) {
            // Insert self before targetNode:
            // self->prev becomes targetNode->prev
            self->prev = targetNode->prev;
            // targetNode->prev becomes self
            targetNode->prev = self;
        }
    }

    return reinterpret_cast<int*>(self);
}