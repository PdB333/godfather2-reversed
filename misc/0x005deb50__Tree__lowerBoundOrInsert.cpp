// FUNC_NAME: Tree::lowerBoundOrInsert
int* Tree::lowerBoundOrInsert(Tree* this, int* outputPair, uint* key)
{
    Node* node = *(Node**)((int)this + 0x1c); // +0x1c: root or header node
    bool goRight = true;

    // Traverse down the tree to find insertion point
    if (*(char*)((int)node->parent + 0x15) == '\0') // parent sentinel? check color at +0x15
    {
        Node* child = node->parent; // treat parent as child pointer? This logic is unclear
        do
        {
            node = child;
            goRight = *key < node->key; // node->key is at offset 12 (local_4[3])
            if (goRight)
            {
                child = node->left; // left child at offset 0
            }
            else
            {
                child = node->right; // right child at offset 8 (local_4[2])
            }
        } while (*(char*)((int)child + 0x15) == '\0'); // check sentinel color
    }

    int resultNode = (int)this; // placeholder for new node
    if (goRight)
    {
        // If we went right and reached the leftmost leaf, insert new node
        if (node == *(Node**)*(int*)((int)this + 0x1c)) // root?
        {
            int* newNode = (int*)Tree::insertNewNode(this, &resultNode, 1, key); // call insert helper
            outputPair[0] = newNode[0];
            outputPair[1] = newNode[1];
            *(char*)(outputPair + 2) = 1; // inserted
            return outputPair;
        }
        // Otherwise, something else (maybe rebalance or error)
        Tree::rebalanceOrError();
    }

    // If existing key found
    if (node->key < *key)
    {
        int* newNode = (int*)Tree::insertNewNode(this, &resultNode, 0, key); // bVar4 = false?
        outputPair[0] = newNode[0];
        outputPair[1] = newNode[1];
        *(char*)(outputPair + 2) = 1; // inserted
        return outputPair;
    }

    // Key already exists, return pointer to existing node and false flag
    outputPair[0] = resultNode;
    outputPair[1] = (int)node;
    *(char*)(outputPair + 2) = 0; // not inserted
    return outputPair;
}