// FUNC_NAME: LinkedListContainer::getNodeData
int __thiscall LinkedListContainer::getNodeData(void *this, int index)
{
    // this: pointer to container object
    // index: zero-based index into a singly linked list
    // Returns the data field at offset +0x14 of the node at the given index,
    // or -1 (0xFFFFFFFF) if the index is out of bounds or the list is empty.
    int result = -1;
    if (this != 0 && index >= 0)
    {
        int *next = *(int **)((int)this + 0x124); // head pointer at +0x124
        for (int i = 0; i < index; i++)
        {
            if (next == 0)
            {
                return -1;
            }
            next = *(int **)((int)next + 0x124); // next node pointer at +0x124
        }
        if (next != 0)
        {
            result = *(int *)((int)next + 0x14); // data field at +0x14
        }
    }
    return result;
}