// FUNC_NAME: EARSObject::destroy
void __thiscall EARSObject::destroy(void)
{
    uint flags;

    // Clear lowest bit (bit 0) and highest bit (bit 31) of the flags
    flags = this->flags & 0x7ffffffe;
    this->flags = flags;

    // If the "registered" flag (bit 17) is not set, set it and call a helper
    if ((flags & 0x20000) == 0) {
        this->flags = flags | 0x20000;
        EARSObject::onDestroy(); // FUN_0051b120: probably a virtual notify
    }

    // Clear bit 18 (0x40000) – maybe a "pending deletion" flag
    this->flags = this->flags & 0xfffbffff;

    // Null out and delete the callback pointer (+0x08)
    if (this->callbackPtr != nullptr) {
        *this->callbackPtr = 0;
        this->callbackPtr = nullptr;
    }

    // Iterate global list of objects that belong to this instance
    // DAT_01205514 is the head of a singly linked list with 'nextPtr' at +0x14
    // and 'ownerPtr' at +0x18
    for (EARSObject* child = g_objectListHead; child != nullptr; child = child->nextPtr) {
        if (child->ownerPtr == this) {
            destroy(child); // Recursively destroy the child
        }
    }
}