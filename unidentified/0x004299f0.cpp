// FUN_004299f0: ObjectList::Clear
#include <cstdint>

// ObjectList manages a linked list of nodes stored in an array of pointers.
// Structure layout (offsets relative to 'this' pointer):
//   +0x00: Pointer to internal data block (pData)
//   +0x04: head index (reset to 0 on clear)
//   +0x08: max number of slots in the node pointer array
//   +0x0C: (unused)
//   +0x10: current count of active nodes
//
// The internal data block (pData) has the following layout:
//   +0x00: (unused)
//   +0x04: (unused)
//   +0x08: Pointer to the base of the node pointer array (array of Node*)
// Each node structure (Node) has:
//   +0x00: Some data pointer (used in processing)
//   +0x04: Padding or pointer
//   +0x08: Next node pointer (singly linked list)

void ObjectList::Clear()
{
    // Get the base of the node pointer array from internal data block
    Node** arrayBase = *reinterpret_cast<Node***>(reinterpret_cast<uint8_t*>(this->pData) + 8); // pData + 8 points to array base pointer
    // Traverse the list starting from the first node (head)
    Node* currentNode = *arrayBase; // first element of array = head node pointer

    while (currentNode)
    {
        // Read next node pointer before freeing current
        Node* nextNode = *reinterpret_cast<Node**>(reinterpret_cast<uint8_t*>(currentNode) + 8); // +0x08 = next pointer
        // Process and free the current node's data
        this->ProcessNodeData(*reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(currentNode) + 8)); // +0x08 used as data? (original uses +0x08)
        this->FreeNode(currentNode);
        // Decrement the active count
        this->count--;
        // Move to next node
        currentNode = nextNode;
    }

    // Zero out the entire node pointer array
    for (uint32_t i = 0; i < static_cast<uint32_t>(this->maxSlots); i++)
    {
        arrayBase[i] = nullptr;
    }
    // Reset head index
    this->headIndex = 0;
}