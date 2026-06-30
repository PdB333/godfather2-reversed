// FUNC_NAME: LinearAllocator::allocateAligned

// Line 0x0065bd60 - Linear allocator with linked list of fixed-size nodes.
// Node structure (0xc bytes):
//   +0x0: Node* prevNode
//   +0x4: char* bufferBase
//   +0x8: int currentOffset
//
// LinearAllocator class (this = unaff_ESI) fields:
//   +0x0: Node* headNode
//   +0x4: int defaultBufferSize

int __thiscall LinearAllocator::allocateAligned(int this, int size)
{
    int alignedSize;
    Node* newNode;
    int nodeSlot;
    int oldOffset;
    Node* currentNode;

    // Check if we need a new node
    currentNode = *(Node**)this;
    if ((currentNode == nullptr) || 
        (currentNode->currentOffset + size > *(int*)(this + 4))) // defaultBufferSize
    {
        // Allocate a new node
        newNode = (Node*)FUN_009c8e50(12); // allocate node structure
        if (newNode != nullptr)
        {
            newNode->bufferBase = (char*)FUN_009c8e80(*(int*)(this + 4)); // allocate buffer of default size
        }
        else
        {
            newNode = nullptr;
        }
        newNode->prevNode = currentNode; // link previous node
        newNode->currentOffset = 0;       // reset offset
        *(Node**)this = newNode;          // update head
    }

    currentNode = *(Node**)this;
    oldOffset = currentNode->currentOffset;
    // Align size up to 4 bytes
    alignedSize = (size + 3) & 0xFFFFFFFC;
    currentNode->currentOffset = oldOffset + alignedSize;
    return (int)(currentNode->bufferBase) + oldOffset;
}