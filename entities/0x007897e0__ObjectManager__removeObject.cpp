// FUNC_NAME: ObjectManager::removeObject
// Function at 0x007897e0
// Removes an object (param_2) from the manager's list and releases the manager's handle.

void __thiscall ObjectManager::removeObject(void* this, void* obj) {
    // obj is expected to have a list node at offset 0x48 (like Object::listNode)
    int* node;  // Points to the list node within obj (obj + 0x48)
    int oldNext;

    // Guard object – not used, possibly for stack unwinding (vtable?).
    // Not shown because it has no effect.

    if (obj == 0) {
        node = 0;
    } else {
        node = reinterpret_cast<int*>(reinterpret_cast<char*>(obj) + 0x48);
    }

    // Intrusive singly‑linked list removal.
    // The node at offset +0x4 holds the 'next' pointer.
    // We save it, then set it to point back to the node's own location (marks removal).
    if (node != 0) {
        oldNext = node[1];               // node->next (offset +0x04)
        reinterpret_cast<int**>(node)[1] = &node; // Mark as removed: next = &node
    }

    // Release the handle stored in 'this' at offset 0x7C.
    // The handle is a refcounted pointer (e.g., to the containing object).
    Handle* handle = reinterpret_cast<Handle*>(reinterpret_cast<char*>(this) + 0x7C);
    FUN_00408a00(handle, 0);             // releaseHandle(handle, 0)

    // If the node existed, free the entire obj (the node is embedded).
    if (node != 0) {
        FUN_004daf90(&node);             // deleteNode(&node) – also sets node to null
    }
}