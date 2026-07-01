// FUNC_NAME: PoolNode::initAndGetNext
// Address: 0x008b4100
// This function initializes a node in a fixed-size memory pool and returns a pointer to the next node (at offset +0x04).
// The inner function FUN_008b3dc0 likely sets up the node's data and links.
// Called repeatedly from initialization loops (0x008b4910, 0x008b50e0) to build a free list.

int PoolNode::initAndGetNext()
{
    // Call the internal initialization routine.
    // It receives both the address of 'this' and the this pointer itself.
    // This pattern suggests it writes a next pointer into the node's header.
    FUN_008b3dc0(&this, (int)this);
    // Return the address of the next node (located 4 bytes after this).
    // The node is likely part of a linked list where offset 0 is a pointer to the next node.
    return (int)this + 4;
}