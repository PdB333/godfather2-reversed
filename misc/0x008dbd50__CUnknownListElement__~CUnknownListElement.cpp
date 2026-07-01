// FUNC_NAME: CUnknownListElement::~CUnknownListElement
int __thiscall CUnknownListElement::~CUnknownListElement(CUnknownListElement* this, byte deletingFlag)
{
    // Set vtable to the base class (or derived?) vtable pointer
    // This is typical in destructor chaining: switch to base vtable before calling base destructor
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc; // vtable for base class (or this class's base)

    // Remove this node from a linked list using three pointers:
    // +0x18: prev, +0x1c: next, +0x20: some other pointer (maybe list head or data)
    if (*(int*)(this + 0x18) != 0) { // if prev exists
        if (*(int*)(this + 0x1c) == 0) {
            // if next is null, set prev's field at +0x4 to the unknown pointer
            *(int*)(*(int*)(this + 0x18) + 0x4) = *(int*)(this + 0x20);
        } else {
            // else set next's field at +0x8 to the unknown pointer
            *(int*)(*(int*)(this + 0x1c) + 0x8) = *(int*)(this + 0x20);
        }
        if (*(int*)(this + 0x20) != 0) {
            // if unknown pointer exists, set its field at +0x4 to this->next
            *(int*)(*(int*)(this + 0x20) + 0x4) = *(int*)(this + 0x1c);
        }
    }

    // Call base class destructor (likely a linked list base or game object base)
    FUN_0064d150(); // CBase::~CBase() (or similar)

    // If the deletion flag is set, free memory
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete(this)
    }

    return (int)this; // scalar deleting destructor returns 'this'
}