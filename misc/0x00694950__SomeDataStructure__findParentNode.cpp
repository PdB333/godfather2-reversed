// FUNC_NAME: SomeDataStructure::findParentNode
// Address: 0x00694950
// Role: Traverses a tree-like data structure based on a comparison function.
// Returns the parent node of the node where the traversal stops (when flag at +0x29 becomes non-zero).
// The structure at this+4 holds a pointer to the root node, which is used as the initial previous node.

struct TreeNode {
    TreeNode* field0;   // +0x00 – used as next node when compare >= 0
    void*    field4;    // +0x04 – not directly used in this function
    TreeNode* field8;   // +0x08 – used as next node when compare < 0
    char     flag;      // +0x29 – traversal stops when non-zero
};

TreeNode* __thiscall SomeDataStructure::findParentNode(int this, int key) {
    // Retrieve the root node pointer from this+4
    TreeNode** rootPtrArray = *(TreeNode***)(this + 4);  // array of pointers? rootPtrArray[0] and [1] exist
    TreeNode* current = rootPtrArray[1];                 // start from second element (maybe right child of root)
    char cFlag = current->flag;                          // check stopping flag
    TreeNode* previous = (TreeNode*)rootPtrArray;        // previous node starts as the root array itself

    while (cFlag == 0) {
        int cmpResult = compareKey(key);                 // external function at 0x004d4b20
        TreeNode* next;
        if (cmpResult < 0) {
            next = current->field8;                      // go to field at +0x08
            current = previous;                          // revert current to previous node
        } else {
            next = current->field0;                      // go to field at +0x00
        }
        previous = current;                              // save current as new previous
        current = next;                                  // move to next node
        cFlag = next->flag;                              // read flag from new node
    }
    return previous;                                     // return parent of the stopping node
}