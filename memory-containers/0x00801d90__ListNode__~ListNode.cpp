// FUNC_NAME: ListNode::~ListNode

int __thiscall ListNode::~ListNode(int this, byte flags)
{
    // Set vtable to base class vtable (0x00e317cc)
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Remove this node from a doubly linked list structure
    // Offsets: +0x18 = prev, +0x1c = next, +0x20 = data (or list head)
    int* prev = *(int**)(this + 0x18);
    int* next = *(int**)(this + 0x1c);
    int* data = *(int**)(this + 0x20);

    if (prev != 0)
    {
        if (next == 0)
        {
            // If no next, update prev's next pointer (offset +4) to data
            *(int**)(prev + 4) = data;
        }
        else
        {
            // If next exists, update next's prev pointer (offset +8) to data
            *(int**)(next + 8) = data;
        }

        if (data != 0)
        {
            // Update data's next pointer (offset +4) to next
            *(int**)(data + 4) = next;
        }
    }

    // Call base class destructor
    FUN_0064d150();

    // If flags bit 0 is set, deallocate memory
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return this;
}