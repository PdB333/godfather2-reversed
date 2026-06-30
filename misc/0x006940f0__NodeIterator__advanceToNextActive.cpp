// FUNC_NAME: NodeIterator::advanceToNextActive
void __fastcall NodeIterator::advanceToNextActive() {
    // param_1 is 'this' (ecx), struct with:
    //   +0x00: int initialized (bool)
    //   +0x04: Node* current
    // Node struct:
    //   +0x00: Node* next (sibling)
    //   +0x04: Node* parent (or previous sibling for list)
    //   +0x08: Node* child (first child or extra pointer)
    //   +0x25: uint8 active (0 = inactive, non-zero = active)

    if (initialized == 0) {
        assertError(); // FUN_00b97aea
    }

    Node* cur = current;
    if (cur->active == 0) {
        Node* child = cur->child;  // +0x08
        if (child->active != 0) {
            // Subtree exists with active nodes: walk up via parent chain
            Node* parent = cur->parent; // +0x04
            while (parent->active == 0 && (cur == parent->child)) {
                current = parent;
                parent = parent->parent;
            }
            current = parent;
            return;
        }
        // No active children: skip inactive siblings
        Node* it = child; // actually child is first sibling? No, child holds pointer to a node; traverse its siblings
        Node* nextSibling = (Node*)it->next; // +0x00
        while (nextSibling->active == 0) {
            it = nextSibling;
            nextSibling = (Node*)nextSibling->next;
        }
        current = it;
        return;
    }
    // Current node is active – should not happen (error)
    assertError();
}