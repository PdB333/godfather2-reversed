// FUNC_NAME: TreeIterator::advanceNextValid
// Function at 0x00694060: Advances an iterator to the next node in a binary tree that has the active flag (at +0x25) set.
// Parameter: int *param_1 – pointer to iterator structure: [0] = some sentinel/flag, [4] = current TreeNode pointer.
// TreeNode layout: [0] left child, [4] right child, [8] parent, [+0x25] active flag (char).

void __fastcall TreeIterator::advanceNextValid(int *iterator) {
    char flag;
    TreeNode *node, *parent, *child, *temp;

    // If sentinel flag is zero, trigger assertion / error handler
    if (*iterator == 0) {
        errorHandler(); // FUN_00b97aea
    }

    node = (TreeNode *)iterator[1];

    // If current node is not active (flag == 0)
    if (*(char *)((int)node + 0x25) == '\0') {
        // Try to find an active ancestor by climbing up the tree via parent links
        parent = (TreeNode *)*(int *)node; // parent = node->parent? Actually dereference node: node->left? Might be parent? Need to interpret.
        // The code uses *node (offset 0) as a pointer to another node.
        if (*(char *)((int)parent + 0x25) == '\0') {
            // Continue climbing: from parent->parent (offset 8)?
            child = (TreeNode *)*(int *)((int)parent + 8); // parent->parent? Or parent->right?
            flag = *(char *)((int)child + 0x25);
            temp = (TreeNode *)*(int *)(child + 8); // child->parent? 

            while (flag == '\0') {
                flag = *(char *)((int)*((int *)child + 8) + 0x25); // check child's parent's flag
                temp = child;
                child = (TreeNode *)*((int *)child + 8); // child = child->parent
            }
            // Found an ancestor with active flag
            iterator[1] = (int)temp; // set current to the node just before the active one? Actually iVar3 holds the node that had active flag? Need more context.
            return;
        }

        // Move to the right child (offset 4) and walk down left children?
        node = (TreeNode *)*(int *)((int)node + 4); // node->right? Or node->parent? Actually piVar2[1] is offset 4.
        flag = *(char *)((int)node + 0x25);
        while (flag == '\0' && iterator[1] != (int)node) {
            // Move further to the right until we find active or loop back
            iterator[1] = (int)node;
            node = (TreeNode *)*(int *)((int)node + 4); // follow right child? 
            flag = *(char *)((int)node + 0x25);
        }

        if (*(char *)(iterator[1] + 0x25) != '\0') {
            errorHandler(); // For some reason assert if current becomes active? Actually condition is if current becomes active, error.
            return;
        }
        iterator[1] = (int)node; // Set current to the node we stopped at
    } else {
        // Current node is active; move to its left child (offset 8?) Actually piVar2[2] is offset 8.
        temp = (TreeNode *)*(int *)((int)node + 8);
        iterator[1] = (int)temp;
        if (*(char *)((int)temp + 0x25) != '\0') {
            errorHandler(); // If left child (or some child) is active, error? Unclear.
            return;
        }
    }
    return;
}