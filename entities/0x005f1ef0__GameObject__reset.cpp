// FUNC_NAME: GameObject::reset
// Function at 0x005f1ef0: Reinitializes a GameObject to its default state and adds it to the global linked list.
// This may be called both from constructors and after destruction to recycle the object.

void __thiscall GameObject::reset()
{
    // Guard against null pointer
    if (this == nullptr)
        return;

    // Possibly enter a reset lock or sequence
    FUN_005f2230(1);

    // Check if there's a child object at offset 0x2C
    if (this->field_0x2C != nullptr)
    {
        // Clear its callback pointer at offset +8
        *reinterpret_cast<int*>(this->field_0x2C + 8) = 0;

        // If there's a resource at offset 0x08, release it
        if (this->field_0x08 != nullptr)
            FUN_005e4cf0();

        this->field_0x2C = nullptr;
    }

    // Zero out various fields (clearing state)
    this->field_0x08 = nullptr;
    this->field_0x30 = 0;         // +0x30
    this->field_0x68 = 0;         // +0x68
    this->field_0x60 = 0;         // +0x60
    this->field_0x34 = 0;         // +0x34

    // Static initialization
    FUN_005f57b0();

    // If global list is enabled, insert this object at head
    if (g_ObjectListEnabled != 0)
    {
        this->m_pNext = g_ObjectListHead;   // +0x00
        g_ObjectListCount++;                // +0x04 (implicit offset)
        g_ObjectListHead = this;
    }

    // Register the object with some subsystem using its own fields and a global byte
    FUN_005dbc10(this->field_0x64_byte,   // +0x64
                 this->field_0x5C,        // +0x5C
                 this->field_0x65_byte,   // +0x65
                 g_SomeGlobalByte);
}

// Global variables:
// g_ObjectListHead (DAT_011a0efc) - head of linked list of all GameObject instances
// g_ObjectListCount (DAT_011a0f08) - number of objects in the list
// g_ObjectListEnabled (DAT_011a0f00) - flag enabling list insertion
// g_SomeGlobalByte (DAT_011a0efa) - used in registration call