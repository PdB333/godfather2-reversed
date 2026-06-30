// FUNC_NAME: RBTree::insertNode
void __thiscall RBTree::insertNode(int *outNode, int parent, int z, int grandparent, int y) {
    // this +0x1c: pointer to sentinel node (nil)
    int nilPtr = *(int *)(*(int *)(this + 0x1c)); // sentinel's left child (self) – typically nil itself
    int sentinel = *(int *)(this + 0x1c);         // sentinel node pointer

    // Assert: parent must be valid and point to this tree? (some sort of validation)
    if ((parent == 0) || (parent != (int)this)) {
        FUN_00b97aea(); // assert failure (likely __debugbreak)
    }

    // If z is the sentinel (empty tree), perform initialization
    if (z == nilPtr) {
        int sentinel2 = *(int *)(this + 0x1c);
        if ((grandparent == 0) || (grandparent != (int)this)) {
            FUN_00b97aea();
        }
        if (y == sentinel2) {
            // Set up root and sentinel self-pointers
            FUN_004cae20(*(undefined4 *)(sentinel2 + 4)); // likely set color of root?
            *(int *)(sentinel2 + 4) = sentinel2;
            *(int *)(this + 0x20) = 0;           // clear some flag (maybe root count?)
            *(undefined4 *)*sentinel2 = *(undefined4 *)(sentinel2);
            *(int *)(sentinel2 + 8) = sentinel2;
            // Output: outNode[1] = root, outNode[0] = this (tree)
            outNode[1] = *(int *)(sentinel2);    // left child of sentinel (root)
            *outNode = (int)this;
            return;
        }
    }

    // Rebalancing loop (insertion fix-up)
    while (true) {
        if ((parent == 0) || (parent != grandparent)) {
            FUN_00b97aea();
        }
        if (z == y) break;
        FUN_004cab50();          // likely rotation (left or right)
        FUN_004c9bf0(this, (undefined (*) [8])local_8, parent, z); // fixup routine
    }

    // Output the final node pair
    outNode[1] = z;
    *outNode = parent;
    return;
}