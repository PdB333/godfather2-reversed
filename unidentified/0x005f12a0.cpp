// FUN_NAME: RefCountedObject::release
// Address: 0x005f12a0
// This function appears to be a release/destructor for a ref-counted object.
// It takes 'this' in ESI and a pointer to a reference store in EDI (likely a linked list node or manager).
// It swaps a pointer, increments a counter, resets fields, and optionally calls a callback.

void __fastcall RefCountedObject::release(RefCountedObject* this, /* in ESI */ ReferenceNode* node /* in EDI */)
{
    // Lock or synchronization (probably spin lock or mutex acquire)
    lock();

    // If node is valid and has a non-zero count at +0x04
    if (node != nullptr && this != nullptr && node->count != 0) // +0x04
    {
        // Copy node's first dword to this (likely a pointer or ref)
        this->field_0 = node->field_0; // +0x00
        // Increment node's generation/epoch at +0x0C
        node->generation++; // +0x0C
        // Set node's first pointer to this (swap)
        node->field_0 = this;
    }

    // Reset this object's fields
    this->field_24 = -1;    // +0x18: sentinel/id
    this->field_16 = 0;     // +0x10: word (low part of dword)
    // Call deallocator with a word from +0x08 and function pointer at +0x24
    deallocate(this->field_08_word, this->callback); // +0x08, +0x24

    // If there is a callback, invoke it and clear
    if (this->callback != nullptr)
    {
        this->callback();
        this->callback = nullptr; // +0x24
        this->field_28 = 0;       // +0x28
        this->field_2C = 0;       // +0x2C
    }
}