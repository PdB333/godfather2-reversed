// FUNC_NAME: std::_Tree::erase
void __thiscall Tree::erase(Tree *this, _Node *iterator, void *param_3, _Node *nodeToErase)
{
    // Check for invalid iterator (trying to erase sentinel node)
    // Sentinel node has _Isnil != 0 at offset +0x15
    if (nodeToErase[0x15] != '\0') {
        // Debug: throw invalid map/set iterator exception
        std::_Debug_message("invalid map/set<T> iterator", 0x1b);
        std::_Throw(/*...*/);
    }

    // Begin erasure: yields the node to physically remove (y)
    __TreeUnlink(this, nodeToErase);

    // Determine the node to replace the erased one (y)
    _Node *y = (_Node *)nodeToErase[0]; // y = nodeToErase->left
    if (y[0x15] != '\0') { // if left child is sentinel (nil)
        y = (_Node *)nodeToErase[2]; // use right child instead
    }

    // y is now the child to splice in (or sentinel if no children)
    _Node *parent = (_Node *)nodeToErase[1]; // nodeToErase->parent
    if (y[0x15] == '\0') { // if y is not sentinel
        y[1] = (int)parent; // y->parent = parent
    }

    // Update parent's child pointer
    if ((_Node *)this->header.left == nodeToErase) {
        this->header.left = y;
    } else if ((_Node *)parent[0] == nodeToErase) { // if nodeToErase is left child
        parent[0] = (int)y; // parent->left = y
    } else { // must be right child
        parent[2] = (int)y; // parent->right = y
    }

    // Update the header sentinel pointers (min and max) if necessary
    // header->parent points to smallest node, header->right to largest
    if ((_Node *)this->header.parent == nodeToErase) {
        // Find new minimum (leftmost node of y's subtree)
        _Node *newMin = y;
        if (y[0x15] == '\0') { // if y is not sentinel
            _Node *temp = (_Node *)y[0];
            while (temp[0x15] == '\0') { // go as far left as possible
                newMin = temp;
                temp = (_Node *)temp[0];
            }
        }
        this->header.parent = (_Node *)newMin;
    }

    _Node *header = (_Node *)this->header; // actual header node
    if ((_Node *)header[2] == nodeToErase) {
        // Update maximum: if y is not sentinel, use its rightmost descendant
        if (y[0x15] == '\0') {
            _Node *newMax = __TreeRightmost(y);
            header[2] = (int)newMax;
        } else {
            header[2] = (int)parent;
        }
    }

    // Red-black tree fixup: only if erased node was black
    // nodeToErase[0x14] is _Color (1 = black, 0 = red)
    if (nodeToErase[0x14] == 1) { // was black
        _Node *x = y; // x is the node that replaced nodeToErase (may be sentinel)
        _Node *xParent = (_Node *)x[1];

        // Standard fixup loop
        while (x != this->header.left && x[0x14] == 0) { // while x is red and not root
            if (x == (_Node *)xParent[0]) { // x is left child
                _Node *w = (_Node *)xParent[2]; // sibling
                if (w[0x14] == 0) { // sibling is red
                    w[0x14] = 1; // black
                    xParent[0x14] = 0; // parent red
                    __leftRotate(this, xParent);
                    w = (_Node *)xParent[2]; // update sibling
                }
                if (w[0][0x14] == 0 && w[2][0x14] == 0) { // both children of sibling black
                    w[0x14] = 0; // sibling red
                    x = xParent;
                    xParent = (_Node *)x[1];
                } else {
                    if (w[2][0x14] == 0) { // right child of sibling black
                        w[0][0x14] = 1; // left child black
                        w[0x14] = 0; // sibling red
                        __rightRotate(this, w);
                        w = (_Node *)xParent[2];
                    }
                    w[0x14] = xParent[0x14]; // sibling gets parent's color
                    xParent[0x14] = 1; // parent black
                    w[2][0x14] = 1; // right child black
                    __leftRotate(this, xParent);
                    x = this->header.left;
                    break;
                }
            } else { // x is right child (mirror case)
                _Node *w = (_Node *)xParent[0];
                if (w[0x14] == 0) {
                    w[0x14] = 1;
                    xParent[0x14] = 0;
                    __rightRotate(this, xParent);
                    w = (_Node *)xParent[0];
                }
                if (w[2][0x14] == 0 && w[0][0x14] == 0) {
                    w[0x14] = 0;
                    x = xParent;
                    xParent = (_Node *)x[1];
                } else {
                    if (w[0][0x14] == 0) {
                        w[2][0x14] = 1;
                        w[0x14] = 0;
                        __leftRotate(this, w);
                        w = (_Node *)xParent[0];
                    }
                    w[0x14] = xParent[0x14];
                    xParent[0x14] = 1;
                    w[0][0x14] = 1;
                    __rightRotate(this, xParent);
                    x = this->header.left;
                    break;
                }
            }
        }
        // Ensure root is black
        x[0x14] = 1;
    }

    // Deallocate the erased node
    // Allocator pointer at this+0x04
    void (*deleter)(void *, size_t) = *(void (**)(void *, size_t))this->allocator;
    deleter(nodeToErase, 0x18); // node size = 24 bytes

    // Decrement size
    if (this->size != 0) {
        this->size--;
    }

    // Return the next iterator (original node pointer) and an extra value
    // This overwrites the caller's stack frame for return values
    *(__Node **)returnAddr = nodeToErase;
    *(void **)(returnAddr + 4) = param_3;
}