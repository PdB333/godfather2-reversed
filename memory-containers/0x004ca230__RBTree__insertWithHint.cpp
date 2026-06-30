// FUNC_NAME: RBTree::insertWithHint
// Address: 0x004ca230
// Purpose: Insert a new node into a red-black tree with a hint iterator.
// This is part of the EA EARS custom map/set implementation.

struct RBTreeNode {
    RBTreeNode* left;      // +0x00
    RBTreeNode* right;     // +0x04
    RBTreeNode* parent;    // +0x08
    unsigned char color;   // +0x14 (0 = black, 1 = red)
    unsigned char pad;     // +0x15
};

struct RBTreeHead {
    RBTreeNode* leftmost;  // +0x00
    RBTreeNode* rightmost; // +0x04
    RBTreeNode* root;      // +0x08
};

// Forward declarations of helper functions
RBTreeNode* __fastcall allocateNode(RBTreeHead* head, RBTreeNode* hint, RBTreeHead* head2);
void __fastcall rotateLeft(RBTreeNode** rootPtr);

void __thiscall RBTree::insertWithHint(RBTreeNode* hintNode, int* outIterator, unsigned char insertBefore)
{
    // Check for overflow (map/set too long)
    if (m_size > 0x1ffffffd) {
        // Exception handling sequence
        // (Omitted for brevity but matches the decompiled exception throw)
        // In practice, this would throw std::exception
        // ...
    }

    // Allocate a new tree node
    RBTreeNode* newNode = allocateNode(m_head, hintNode, m_head);
    m_size++;

    // Insert the node at the correct position based on hint
    if (hintNode == m_head) {
        // Tree is empty; set root and extremal pointers
        m_head->rightmost = newNode;
        m_head->leftmost  = newNode;
        m_head->root      = newNode;
    }
    else if (insertBefore == 0) {
        // Insert after hint (right side)
        hintNode->right = newNode;
        if (hintNode == m_head->rightmost) {
            m_head->rightmost = newNode;
        }
    }
    else {
        // Insert before hint (left side)
        hintNode->left = newNode;
        if (hintNode == m_head->leftmost) {
            m_head->leftmost = newNode;
        }
    }

    // Red‑black tree rebalancing (insert fixup)
    RBTreeNode* current = newNode;
    do {
        unsigned char parentColor = current->parent->color;

        if (parentColor != 0) {
            // Parent is red – need to fix
            if (current == current->parent->left) {
                // current is left child of its parent
                RBTreeNode* uncle = current->parent->right;
                if (uncle->color != 0) {
                    // Case 1: uncle is red → recolor
                    current->parent->color = 0;
                    uncle->color = 0;
                    current->parent->parent->color = 1;
                    current = current->parent->parent;
                }
                else {
                    // Case 2: uncle is black
                    if (current == current->parent->right) {
                        // Left rotation needed
                        current = current->parent;
                        rotateLeft(&m_head->root);
                    }
                    // Case 3: recolor and right rotation
                    current->parent->color = 0;
                    current->parent->parent->color = 1;
                    RBTreeNode* grandparent = current->parent->parent;
                    RBTreeNode* temp = grandparent->left;
                    grandparent->left = temp->right;
                    if (temp->right) {
                        temp->right->parent = grandparent;
                    }
                    temp->parent = grandparent->parent;
                    if (grandparent->parent == m_head) {
                        m_head->root = temp;
                    }
                    else if (grandparent == grandparent->parent->left) {
                        grandparent->parent->left = temp;
                    }
                    else {
                        grandparent->parent->right = temp;
                    }
                    temp->right = grandparent;
                    grandparent->parent = temp;
                    current = current->parent;
                }
            }
            else {
                // current is right child of its parent (symmetric)
                RBTreeNode* uncle = current->parent->left;
                if (uncle->color != 0) {
                    // Case 1: uncle red
                    current->parent->color = 0;
                    uncle->color = 0;
                    current->parent->parent->color = 1;
                    current = current->parent->parent;
                }
                else {
                    // Case 2: uncle black
                    if (current == current->parent->left) {
                        current = current->parent;
                        // Right rotation
                        RBTreeNode* temp = current->parent->right;
                        current->parent->right = temp->left;
                        if (temp->left) {
                            temp->left->parent = current->parent;
                        }
                        temp->parent = current->parent->parent;
                        if (current->parent->parent == m_head) {
                            m_head->root = temp;
                        }
                        else if (current->parent == current->parent->parent->left) {
                            current->parent->parent->left = temp;
                        }
                        else {
                            current->parent->parent->right = temp;
                        }
                        temp->left = current->parent;
                        current->parent->parent = temp;
                    }
                    // Case 3: recolor and left rotation
                    current->parent->color = 0;
                    current->parent->parent->color = 1;
                    RBTreeNode* temp = current->parent->parent;
                    temp->left = temp->left->right;
                    if (temp->left->right) {
                        temp->left->right->parent = temp;
                    }
                    temp->left->parent = temp->parent;
                    if (temp->parent == m_head) {
                        m_head->root = temp->left;
                    }
                    else if (temp == temp->parent->left) {
                        temp->parent->left = temp->left;
                    }
                    else {
                        temp->parent->right = temp->left;
                    }
                    temp->left->right = temp;
                    temp->parent = temp->left;
                    current = current->parent;
                }
            }

            // Update current's parent color for next iteration
            parentColor = current->parent->color;
        }
        else {
            // Parent is black: exit loop (tree is now valid)
            break;
        }
    } while (true);

    // Ensure root is black
    m_head->root->color = 0;

    // Output iterator: (container pointer, node pointer)
    outIterator[0] = (int)this;
    outIterator[1] = (int)newNode;
}