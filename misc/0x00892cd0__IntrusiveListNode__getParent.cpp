// FUNC_NAME: IntrusiveListNode::getParent
int __thiscall IntrusiveListNode::getParent()
{
    // Offset +0x14 holds a pointer to a child node embedded in a parent structure.
    // Subtract 0x48 to recover the parent object's base address.
    int* childPtr = *(int**)((int)this + 0x14);
    if (childPtr != nullptr)
    {
        return (int)childPtr - 0x48;
    }
    return 0;
}