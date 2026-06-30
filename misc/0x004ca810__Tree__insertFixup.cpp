// FUNC_NAME: Tree::insertFixup
// Function at 0x004ca810: Inserts a node into a red-black tree and rebalances.
// Parameters:
//   output[2] – receives (parent, node) pair after fixup
//   z – node being inserted (must be non-nil)
//   zParent – parent of z (or nil if root)
//   nil – sentinel node (same as this->nil)
//   y – existing node for comparison (e.g., uncle)
void __thiscall Tree::insertFixup(int *output, Node *z, Node *zParent, Node *nil, Node *y) {
    Node *root = **(Node ***)(this + 0x1c); // null sentinel from tree root pointer

    // Validate parameters: z must be the caller's this pointer
    if (z == nullptr || z != this) {
        assert_fail();
    }

    // If both zParent and y are the sentinel, initialize an empty tree
    if (zParent == root && y == root) {
        freeNode(*(void **)(*(int *)(this + 0x1c) + 4));
        *(int *)(*(int *)(this + 0x1c) + 4) = *(int *)(this + 0x1c); // nil->next = nil
        *(int *)(this + 0x20) = 0; // tree color flag (0 = black? or height)
        *(int *) *(int *)(this + 0x1c) = *(int *)(this + 0x1c); // nil->prev = nil
        *(int *)(*(int *)(this + 0x1c) + 8) = *(int *)(this + 0x1c); // nil->parent = nil
        output[1] = root;
        output[0] = this; // tree node itself
        return;
    }

    // Main rebalance loop
    while (true) {
        if (z == nullptr || z != y) {
            assert_fail();
        }
        if (zParent == nil) break; // reached root (nil parent)
        rotate();
        modifyNode(this, /* local_8 */, z, zParent); // adjust colors/links
    }

    output[1] = zParent; // final parent
    output[0] = z; // inserted node
}