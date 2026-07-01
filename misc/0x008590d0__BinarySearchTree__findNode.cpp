// FUNC_NAME: BinarySearchTree::findNode
// Address: 0x008590d0
// Role: Binary search tree lookup by key. Traverses tree rooted at this->root, stores found node pointer in outNode (or null if not found).

void __thiscall BinarySearchTree::findNode(int* outNode, uint* key) const
{
    int currentNode = this->root;  // *param_1
    int foundNode = 0;            // iVar3

    while (currentNode != 0 && foundNode == 0)
    {
        if (*key < *(uint*)(currentNode + 0x10))  // node->key
        {
            currentNode = *(int*)(currentNode + 8);  // node->left
            // foundNode remains 0
        }
        else if (*(uint*)(currentNode + 0x10) < *key)
        {
            currentNode = *(int*)(currentNode + 0xC);  // node->right
            // foundNode remains 0
        }
        else
        {
            foundNode = currentNode;  // key matches
        }
    }

    *outNode = foundNode;  // *param_2
}