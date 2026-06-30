// FUNC_NAME: SimObject::processChildren
// Function address: 0x00624d20
// Recursively processes a child list, calling a virtual method on each child, then either releases
// the child (vtable+0x4) or marks it for deletion (flag bit 1). The list head is stored at +0x20.

void __fastcall SimObject::processChildren(SimObject* this) {
    SimObject* child = this->childList;                 // +0x20: linked list head
    while (child != nullptr) {
        SimObject::processChildren(child);               // recursive processing of child's children

        // Call virtual method on parent (this) to process the child, vtable offset 0x1c
        (this->vtable->processChild)(child);             // e.g. remove from list or update state

        // Check child flags at +0x14 (word at child[5] as int*)
        if ((child->flags & 1) == 0) {
            // Flag 0 clear: call finalization virtual on child with arg 1, vtable offset 0x4
            (child->vtable->finalize)(1);                // release or delete
        } else {
            // Flag 0 set: mark flag 1 (pending deletion or removal)
            child->flags |= 2;
        }

        child = this->childList;                         // re-fetch head (previous child may have been removed)
    }
}