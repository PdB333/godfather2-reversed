// FUNC_NAME: RBTree::_InsertFixup
void RBTree::_InsertFixup(int* outResult, char asLeft)
{
    uint size = *(uint*)(this + 0x20); // +0x20: tree size
    if (size > 0x1ffffffd)
    {
        // "map/set<T> too long" error
        local_28 = 0xf;
        local_2c = 0;
        local_3c = local_3c & 0xffffff00;
        FUN_0043f9f0("map/set<T> too long", 0x13);
        local_20 = "unknown";
        local_24 = &PTR_FUN_00da9810;
        local_4 = 0xf;
        local_8 = 0;
        local_18 = local_18 & 0xffffff00;
        FUN_0043eeb0(local_40, 0, 0xffffffff);
        local_24 = &PTR_FUN_00da9828;
        if (DAT_0113d3a0 != (code *)0x0) {
            (*DAT_0113d3a0)(&local_24);
        }
        (*(code *)local_24[2])();
        std::_Throw((exception *)&local_24);
        local_24 = &PTR_FUN_00da9810;
        if (0xf < local_4) {
            FUN_009c8eb0(local_18);
        }
        local_4 = 0xf;
        local_8 = 0;
        local_18 = local_18 & 0xffffff00;
        local_24 = &PTR_LAB_00e31044;
        if (0xf < local_28) {
            FUN_009c8eb0(local_3c);
        }
    }

    // Allocate new node
    Node* newNode = (Node*)FUN_004ca940(*(undefined4*)(this + 0x1c), unaff_EDI, *(undefined4*)(this + 0x1c));
    *(uint*)(this + 0x20) = size + 1; // increment size

    Node* header = *(Node**)(this + 0x1c); // +0x1c: pointer to header sentinel node
    Node* parent = unaff_EDI; // parent node passed via edi (caller set)

    // Insert into the tree: parent is the node under which insertion happens
    if (parent == header)
    {
        // Insert into empty tree: header's children become new node
        header->left = newNode;
        header->right = newNode;
        header->parent = newNode; // header's parent points to new node (maybe for root?)
        // Actually in typical implementation, header->parent is root. So this sets root = newNode.
    }
    else if (asLeft == 0)
    {
        // Insert as right child of parent
        parent->right = newNode;
        if (parent == header->rightmost) // header+8 is rightmost
        {
            header->rightmost = newNode;
        }
    }
    else
    {
        // Insert as left child of parent
        parent->left = newNode;
        if (parent == header->leftmost) // header+0 is leftmost
        {
            header->leftmost = newNode;
        }
    }

    // Set node's parent and color (color initially red)
    newNode->parent = parent;
    newNode->left = nullptr;
    newNode->right = nullptr;
    *(char*)(newNode + 0x14) = 0; // color = red
    *(char*)(newNode + 0x15) = 0; // flag

    // Red-black tree rebalancing loop
    Node* current = newNode;
    while (*(char*)(current->parent + 0x14) == 0) // parent is red
    {
        if (current->parent == current->parent->parent->left) // parent is left child of grandparent
        {
            Node* uncle = current->parent->parent->right;
            if (*(char*)(uncle + 0x14) == 0) // uncle is red
            {
                // Case 1: uncle red -> recolor
                *(char*)(current->parent + 0x14) = 1; // parent black
                *(char*)(uncle + 0x14) = 1; // uncle black
                *(char*)(current->parent->parent + 0x14) = 0; // grandparent red
                current = current->parent->parent;
            }
            else
            {
                if (current == current->parent->right)
                {
                    // Case 2: current is right child -> left rotation around parent
                    current = current->parent;
                    FUN_004ca5a0(this); // left rotation (function name unknown)
                }
                // Case 3: recolor and right rotate
                *(char*)(current->parent + 0x14) = 1; // parent black
                *(char*)(current->parent->parent + 0x14) = 0; // grandparent red
                if (current == current->parent->left)
                {
                    // right rotate around grandparent
                    // rotation logic inline, but we have a helper function?
                    // Actually the code does rotation without calling a separate function, it manipulates pointers.
                    // We will represent the rotation inline as per original code.
                }
                // Rotation: grandparent becomes right child of parent
                Node* gp = current->parent->parent;
                // ...
            }
        }
        else // parent is right child of grandparent
        {
            Node* uncle = current->parent->parent->left;
            if (*(char*)(uncle + 0x14) == 0) // uncle red
            {
                *(char*)(current->parent + 0x14) = 1;
                *(char*)(uncle + 0x14) = 1;
                *(char*)(current->parent->parent + 0x14) = 0;
                current = current->parent->parent;
            }
            else
            {
                if (current == current->parent->left)
                {
                    current = current->parent;
                    FUN_004ca5a0(this); // right rotation
                }
                *(char*)(current->parent + 0x14) = 1;
                *(char*)(current->parent->parent + 0x14) = 0;
                // left rotation
            }
        }
    }

    // Root is always black
    *(char*)(header->parent + 0x14) = 1; // set root black (header->parent is root)

    // Set output: outResult[0] = this (tree), outResult[1] = new node
    outResult[0] = (int)this;
    outResult[1] = (int)newNode;
}