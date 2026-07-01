// FUNC_NAME: NodeListDictionary::getValue

// Reconstructed from address 0x00890e40
// This function looks up an entry in a linked list of nodes (hash table bucket or simple list)
// Each node holds: +0x04 key, +0x08 next pointer, +0x0C elementCount, +0x10 dataArray[elementCount]
// Returns the value at param_3 index from the matching node, or 0 if not found/invalid index.

int NodeListDictionary::getValue(int key, unsigned int index) const
{
    // Start from the head of the list stored at this+0x0C
    Node* node = reinterpret_cast<Node*>(*(int*)(reinterpret_cast<const char*>(this) + 0x0C));

    while (node != nullptr)
    {
        // Check if key matches node->key (offset +0x04)
        if (*(int*)(reinterpret_cast<const char*>(node) + 0x04) == key)
        {
            // Key found; now check if index is within bounds (node->elementCount at +0x0C)
            if (index < *(unsigned int*)(reinterpret_cast<const char*>(node) + 0x0C))
            {
                // Return the value from the array at node+0x10 + index*4
                return *(int*)(reinterpret_cast<const char*>(node) + 0x10 + index * 4);
            }
            else
            {
                // Index out of bounds
                return 0;
            }
        }
        // Move to next node (offset +0x08 is next pointer)
        node = reinterpret_cast<Node*>(*(int*)(reinterpret_cast<const char*>(node) + 0x08));
    }

    // Key not found in the list
    return 0;
}