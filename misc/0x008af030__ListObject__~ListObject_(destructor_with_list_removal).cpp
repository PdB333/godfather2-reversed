// FUNC_NAME: ListObject::~ListObject (destructor with list removal)
void __fastcall ListObject::~ListObject(int this)
{
    // Call base class destructor (likely at 0x004bc280) and deallocator (0x0064d150)
    someBaseDestructor();
    
    // Set vtable pointer to the static vtable at 0x00e317cc for this class
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;
    
    // Unlink this node from a doubly linked list.
    // Offsets: +0x18 = pNext, +0x1c = pPrev, +0x20 = listHead (or some sentinel)
    if (*(int*)(this + 0x18) != 0) {
        if (*(int*)(this + 0x1c) == 0) {
            // pPrev is null: first node in list, update listHead->pPrev to point to pNext's head?
            *(int*)(*(int*)(this + 0x18) + 4) = *(int*)(this + 0x20);
        } else {
            // pPrev not null: update pPrev->pNext (offset +8) to point to pNext's head?
            *(int*)(*(int*)(this + 0x1c) + 8) = *(int*)(this + 0x20);
        }
        if (*(int*)(this + 0x20) != 0) {
            // Update head's pPrev (offset +4) to point back to pPrev
            *(int*)(*(int*)(this + 0x20) + 4) = *(int*)(this + 0x1c);
        }
    }
    
    // Call deallocation routine (likely operator delete or memory manager free)
    someDealloc();
    return;
}