// FUNC_NAME: SplayTree::splay

void __thiscall SplayTree::splay(SplayTree* this, SplayNode** link) {  // param_1 = this, param_2 = link (pointer to node pointer)
    SplayNode *node = *link;                                    // iVar1 = *param_2
    *link = node->next;                                         // *param_2 = node->next (+0x08)
    if (node->next && node->next->isSentinel) {                 // *(int *)(iVar1+8) check +0x15 flag
        node->next->prev = link;                                // Set next node's prev to the link pointer (address of link)
    }
    node->prev = link->parent;                                  // node->prev (+0x04) = link[1] (parent or container pointer)
    if (link == this->head->first) {                            // Compare link to head's first node pointer (+0x04)
        this->head->first = node;                               // Set head's first to node
        node->next = link;                                      // node->next = link (address of original link)
        link->parent = node;                                    // link->parent = node
        return;
    }
    SplayNode *parent = link->parent;                           // piVar2 = parent
    if (link == parent->right) {                                // Compare link to parent's right child (+0x08)
        parent->right = node;                                   // Set parent's right to node
        node->next = link;                                      // node->next = link
        link->parent = node;                                    // link->parent = node
        return;
    }
    parent->left = node;                                        // *piVar2 = node (set parent's left child)
    node->next = link;                                          // node->next = link
    link->parent = node;                                        // link->parent = node
    return;
}
// Node layout: +0x00 data, +0x04 prev/parent, +0x08 next/right, +0x15 isSentinel (char)
// Link layout: [0] node pointer, [1] parent/container pointer (used as prev link)
// Head layout: +0x00 unknown, +0x04 first node pointer