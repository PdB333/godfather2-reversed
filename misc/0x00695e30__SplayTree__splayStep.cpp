// FUNC_NAME: SplayTree::splayStep
void __thiscall SplayTree::splayStep(SplayTree* thisTree, SplayTreeNode** outPair, SplayTreeNode* leftNode, int leftKey, SplayTreeNode* rightNode, int rightKey) {
    int rootValue = **(int**)((int)thisTree + 4);

    // Debug assertion: leftNode must be null or equal to thisTree
    if (leftNode != 0 && leftNode != thisTree) {
        __debugbreak(); // FUN_00b97aea
    }

    if (rightKey == rootValue) {
        int* currentPtr = *(int**)((int)thisTree + 4);
        // leftNode must be null or equal to thisTree
        if (rightNode != 0 && rightNode != thisTree) {
            __debugbreak();
        }
        // rightKey must equal rootValue (already checked)
        if (rightKey == rootValue) {
            // Call rotation helper on the stored pointer
            splayRotate(*(undefined4*)(*(int*)((int)thisTree + 4) + 4));

            // Rewire parent pointers to make the root point to itself (circular)
            *(int*)(*(int*)((int)thisTree + 4) + 4) = *(int*)((int)thisTree + 4);
            *(undefined4*)((int)thisTree + 8) = 0;
            *(undefined4*)*(undefined4*)((int)thisTree + 4) = *(undefined4*)((int)thisTree + 4);
            *(int*)(*(int*)((int)thisTree + 4) + 8) = *(int*)((int)thisTree + 4);

            rootValue = **(int**)((int)thisTree + 4);
            outPair[0] = thisTree;
            outPair[1] = rootValue;
            return;
        }
    }

    // Iterative splay step: traverse until keys match
    while (true) {
        // leftNode must be null or equal to rightNode
        if (leftNode != 0 && leftNode != rightNode) {
            __debugbreak();
        }
        if (leftKey == rightKey) break;

        // Perform intermediate rotation and comparison
        splayIntermediate();
        splayCompare(&leftNode, leftNode, rightKey);
    }

    outPair[0] = leftNode;
    outPair[1] = rightKey;
    return;
}