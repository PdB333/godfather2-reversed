// FUNC_NAME: ListNode::resetToSelf
void __thiscall ListNode::resetToSelf() {
    // Remove this node from its current list by unlinking the old next pointer
    FUN_008ed090(this->next);

    // Make this node a single-element circular list
    this->next = this;
    this->prev = this;
    this->pOwner = this;  // +0x08 field (possibly list head or container pointer)

    // Clear an additional field? The code sets *(this + 8) = 0 before setting pOwner = this, so it's effectively the same.
    // But to match the original: first clear, then set to this.
    this->pOwner = this;  // already set above, but the original order: clear then assign.
    // Actually the decompiler shows two separate stores, so we keep both.
}
```