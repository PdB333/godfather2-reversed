// FUNC_NAME: RBTree::insertNodeBalance
void RBTree::insertNodeBalance(RBTree* this, RBTree::Node*& result, char hint)
{
    // Check for overflow
    if (this->size > 0x1ffffffd)
    {
        // Throw std::length_error ("map/set too long")
        char buffer[4];
        uint bufferLen;
        uint local_3c;
        // ... (throw logic omitted for brevity, follows EA STL pattern)
        // This path calls into EA STL exception handling.
        // For reconstruction, we assume it calls std::_Throw(std::length_error)
        // Actual implementation details are not critical.
        // ...
        return;
    }

    // Allocate new node via internal allocator
    Node* newNode = this->allocator.allocate();  // FUN_005e10f0 returns node*

    // Increment size
    this->size++;

    // Insert at hint position
    Node* header = this->header;  // +0x1c points to sentinel node
    Node* hintNode = unaff_EDI;  // hint iterator (passed in register EDI, not captured in params)
    // (Note: actual parameter passing might be via ECX, EDX, EDI)

    if (hintNode == header)
    {
        // Insert at end (rightmost)
        header->right = newNode;
        header->left = newNode;
        header->parent = newNode;
    }
    else if (hint == 0)
    {
        // Insert before hint (left side)
        hintNode->left = newNode;
        if (hintNode == header->rightmost)
            header->rightmost = newNode;
    }
    else
    {
        // Insert after hint (right side)
        hintNode->right = newNode;
        if (hintNode == header->leftmost)
            header->leftmost = newNode;
    }

    // Set node links (parent, child pointers)
    newNode->parent = hintNode;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->color = RED;  // +0x14 = 1

    Node* current = newNode;
    // Rebalance red-black tree
    while (true)
    {
        Node* parent = current->parent;
        if (parent->color == BLACK)  // +0x14 check for red/black; 1 = red, 0 = black
            break;

        Node* grandparent = parent->parent;
        Node* uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;

        if (uncle && uncle->color == RED)
        {
            // Case 1: uncle is red -> recolor
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            current = grandparent;
            continue;
        }

        // Case 2 & 3: uncle is black -> rotate
        if (parent == grandparent->left)
        {
            if (current == parent->right)
            {
                // Left-Right case: rotate left at parent
                rotateLeft(this, parent);
                current = parent;
                parent = current->parent;
            }
            // Left-Left case: rotate right at grandparent
            rotateRight(this, grandparent);
            parent->color = BLACK;
            grandparent->color = RED;
        }
        else
        {
            if (current == parent->left)
            {
                // Right-Left case: rotate right at parent
                rotateRight(this, parent);
                current = parent;
                parent = current->parent;
            }
            // Right-Right case: rotate left at grandparent
            rotateLeft(this, grandparent);
            parent->color = BLACK;
            grandparent->color = RED;
        }
        break;
    }

    // Ensure root is black
    header->parent->color = BLACK;

    // Set output pair: result = (this iterator, newNode)
    // Note: param_2 is a pointer to a pair (or two pointers)
    result[0] = this;   // *result = this (tree)
    result[1] = newNode; // result[1] = new node (the iterator)
}