// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x008a9560
// Role: Destructor for a class that is part of a doubly linked list. Removes this node from the list, calls base destructor, and optionally deallocates memory.

struct SomeClass {
    // +0x00: unknown (size 0x18)
    // +0x18: pointer to previous node in list (or null)
    void* m_pPrev;
    // +0x1c: pointer to next node in list (or null)
    void* m_pNext;
    // +0x20: pointer to some data (or null)
    void* m_pData;
    // +0x24: unknown (size 4)
    // +0x28: vtable pointer
    void** vtable;
};

// Base class destructor (likely EARSObject or similar)
void __thiscall BaseClassDestructor(void* this);

// Custom deallocation function (likely operator delete)
void __thiscall Deallocate(void* this);

int __thiscall SomeClass::~SomeClass(void* this, byte deleteFlag) {
    // Set vtable to base class vtable (for proper destruction chain)
    *(void***)((int)this + 0x28) = &PTR_LAB_00e317cc;

    // Remove this node from the linked list
    if (*(void**)((int)this + 0x18) != 0) {
        if (*(void**)((int)this + 0x1c) == 0) {
            // No next node: update previous node's "next" pointer (offset +4)
            *(void**)(*(int*)((int)this + 0x18) + 4) = *(void**)((int)this + 0x20);
        } else {
            // Has next node: update next node's "prev" pointer (offset +8)
            *(void**)(*(int*)((int)this + 0x1c) + 8) = *(void**)((int)this + 0x20);
        }
        if (*(void**)((int)this + 0x20) != 0) {
            // Update data node's "next" pointer (offset +4) to point to next node
            *(void**)(*(int*)((int)this + 0x20) + 4) = *(void**)((int)this + 0x1c);
        }
    }

    // Call base class destructor
    BaseClassDestructor(this);

    // If deleteFlag is set, deallocate memory
    if ((deleteFlag & 1) != 0) {
        Deallocate(this);
    }

    return (int)this;
}