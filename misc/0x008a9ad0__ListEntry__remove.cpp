// FUNC_NAME: ListEntry::remove
int __thiscall ListEntry::remove(ListEntry* this, byte shouldDelete)
{
    // Set vtable to base class vtable to prevent virtual calls during destruction
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Remove this entry from the doubly linked list structure
    // Offsets: +0x18 = next, +0x1c = prev, +0x20 = somePointer (maybe parent or list head)
    ListEntry* next = *(ListEntry**)(this + 0x18);
    ListEntry* prev = *(ListEntry**)(this + 0x1c);
    ListEntry* somePointer = *(ListEntry**)(this + 0x20);

    if (next != 0) {
        if (prev == 0) {
            // Update next's field at +4 to point to somePointer
            *(ListEntry**)(next + 4) = somePointer;
        } else {
            // Update prev's field at +8 to point to somePointer
            *(ListEntry**)(prev + 8) = somePointer;
        }
    }
    if (somePointer != 0) {
        // Update somePointer's field at +4 to point to prev
        *(ListEntry**)(somePointer + 4) = prev;
    }

    // Call base class destructor
    FUN_0064d150();

    // If shouldDelete's lowest bit is set, free the memory
    if ((shouldDelete & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}