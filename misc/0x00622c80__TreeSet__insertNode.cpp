// FUNC_NAME: TreeSet::insertNode
// Function address: 0x00622c80
// Reconstructed red-black tree insertion with balancing.
// Tree structure: header at +0x1c (pointer to sentinel with first, last, root), size at +0x20.
// Node layout: [0] left, [4] right, [8] parent, [0x24] color (0=black,1=red), [0x25] flag (used during rotations).

#include <exception> // for std::length_error

class RedBlackTree
{
public:
    struct Node
    {
        Node* left;   // +0x00
        Node* right;  // +0x04
        Node* parent; // +0x08
        char color;   // +0x24 (0 = black, 1 = red)
        char flag;    // +0x25 (unused/external flag, possibly for iterator marking)
    };

private:
    struct Header
    {
        Node* first;  // +0x00 (leftmost)
        Node* last;   // +0x04 (rightmost)
        Node* root;   // +0x08
    };

    Header* m_pHeader; // +0x1c
    size_t m_size;     // +0x20

    // Node allocation (simplified)
    Node* allocateNode()
    {
        return reinterpret_cast<Node*>(FUN_006238d0(m_pHeader, nullptr, m_pHeader));
    }

    // Rotate left at node x
    void rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;
        if (x == m_pHeader->root)
            m_pHeader->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Rotate right at node x
    void rotateRight(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        y->parent = x->parent;
        if (x == m_pHeader->root)
            m_pHeader->root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Throw length_error if size exceeds limit
    void checkSize()
    {
        if (m_size > 0xaaaaaa8)
        {
            // throw std::length_error("map/set<T> too long");
            // Original code calls FUN_0043f9f0("map/set<T> too long", 0x13) then throw
            // We'll just simulate with a function call.
            // For reconstruction, we'll assume std::length_error is thrown.
            // In the original, a local string is built and a custom exception handler is used.
            // We'll keep it simple: throw std::length_error("map/set<T> too long");
            // (Actual implementation would use EA's internal throw mechanism)
            // We'll leave a comment.
            throw std::length_error("map/set<T> too long");
        }
    }

public:
    // Insert node at position given by iterator hint.
    // param_2 is output: pair<iterator, bool> (this pointer, node pointer)
    // param_3: if true, insert before hint; if false, insert after hint.
    void insertNode(Node* hint, Node** outNode, bool bInsertBefore)
    {
        checkSize();

        Node* newNode = allocateNode();
        m_size++;

        if (hint == nullptr)
        {
            // Tree empty: set first, last, root
            m_pHeader->first = newNode;
            m_pHeader->last = newNode;
            m_pHeader->root = newNode;
            newNode->parent = nullptr;
            newNode->left = nullptr;
            newNode->right = nullptr;
        }
        else if (!bInsertBefore)
        {
            // Insert after hint
            newNode->parent = hint;
            hint->right = newNode;
            if (hint == m_pHeader->last)
                m_pHeader->last = newNode;
        }
        else
        {
            // Insert before hint
            newNode->parent = hint;
            hint->left = newNode;
            if (hint == m_pHeader->first)
                m_pHeader->first = newNode;
        }

        // Fix red-black properties
        newNode->color = 1; // red
        Node* current = newNode;

        while (current->parent && current->parent->color == 1)
        {
            Node* grandparent = current->parent->parent;
            if (!grandparent)
                break;

            if (current->parent == grandparent->left)
            {
                Node* uncle = grandparent->right;
                if (uncle && uncle->color == 1)
                {
                    // Case 1: uncle is red
                    current->parent->color = 0;
                    uncle->color = 0;
                    grandparent->color = 1;
                    current = grandparent;
                }
                else
                {
                    // Case 2: uncle is black
                    if (current == current->parent->right)
                    {
                        // Left rotation at parent
                        rotateLeft(current->parent);
                        current = current->left; // updated after rotation
                    }
                    // Case 3: rotate right at grandparent
                    current->parent->color = 0;
                    grandparent->color = 1;
                    rotateRight(grandparent);
                }
            }
            else // parent == grandparent->right
            {
                Node* uncle = grandparent->left;
                if (uncle && uncle->color == 1)
                {
                    // Symmetric case 1
                    current->parent->color = 0;
                    uncle->color = 0;
                    grandparent->color = 1;
                    current = grandparent;
                }
                else
                {
                    // Symmetric case 2
                    if (current == current->parent->left)
                    {
                        rotateRight(current->parent);
                        current = current->right;
                    }
                    // Symmetric case 3
                    current->parent->color = 0;
                    grandparent->color = 1;
                    rotateLeft(grandparent);
                }
            }
        }

        m_pHeader->root->color = 0; // root is black

        // Output result
        outNode[0] = reinterpret_cast<Node*>(this);
        outNode[1] = newNode;
    }
};
// Note: This reconstruction assumes the standard red-black tree algorithm.
// The original code uses custom rotation functions (FUN_006223e0 and inline rotations)
// and specific pointer manipulations for the sentinel header.
// The 'flag' field at +0x25 may be used to mark during rotations (e.g., to avoid redundant work).