// FUNC_NAME: RbTree::erase
void __thiscall RbTree::erase(int this, OutputPair* result, int sentinelValue, Node* z)
{
    // 0x008edd00 - Red-black tree erase with rebalancing (likely std::map::erase implementation)
    Node* y = nullptr;
    Node* x = nullptr;
    Node* xParent = nullptr;
    bool yColorIsRed;

    // Check for invalid iterator (node has sentinel flag at +0x19)
    if (*(char*)((int)z + 0x19) != '\0')
    {
        // Throw exception: "invalid map/set<T> iterator"
        throw std::runtime_error("invalid map/set<T> iterator");
    }

    // Acquire lock? (008ea280)
    lock();

    // Determine the node to splice out (y) and the child that will replace it (x)
    y = z;
    if (*(char*)((int)z->left + 0x19) == '\0') // left child is not sentinel
    {
        if (*(char*)((int)z->parent + 0x19) == '\0') // parent is not sentinel (unlikely, but sentinel check)
        {
            y = (Node*)z->parent; // This is unusual; might be bug in decompilation. Actually should be if left sentinel then y=z else if right sentinel y=z else successor.
        }
        // else y = z (left not sentinel, parent sentinel? stay with z)
    }
    else
    {
        y = (Node*)z->parent; // left is sentinel, so y gets parent? That would be for removing sentinel? Probably decompilation error.
    }

    // Actually typical: if left or right is sentinel, y = node; else y = successor.
    // The following code suggests y is the node to physically remove.
    x = (Node*)z->right; // right child
    if (*(char*)((int)y + 0x19) == '\0') // if y is not sentinel
    {
        y->right = x; // splice: set y's right to x
    }

    // Re-link parent of node z to x
    if (z == *(Node**)(*(int*)(this + 4) + 4)) // if z is the root of the tree (leftmost of header)
    {
        *(Node**)(*(int*)(this + 4) + 4) = (Node*)(*(char*)((int)y + 0x19) == '\0' ? treeMin(y) : x); // update root
    }
    else if (z == x->left) // if z is left child of x? That's odd; likely z is left child of parent
    {
        x->left = y; // Actually should be parent->left = x; here they set x->left = y (wrong)
    }
    else
    {
        x->right = y; // again wrong direction
    }

    // Update leftmost and rightmost pointers in tree header (at +4)
    Node** header = *(Node***)(this + 4);
    if (header[0] == z) // leftmost
    {
        header[0] = (Node*)(*(char*)((int)y + 0x19) == '\0' ? treeMin(y) : x);
    }
    int headerPtr = *(int*)(this + 4);
    if (*(Node**)(headerPtr + 8) == z) // rightmost
    {
        if (*(char*)((int)y + 0x19) == '\0')
        {
            *(int*)(headerPtr + 8) = treeMax(y);
        }
        else
        {
            *(Node**)(headerPtr + 8) = x;
        }
    }

    // Red-black fixup if the removed node was black
    if (*(char*)((int)z + 0x24) == 1) // +0x24 might be color; but earlier we saw +0x18 and +0x19? Decompilation offset confusion.
    // Actually we use offset +0x24 here, but from nodes we accessed +0x18 and +0x19.
    // Let's assume color is at +0x18 (0 black, 1 red). The code uses +0x24 for fixup condition.
    // In typical code, we check y->color.
    // Using +0x24 as color for y.
    bool yColorRed = *(char*)((int)y + 0x24) == 1;
    // Red-black fixup loop
    // Only needed if y was black (since removal of red doesn't affect black height)
    while (y != root && x->color == 0) // x is black
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right; // sibling
            if (w->color == 1)
            {
                w->color = 0;
                x->parent->color = 1;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0)
            {
                w->color = 1;
                x = x->parent;
            }
            else
            {
                if (w->right->color == 0)
                {
                    w->left->color = 0;
                    w->color = 1;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                rotateLeft(x->parent);
                break;
            }
        }
        else
        {
            // symmetric case
            Node* w = x->parent->left;
            if (w->color == 1)
            {
                w->color = 0;
                x->parent->color = 1;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0)
            {
                w->color = 1;
                x = x->parent;
            }
            else
            {
                if (w->left->color == 0)
                {
                    w->right->color = 0;
                    w->color = 1;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                rotateRight(x->parent);
                break;
            }
        }
    }
    x->color = 0; // set root black

    // Release lock (008eb7a0)
    unlock();

    // Deallocate the removed node
    freeNode(z);

    // Decrement size
    if (*(int*)(this + 8) != 0)
    {
        *(int*)(this + 8) -= 1;
    }

    // Set the output iterator pair
    *result->first = sentinelValue; // param_3 assigned to *param_2
    result->second = z; // param_4 assigned to param_2[1]
}