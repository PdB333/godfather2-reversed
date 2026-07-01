// FUNC_NAME: BucketManager::clearLinkedListsArray
// This function destroys all nodes in each linked list stored in an array of heads,
// then sets each head to null.
// Address: 0x0088faf0
// EA EARS engine – likely used for spatial buckets or object pooling.

void BucketManager::clearLinkedListsArray(uint arraySize)
{
    // Iterate over each bucket head in the array
    for (uint i = 0; i < arraySize; ++i)
    {
        // Get the head of the i-th linked list
        Node* node = *reinterpret_cast<Node**>(this + i * 4);  // +0x00 per slot (array of pointers)

        // Traverse and delete all nodes in this list
        while (node != nullptr)
        {
            Node* nextNode = reinterpret_cast<Node*>(node->next);  // offset +0x08: next pointer
            deleteNode(node);                                       // FUN_009c8f10: frees the node
            node = nextNode;
        }

        // Clear the head pointer
        *reinterpret_cast<uint32_t*>(this + i * 4) = 0;
    }
}