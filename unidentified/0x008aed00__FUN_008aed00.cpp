// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x008aed00
// Destructor for a class that is part of a doubly linked list.
// Removes this node from the list and optionally frees memory.

int __thiscall SomeClass::~SomeClass(void* this, byte deleteFlag)
{
    // Call base class destructor (likely at 0x00407430)
    FUN_00407430();

    // Set vtable pointer to this class's vtable (0x00e317cc)
    *(void***)((int)this + 0x28) = &PTR_LAB_00e317cc;

    // Linked list removal: this node has prev at +0x18, next at +0x1c, and a value pointer at +0x20.
    // The list nodes have next at +4 and prev at +8.
    // When this node is destroyed, it replaces itself in the list with the value object.
    int* prev = *(int**)((int)this + 0x18);
    int* next = *(int**)((int)this + 0x1c);
    int* value = *(int**)((int)this + 0x20);

    if (prev != 0) {
        if (next == 0) {
            // No next node: set prev->next = value
            *(int**)((int)prev + 4) = value;
        } else {
            // Next exists: set next->prev = value
            *(int**)((int)next + 8) = value;
        }
        if (value != 0) {
            // Set value->next = next
            *(int**)((int)value + 4) = next;
        }
    }

    // Call another cleanup function (likely at 0x0064d150)
    FUN_0064d150();

    // If deleteFlag is set, free the memory (operator delete at 0x009c8eb0)
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return (int)this;
}