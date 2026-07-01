// FUNC_NAME: SomeClass::~SomeClass
int SomeClass::~SomeClass(byte flags)
{
    // Set vtable to a special destructor vtable (to avoid further virtual calls)
    *reinterpret_cast<void***>(this + 0x28) = &PTR_LAB_00e317cc;

    // Unlink this node from the list/tree structure
    // Offsets: +0x18 = prev, +0x1c = next, +0x20 = data object pointer
    Node* prev = *reinterpret_cast<Node**>(this + 0x18);
    Node* next = *reinterpret_cast<Node**>(this + 0x1c);
    void* data = *reinterpret_cast<void**>(this + 0x20);

    if (prev != nullptr)
    {
        if (next == nullptr)
        {
            // Update prev's field at +0x04 to point to data
            *reinterpret_cast<void**>(prev + 0x04) = data;
        }
        else
        {
            // Update next's field at +0x08 to point to data
            *reinterpret_cast<void**>(next + 0x08) = data;
        }

        if (data != nullptr)
        {
            // Update data's field at +0x04 to point to next node
            *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(data) + 0x04) = next;
        }
    }

    // Call base class destructor (likely an EARS framework base)
    baseDestructor();

    // If flags indicate memory deallocation, call operator delete
    if (flags & 1)
    {
        operatorDelete(this);
    }

    return reinterpret_cast<int>(this);
}