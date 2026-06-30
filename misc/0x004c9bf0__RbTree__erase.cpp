// FUNC_NAME: RbTree::erase
void RbTree::erase(Node* z) // returns iterator to next node (via hidden return struct)
{
    // If iterator points to end (sentinel), throw "invalid map/set<T> iterator"
    if (*((char*)z + 0x15) != 0) // +0x15: sentinel flag
    {
        // Exception throw path
        // ... (omitted for brevity)
    }

    // Helper function to fix tree after deletion
    fixupAfterErase();

    // Determine node to splice out (y) and its child (x)
    Node* y = z;
    Node* x = nullptr;
    bool yWasRed = *((char*)y + 0x14) != 0; // color at +0x14

    if (*((char*)z + 0x15) == 0) // z is not sentinel
    {
        if (*((char*)z[2] + 0x15) == 0) // z->right is not sentinel? actually offset +0x15 on right child
        {
            y = z[2]; // use z->right as y
        }
    }
    else
    {
        y = z[2]; // use z->right as y
    }

    // Standard RB deletion: find splice node
    if (*((char*)y + 0x15) == 0) // y is not sentinel
    {
        y[1] = z[1]; // y->parent = z->parent
    }

    // Update parent's child pointers
    if ((Node*)*(*(int*)(this + 0x1c) + 4) == z) // if z is root? Actually this+0x1c points to header node, +4 is root
    {
        *(int*)(*(int*)(this + 0x1c) + 4) = y;
    }
    else if (*z[1] == z) // z is left child of its parent
    {
        z[1][0] = y; // parent->left = y
    }
    else
    {
        z[1][2] = y; // parent->right = y
    }

    // Update leftmost pointer if necessary
    if ((Node*)**(int**)(this + 0x1c) == z) // z is leftmost
    {
        // Find new leftmost
        Node* newLeft = y;
        if (*((char*)y + 0x15) == 0) // y not sentinel
        {
            while (*((char*)*y + 0x15) == 0) // while y->left is not sentinel
            {
                y = *y; // y = y->left
                newLeft = y;
            }
        }
        **(int**)(this + 0x1c) = newLeft; // update leftmost
    }

    // Update rightmost pointer if necessary
    int header = *(int*)(this + 0x1c);
    if (*(int**)(header + 8) == z) // if z is rightmost
    {
        if (*((char*)y + 0x15) == 0) // y not sentinel
        {
            *(int*)(header + 8) = FUN_004ca540(); // find rightmost from y's subtree
        }
        else
        {
            *(int*)(header + 8) = z[1]; // parent becomes new rightmost
        }
    }

    // Rebalancing if spliced node was black
    if (*((char*)z + 0x14) == 1) // z was black? Actually color is at +0x14, 1 usually black
    {
        // Complex rebalancing loop (rotations and recoloring)
        // ... (code omitted for clarity, similar to standard RB delete fixup)
        // Uses FUN_004ca4f0 (left rotate) and FUN_004ca5a0 (right rotate)
    }

    // Set spliced node's color to red (if it was red? Actually it's standard)
    *((char*)y + 0x14) = 1; // or 0? The code sets it to 1 at the end

    // Destroy the node (calls deallocator at this+4 vtable)
    (*(void (**)(Node*, int))(**(int**)(this + 4) + 4))(z, 0x18);

    // Decrement size
    if (*(int*)(this + 0x20) != 0)
    {
        *(int*)(this + 0x20) -= 1;
    }

    // Return value is packed into two words (next node and something)
    // *((int*)return_ptr) = z; // actually returns the node that was erased? No, returns next iterator
    // return_ptr[1] = param_2; // param_2 is likely next node
    // This function returns an iterator (pair of pointers) via hidden return pointer.
}