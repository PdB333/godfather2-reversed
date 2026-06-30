//FUNC_NAME: RBTree::fixupAfterDelete
void __thiscall RBTree::fixupAfterDelete(RBNode** link, RBNode* parentNode)
{
    RBNode* node = *link; // The node being removed/replaced
    RBNode* child = node->right; // +0x08: right child

    // Replace the link with the child
    *link = child;

    // If the child is red, recolor it black (set parent to link? Actually set child's parent to link's address? That seems wrong)
    if (child->color == 0) // +0x25: color (0 = red)
    {
        child->parent = link; // +0x04: parent pointer (but link is a pointer to pointer, not a node)
    }

    // Set node's parent to the parent node
    node->parent = parentNode; // +0x04

    // Now handle the case where the link is the root's right child? 
    // This looks like a rotation/recoloring step for deletion fixup
    if (link == this->root->right) // +0x04 of root? Actually param_1+4 is something like a sentinel or root pointer
    {
        this->root->right = node;
        node->right = link;
        link->parent = node; // Actually param_2[1] is parentNode, so this sets parentNode to node? Confusing.
        return;
    }

    RBNode* grandparent = parentNode; // param_2[1] is the parent of the node? Actually param_2[1] is the parent of the link? In the code, param_2[1] is used as the parent.
    // The code checks if link is the left child of grandparent
    if (link == grandparent->left) // +0x08? Actually grandparent->left is at +0x08? But we used +0x08 for right child. Need consistency.
    {
        grandparent->left = node;
        node->right = link;
        link->parent = node;
        return;
    }

    // Otherwise, link is the right child of grandparent
    grandparent->right = node;
    node->right = link;
    link->parent = node;
}