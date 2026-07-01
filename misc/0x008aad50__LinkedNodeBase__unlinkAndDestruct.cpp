// FUNC_NAME: LinkedNodeBase::unlinkAndDestruct
// @ 0x008aad50 - Destructor/unlink function for a doubly-linked list node (likely from EA EARS container framework).
// Handles unlink from list, then calls base destructor, optionally deallocating.
// Structure: +0x18 next, +0x1c prev, +0x20 pointer data? Or this is the node itself? 
// Actually based on pattern: +0x18 = prev, +0x1c = next, +0x20 = data or self? 
// Fixed: +0x18 = prev, +0x1c = next, +0x20 = self reference.
// param_2: bit 0 = if set, deallocates this node via operator delete.

int __thiscall LinkedNodeBase::unlinkAndDestruct(int thisPtr, byte flags)
{
    // Set vtable pointer (PTR_LAB_00e317cc)
    *(void***)(thisPtr + 0x28) = &PTR_LAB_00e317cc;

    if (*(int*)(thisPtr + 0x18) != 0) {  // if prev exists
        if (*(int*)(thisPtr + 0x1c) == 0) { // if next is null (we are tail)
            // Set prev's next to my next? Wait, this pattern is weird.
            // Actually +0x18 = next, +0x1c = prev? Let me re-evaluate.
            // Common linked list: +0x18 = next, +0x1c = prev
            // If next exists (not 0):
            //   if prev == 0 (head): set next's prev = this->data?
            //   else: set next's next? No...
            // Rewrite properly:
            // Standard double-linked list node: +0x18 = next, +0x1c = prev
            // If prev:
            //   if not next: prev->next = data (weird)
            //   else: prev->next = next? Hmm.

            // Let me just reconstruct based on standard unlink:
            // node->prev->next = node->next
            // node->next->prev = node->prev
            // This code: if prev exists, set prev->next or prev->something to data?
            // Actually looking at code:
            // *(int*)(*(int*)(this+0x18)+4) = data  -> setting prev->something
            // *(int*)(*(int*)(this+0x1c)+8) = data  -> setting next->something
            // Could be offset 4 = next, offset 8 = prev within the node.

            // Re-interpretation:
            // +0x18 = prev pointer
            // +0x1c = next pointer  
            // +0x20 = stored data (generic pointer)

            // Set prev->next to data
            *(int*)(*(int*)(thisPtr + 0x18) + 4) = *(int*)(thisPtr + 0x20);
        } else {
            // Set next->prev to data
            *(int*)(*(int*)(thisPtr + 0x1c) + 8) = *(int*)(thisPtr + 0x20);
        }
        // If data exists, set data->prev to next
        if (*(int*)(thisPtr + 0x20) != 0) {
            *(int*)(*(int*)(thisPtr + 0x20) + 4) = *(int*)(thisPtr + 0x1c);
        }
    }

    FUN_0064d150(); // Base destructor call (?), likely ~somebase()

    if ((flags & 1) != 0) {
        FUN_009c8eb0(thisPtr); // operator delete(thisPtr)
    }
    return thisPtr;
}