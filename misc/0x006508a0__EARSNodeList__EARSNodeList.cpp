// FUNC_NAME: EARSNodeList::EARSNodeList
// Function at 0x006508a0 - Constructor for a node list container with vtable and linked list cleanup
// Uses placement delete flag (param_2 & 1)
undefined4 * __thiscall EARSNodeList::EARSNodeList(undefined4 *this, byte aFlag)
{
    undefined4 *nextNode;
    undefined4 *currentNode;
    
    // Set up two vtable pointers (possibly multiple inheritance)
    this[6] = &PTR_LAB_00e317cc;  // +0x18: second vtable
    *this = &PTR_LAB_00e42de4;    // +0x00: first vtable
    
    // Initialize the linked list: clear all nodes starting from head (offset +0x04)
    currentNode = (undefined4 *)this[1];
    while (currentNode != (undefined4 *)0x0) {
        nextNode = (undefined4 *)currentNode[2];
        *currentNode = 0;          // node->field0 = nullptr
        currentNode[1] = 0;        // node->field4 = nullptr
        currentNode[2] = 0;        // node->next = nullptr
        currentNode = nextNode;
    }
    
    // If the flag's lowest bit is set, call the custom deallocator (likely pool free)
    if ((aFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    return this;
}