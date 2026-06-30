// FUNC_NAME: Tree::insert
// Function address: 0x005deb50
// Role: Insert a key into a binary search tree (likely AVL or balanced tree) and return node info.
// Parameters:
//   this + 0x1c = pointer to a small struct (8 bytes): [0] = sentinel/null? [4] = root node pointer
//   param_2 = output structure (3 ints): [0] = key, [1] = node pointer, [2] = flag (0=found, 1=inserted)
//   param_3 = pointer to key to insert/find

struct TreeNode {
    TreeNode* left;         // +0x00
    int unknown_field;      // +0x04 (possibly height or parent pointer)
    TreeNode* right;        // +0x08
    int key;                // +0x0C
    char flag;              // +0x15 (0 = internal node? non-zero = leaf/valid)
};

struct TreeRoot {
    TreeNode* sentinel;     // +0x00
    TreeNode* root;         // +0x04
};

// External functions (defined elsewhere)
// Inserts a new node with given key under the parent, returns a pointer to the inserted node's key/value pair
int* insertNode(void* thisPtr, void* parent, bool rightChild, uint* key);
// Rebalance the tree after insertion
void rebalanceAfterInsert(void);

int* __thiscall Tree::insert(void* thisPtr, int* output, uint* key)
{
    // Get the tree's root structure (pointed to by this+0x1c)
    TreeRoot* treeRoot = *(TreeRoot**)((char*)thisPtr + 0x1c);
    TreeNode* currentNode = treeRoot->root;  // initial root node
    bool wentLeft = true;                    // direction of last move

    // Traverse the tree until we find a leaf (flag non-zero)
    if (currentNode != nullptr && currentNode->flag == '\0') {
        TreeRoot* sentinelRoot = treeRoot; // keep for later check (actually used for sentinel comparison)
        do {
            // Update the "parent" to current node before moving
            // (the loop actually uses a pointer to the current node stored in "parent" variable)
            // In decompile: local_4 = puVar2; where puVar2 is the child node from last iteration.
            // We'll use a separate variable to track the last "parent" node.
            TreeNode* parentNode = currentNode;
            wentLeft = *key < (uint)currentNode->key;
            if (wentLeft) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        } while (currentNode != nullptr && currentNode->flag == '\0');
        // After loop, parentNode is the last non-leaf node, currentNode is the next child (could be leaf or null)
        // Actually the loop condition uses puVar2 which becomes the child node; the assignment
        // "local_4 = puVar2" sets the parent to that child, so after loop, local_4 is the child (leaf or null).
        // But we need to adjust: The decompile sets local_4 to the child and then checks on loop condition.
        // It's easier to follow the logic with a while loop that updates parent after moving.
    }

    // The code above is a simplified version; original uses a while loop with local_4 as the "parent" node.
    // Actually the decompile shows: initially local_4 = treeRoot; then puVar2 = local_4[1] (root);
    // then while (*(char*)((int)puVar2 + 0x15) == '\0') { local_4 = puVar2; ... }
    // So local_4 keeps the parent of the node just examined.
    // After loop, local_4 is the last internal node (or root if root is leaf).
    // We'll reimplement that logic precisely.

    // Better reconstruction (matching the decompile exactly):
    TreeRoot* rootStruct = treeRoot;
    TreeNode* parentNode = (TreeNode*)(&treeRoot->root); // actually local_4 points to the TreeRoot's array ([0] sentinel, [1] root)
    // Wait, the decompile: local_4 = *(undefined4 **)(param_1 + 0x1c); // so local_4 points to the 8-byte structure
    // Then puVar2 = local_4[1]; -> puVar2 is the root node pointer.
    // Then while (puVar2->flag == 0) { local_4 = puVar2; if (*key < puVar2->key) puVar2 = puVar2->left; else puVar2 = puVar2->right; }
    // So local_4 is a pointer that after the loop points to the node that is the parent of the current search path.
    // Then after loop, they check if (bVar4) { if (local_4 == rootStruct->root) { insertNode ... } else { rebalance } }
    // So local_4 is the node where we stopped (the node whose child would be the insertion point).

    TreeNode* currentNode = treeRoot->root;
    TreeNode* lastInternal = (TreeNode*)treeRoot; // initially points to the TreeRoot struct (sentinel maybe)
    bool direction = true; // direction of last move

    // Traverse while current node is internal (flag == 0)
    while (currentNode != nullptr && currentNode->flag == '\0') {
        lastInternal = currentNode;
        direction = *key < (uint)currentNode->key;
        if (direction) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }

    // After loop, lastInternal is the parent of the leaf/empty spot
    // bVar4 is the direction that was taken from lastInternal to currentNode (true = left, false = right)
    bool wentLeft = direction; // corresponds to bVar4

    // Check if we should insert at the root (when parent is the sentinel)
    if (wentLeft) {
        if (lastInternal == (TreeNode*)treeRoot->sentinel) { // actually comparing to the root node? The decompile: if (local_4 == **(int**)(param_1+0x1c))
            // That condition checks if the parent is the root of the tree (since root is stored as the second pointer in the 8-byte struct).
            // **(int**)(param_1+0x1c) = *((int*)treeRoot) = treeRoot->sentinel? Wait, treeRoot is a pointer to an array of two ints.
            // Since treeRoot is of type TreeRoot*, dereferencing it once gives the first element (sentinel). Dereferencing twice gives the sentinel value (which is a pointer to a node?).
            // But local_4 is a pointer to a node. So the comparison checks if local_4 == sentinel (since sentinel is also a node pointer?).
            // Actually the sentinel might be a special node that represents the root's parent.
            // For simplicity, we can treat it as checking if lastInternal is the sentinel node.
            if (lastInternal == (TreeNode*)treeRoot->sentinel) {
                // Insert at the root
                int* inserted = insertNode(thisPtr, &lastInternal, 1, key); // param_2 = output, flag 1? Let's look at call: FUN_005df5f0(param_1,&local_8,1,param_3)
                // local_8 is an int variable on stack that holds thisPtr? Actually local_8 = param_1; they pass address of local_8.
                // This is likely a placeholder for the parent pointer. So we'll treat it as inserting at root.
                output[0] = inserted[0];
                output[1] = inserted[1];
                *(char*)(output + 2) = 1; // flag = 1 (inserted)
                return output;
            }
            // If not root, rebalance (rotation)
            rebalanceAfterInsert();
        } else {
            // If not wentLeft? Actually the if (bVar4) block contains the comparison, else it goes to FUN_005e1230.
            // Wait the decompile: if (bVar4) { if (local_4 == root) { insert } else { rebalance } } else { skip? }
            // Let's re-read:
            // if (bVar4) {
            //     if (local_4 == **(int**)(param_1+0x1c)) {
            //         piVar3 = some insertion;
            //         ... return param_2 with flag 1;
            //     }
            //     FUN_005e1230();
            // }
            // So if bVar4 is true, and the parent is not the root, they call rebalance.
            // If bVar4 is false, they skip that block entirely and go to the next comparison.
            // So our if-else structure should match.
            if (lastInternal != (TreeNode*)treeRoot->sentinel) {
                rebalanceAfterInsert();
            }
        }
    }

    // Now check if the key is less than the current node's key again? Actually they compare (uint)local_4[3] < *param_3
    // This is checking if the key we are inserting is greater than the parent's key (since we already have direction from last move).
    // But after the loop, currentNode is the leaf (or null) that we looked at.
    // The next block: if ((uint)currentNode->key < *key) { insert at that side }
    // Since currentNode is the leaf where we stopped (with flag != 0), we compare the leaf's key with the search key.
    // If leaf key < search key, we insert on the right (because we came from parent with wentLeft? Wait, the direction we stored is from parent to leaf.
    // Actually after the loop, currentNode is the leaf node (or null) that we examined. Its key is different from the search key.
    // The code: if ((uint)local_4[3] < *param_3) -> local_4[3] is the key of the lastInternal node (parent). That doesn't make sense.
    // Let's re-express: The loop ends when currentNode is a leaf (flag != 0). At that point, lastInternal is the parent of that leaf.
    // Then they check: if ((uint)lastInternal->key < *key) { ... } else { not insert? }
    // Actually the decompile: if ((uint)local_4[3] < *param_3) { ... } so local_4 is lastInternal.
    // So they check if the parent's key is less than the search key. That would be true if we took the right branch from parent (since parent key < search key when going right).
    // In that case, they call insertion on the right side.
    // So we should handle that.

    if ((uint)lastInternal->key < *key) {
        // Insert on the right side (since key > parent key)
        int* inserted = insertNode(thisPtr, &lastInternal, 1, key); // the 1 indicates right child? Actually the call passes bVar4 as third parameter, which here is true (since we just compared and found key > parent key -> wentRight = true)
        output[0] = inserted[0];
        output[1] = inserted[1];
        *(char*)(output + 2) = 1; // inserted
        return output;
    }

    // If key <= parent key, then the key should already be in the tree? Actually if equal, it would have been found earlier? But the traversal stops at a leaf, so equal key means the leaf is the node?
    // The loop would have stopped if currentNode->flag != 0, meaning we reached a leaf node that may have the same key.
    // But we only check parent's key, not leaf's key. Hmm.
    // Actually after loop, currentNode is the leaf (flag != 0). The comparison: (uint)currentNode->key < *key? No, it's local_4[3] (parent key) < *key.
    // So if parent key is not less than search key, they set output to the parent node and flag 0 (found).
    // That suggests that if the search key is less than parent key, the leaf node (which is left child) might be the key? Or maybe the leaf node's key is > parent key? I'm confused.
    // Let's trust the decompile: else { output[0] = local_8 (thisPtr?); output[1] = local_4 (parent node); flag = 0; }
    // So they treat the parent node as the found node. That likely means the tree stores keys only at internal nodes? And leaves are sentinels?
    // Actually the flag at +0x15: if non-zero, node is a leaf (key stored). If zero, internal node.
    // So the leaf nodes contain the actual keys. The internal nodes are just for navigation.
    // Then the traversal stops when reaching a leaf. They compare the leaf's key? No, they compare parent's key. That would be wrong.
    // Perhaps the loop condition is inverted? The while loop condition is if current node's flag is zero (internal), continue. So when flag is non-zero, we stop at that node (leaf).
    // The leaf node has the key. So after loop, currentNode is the leaf. Then they should compare leaf's key.
    // But the code compares local_4[3] (parent) key. This suggests local_4 is actually the leaf node? Wait, the loop sets local_4 = puVar2, then puVar2 = child. So after loop, local_4 is the last internal node (parent). The leaf is puVar2 (currentNode). But in the code after loop, they use local_4 for comparison. That is the parent.
    // Unless they treat the parent's key as a reference? Maybe the tree uses a different layout: the key is stored in the internal node, and leaves are empty sentinels? That would make sense for a B-tree or something.
    // But the decompile checks (uint)local_4[3] < *param_3. If local_4 is the parent internal node, and the key is supposed to be at that node, then the search should have matched? Actually internal nodes have keys too, but they are for routing.
    // I need to simplify: The exact interpretation is ambiguous. For the reconstruction, we'll keep the logic as per decompile but with meaningful names.

    // Fallback: if key not less than parent key, treat parent as containing the key? Possibly the key is stored in the internal node.
    output[0] = (int)thisPtr; // local_8 is this (param_1)
    output[1] = (int)lastInternal; // node pointer
    *(char*)(output + 2) = 0; // not inserted, found
    return output;
}