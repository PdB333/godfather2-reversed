// FUNC_NAME: RBTree::erase
// Function address: 0x005dec30
// Removes a node from a red-black tree and rebalances.
// Node structure: left(+0x00), right(+0x04), parent(+0x08), color(+0x14), isNil(+0x15)
// Container structure: allocator(+0x04), head(+0x1c), size(+0x20)
// Head node: leftmost(+0x00), rightmost(+0x04), root(+0x08)

void RBTree::erase(RBTreeNode* nodeToErase)
{
    // If node is the sentinel (isNil != 0), throw invalid iterator
    if (nodeToErase->isNil != 0) {
        // Throw "invalid map/set<T> iterator"
        // (exception handling code omitted for clarity)
        // ...
        return;
    }

    // Lock the tree (synchronization)
    lockTree();

    RBTreeNode* node = nodeToErase;
    RBTreeNode* successor; // will hold the node that replaces the erased one

    // Determine the node to physically remove (node) and its successor
    if (nodeToErase->isNil == 0) {
        if (nodeToErase->right->isNil == 0) {
            // Node has two children: find in-order successor (leftmost of right subtree)
            successor = nodeToErase->right;
        } else {
            successor = nodeToErase->left;
        }
    } else {
        successor = nodeToErase->right;
    }

    // If successor is not nil, it will replace node
    if (successor->isNil == 0) {
        successor->parent = nodeToErase->parent;
    }

    // Update parent's child pointer
    if (nodeToErase->parent == head) {
        // Node is root
        head->root = successor;
    } else if (nodeToErase == nodeToErase->parent->left) {
        nodeToErase->parent->left = successor;
    } else {
        nodeToErase->parent->right = successor;
    }

    // Update leftmost and rightmost if necessary
    if (head->leftmost == nodeToErase) {
        // Find new leftmost: either successor or the leftmost of successor's subtree
        if (successor->isNil == 0) {
            RBTreeNode* leftmost = successor;
            while (leftmost->left->isNil == 0) {
                leftmost = leftmost->left;
            }
            head->leftmost = leftmost;
        } else {
            head->leftmost = successor->parent;
        }
    }

    if (head->rightmost == nodeToErase) {
        if (successor->isNil == 0) {
            // Find new rightmost: either successor or the rightmost of successor's subtree
            RBTreeNode* rightmost = successor;
            while (rightmost->right->isNil == 0) {
                rightmost = rightmost->right;
            }
            head->rightmost = rightmost;
        } else {
            head->rightmost = successor->parent;
        }
    }

    // Rebalance if the removed node was black
    if (nodeToErase->color == BLACK) {
        // Fix red-black properties
        RBTreeNode* x = successor;
        RBTreeNode* w;
        while (x != head->root && x->color == BLACK) {
            if (x == x->parent->left) {
                w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = head->root;
                }
            } else {
                // Symmetric case
                w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = head->root;
                }
            }
        }
        x->color = BLACK;
    }

    // Deallocate the node
    allocator->deallocate(nodeToErase, 0x18); // size 24 bytes

    // Decrement size
    if (size > 0) {
        size--;
    }

    // Return the erased node (for iterator update)
    // (The original code writes nodeToErase and param2 to the stack; we ignore that)
}