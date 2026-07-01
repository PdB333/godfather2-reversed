// FUNC_NAME: RbTree::insertFixup
void __thiscall RbTree::insertFixup(RbTree* this, RbTreeNode** outResult, RbTreeNode* parent, RbTreeNode* node, RbTreeNode* grandparent, RbTreeNode* greatGrandparent)
{
    // Dereference root pointer stored at this+0x04 (pointer to root node)
    RbTreeNode* root = *(RbTreeNode**)*(int**)(this + 4);
    
    // Assert: parent must be either null or equal to this node (used as sentinel)
    if ((parent != 0) && (parent != (RbTreeNode*)this)) {
        FUN_00b97aea(); // likely assert failure
    }
    
    // Short‑circuit when the new node becomes the root
    if (node == root) {
        root = *(RbTreeNode**)*(int**)(this + 4);
        
        // Validate grandparent (sentinel)
        if ((grandparent != 0) && (grandparent != (RbTreeNode*)this)) {
            FUN_00b97aea(); // assert
        }
        if (greatGrandparent == root) {
            // Allocate / initialise root cell
            FUN_008eb390(*(uint32_t*)(*(int*)(this + 4) + 4));
            
            // Relink the tree: new root points to itself in both directions
            *(int*)(*(int*)(this + 4) + 4) = *(int*)(this + 4);   // root->parent = &root
            *(uint32_t*)(this + 8) = 0;                           // color / sentinel
            *(uint32_t*)*(uint32_t*)(this + 4) = *(uint32_t*)(this + 4); // root->left = &root
            *(int*)(*(int*)(this + 4) + 8) = *(int*)(this + 4);   // root->right = &root
            
            // Output pair: (this, root)
            *outResult = (RbTreeNode*)this;
            outResult[1] = root;
            return;
        }
    }
    
    // Standard rebalancing loop (red‑black tree fixing)
    while (true) {
        // Sentinel check for each iteration
        if ((parent != 0) && (parent != (RbTreeNode*)this)) {
            FUN_00b97aea(); // assert
        }
        if (node == grandparent) break;
        
        // Perform a rotation (left or right depending on orientation)
        FUN_008ea480();
        FUN_008ee030(/* local buffer */ , parent, node);
    }
    
    // Output the final (parent, grandparent) pair after fixups
    *outResult = parent;
    outResult[1] = grandparent;
}