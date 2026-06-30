// FUNC_NAME: BinarySearchTree::findNode
// Address: 0x00573db0
// Binary search tree lookup. Returns node pointer if key exists, else nullptr.
// Node structure: +0x8 = left child, +0xC = right child, +0x10 = key (int)

int* __thiscall BinarySearchTree::findNode(int** thisPtr, int* keyPtr)
{
    int* currentNode = *thisPtr;                // Root node from this->root
    int* result = nullptr;

    while (currentNode != nullptr && result == nullptr)
    {
        int nodeKey = *(int*)(currentNode + 0x10);  // +0x10: key
        if (*keyPtr < nodeKey)
        {
            // Go left subtree
            currentNode = *(int**)(currentNode + 0x8);
        }
        else
        {
            // Potential match or go right
            result = currentNode;
            if (nodeKey < *keyPtr)
            {
                // Go right subtree, reset result since not equal
                currentNode = *(int**)(currentNode + 0xC);
                result = nullptr;
            }
            // else exact match -> result remains currentNode, loop will exit
        }
    }
    return result;
}