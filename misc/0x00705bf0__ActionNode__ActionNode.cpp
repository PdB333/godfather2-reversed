// FUNC_NAME: ActionNode::ActionNode
void __thiscall ActionNode::ActionNode(ActionNode* this, int params) {
    // VTable pointer at offset 0
    this->vtable = &PTR_FUN_00d6102c;

    // Extract the node to insert after from params + 4
    ActionNode* insertAfter = *(ActionNode**)(params + 4);
    this->prev = insertAfter;                 // +0x04: previous pointer
    this->next = nullptr;                     // +0x08: next pointer

    if (insertAfter != nullptr) {
        // Copy the existing next pointer to our next
        this->next = reinterpret_cast<ActionNode*>(*(int*)((int)insertAfter + 4));
        // Set the existing node's next to point to our prev field (unusual linked list pattern)
        *(int**)((int)insertAfter + 4) = reinterpret_cast<int*>(&(this->prev));
    }

    // Copy two data words from the initialization structure
    this->data1 = *(int*)(params + 0xc);      // +0x0c
    this->data2 = *(int*)(params + 0x10);     // +0x10
}