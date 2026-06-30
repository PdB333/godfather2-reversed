// FUNC_NAME: TreeNode::rotateLeft
// Function at 0x00573fd0: Performs a left rotation on a binary tree node, updating the root pointer.
// The tree node uses fields: +0 height (int), +4 left child (int*), +8 right child (int*), +12 parent (int*).
// Parameters: param_1 (unused), param_2 (int** ppRoot), param_3 (int** ppResult).
// After rotation, *ppRoot and *ppResult both point to the new root (pivot).

void __fastcall TreeNode::rotateLeft(undefined4 param_1, int **ppRoot, int **ppResult)
{
    int *node = *ppRoot;                  // current root node
    int *pivot = *(int **)(node + 2);     // pivot = node->right (offset +8)
    int *oldLeft = *(int **)(node + 1);   // oldLeft = node->left (offset +4)

    // Node's right becomes pivot's parent (which is node itself initially, but we're about to change)
    *(int **)(node + 2) = *(int **)(pivot + 3); // node->right = pivot->parent (offset +12)

    // If pivot had a parent, update that parent's left child to point to node
    if (*(int **)(pivot + 3) != 0)
    {
        *(int **)(*(int **)(pivot + 3) + 1) = (int *)node; // pivot->parent->left = node
    }

    // Set pivot's parent to node
    *(int **)(pivot + 3) = (int *)node;

    // Set node's left to pivot
    *(int **)(node + 1) = (int *)pivot;

    // Recalculate height for node (field +0)
    int *nodeChildren[2];
    nodeChildren[0] = (int *)*(node + 1); // node->left
    nodeChildren[1] = (int *)*(node + 2); // node->right
    int nodeHeightLeft = (nodeChildren[0] != 0) ? *(int *)nodeChildren[0] : -1;
    int nodeHeightRight = (nodeChildren[1] != 0) ? *(int *)nodeChildren[1] : -1;
    int nodeHeight = (nodeHeightLeft <= nodeHeightRight) ? nodeHeightRight : nodeHeightLeft;
    *(int *)node = nodeHeight + 1;

    // Recalculate height for pivot
    int *pivotChildren[2];
    pivotChildren[0] = (int *)*(pivot + 1); // pivot->left
    pivotChildren[1] = (int *)*(pivot + 2); // pivot->right
    int pivotHeightLeft = (pivotChildren[0] != 0) ? *(int *)pivotChildren[0] : -1;
    int pivotHeightRight = (pivotChildren[1] != 0) ? *(int *)pivotChildren[1] : -1;
    int pivotHeight = (pivotHeightLeft <= pivotHeightRight) ? pivotHeightRight : pivotHeightLeft;
    *(int *)pivot = pivotHeight + 1;

    // Update the root pointer and the additional output pointer to pivot
    *ppRoot = (int *)pivot;
    *ppResult = (int *)pivot;
}