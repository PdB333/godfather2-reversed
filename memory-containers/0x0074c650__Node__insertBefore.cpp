// FUNC_NAME: Node::insertBefore
// Function at 0x0074c650: Inserts this node into a doubly linked list before a target node.
// The target node is embedded at offset 0x48 within the given container object.
// If container is null, this node is unlinked (set to null).

struct ListNode {
    ListNode* next;  // +0x00
    ListNode* prev;  // +0x04
};

struct ContainerObject {
    // ... other members ...
    ListNode listNode;  // +0x48
};

// Note: This function is a member of ListNode.
int* __thiscall ListNode::insertBefore(int* thisPtr, int* containerPtr)
{
    ListNode* self = reinterpret_cast<ListNode*>(thisPtr);
    ListNode* targetNode = nullptr;

    if (containerPtr != 0) {
        // The actual node to insert before is at offset 0x48 in the container.
        targetNode = reinterpret_cast<ListNode*>(reinterpret_cast<char*>(containerPtr) + 0x48);
    }

    // Unlink if we are already pointing somewhere else.
    if (self->next != targetNode) {
        if (self->next != nullptr) {
            // Callee at 0x004daf90 likely removes this node from its previous list.
            FUN_004daf90(reinterpret_cast<int*>(self));
        }
        self->next = targetNode;
        if (targetNode != nullptr) {
            // Update the previous pointer of the target node to point back to self.
            self->prev = targetNode->prev;
            targetNode->prev = self;
        }
    }
    return reinterpret_cast<int*>(self);
}