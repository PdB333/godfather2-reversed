// FUNC_NAME: ListManager::addEntry

// 0x008a0d20: Adds an entry (with intrusive node at +0x48) to an intrusive list (head at this+0x1c).
// Internal helper using a temporary stack-based node pointer for list insertion.
void __thiscall ListManager::addEntry(ListManager* this, Entry* entry) {
    // Intrusive node inside entry (offset 0x48)
    ListNode* node = (entry != nullptr)
        ? reinterpret_cast<ListNode*>(reinterpret_cast<char*>(entry) + 0x48)
        : nullptr;

    uint32_t savedNext = 0; // placeholder for original next pointer

    // Prepare node for insertion: save its current next, then set next to point to
    // the local node pointer variable (a stack‑based dummy for use by listAdd).
    if (node != nullptr) {
        savedNext = node->next; // actually storing offset +4 (next)
        node->next = reinterpret_cast<ListNode*>(&node); // self‑reference hack
    }

    // Transfer the node (via stack pointer) into the list at this+0x1c.
    listAdd(reinterpret_cast<ListNode*>(reinterpret_cast<char*>(this) + 0x1c), &node);

    // Cleanup: after insertion, the node pointer is usually cleared by listAdd,
    // so this branch is typically dead; kept as a safeguard.
    if (node != nullptr) {
        nodeRemove(&node); // release any leftover state
    }
}