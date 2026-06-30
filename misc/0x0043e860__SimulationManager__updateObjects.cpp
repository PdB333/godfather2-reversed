// FUNC_NAME: SimulationManager::updateObjects

/**
 * Iterates through a circular doubly-linked list of registered objects,
 * calling a virtual method on each. The list head is stored at this+0x38.
 * Each object has its list node embedded at offset 0 (prev, next).
 * The virtual method called is the third entry in the vtable (offset +8),
 * and receives the value stored at this+0x18 as its argument.
 * The function ends by clearing this+0x18 and calling a cleanup function.
 */
void __fastcall SimulationManager::updateObjects(SimulationManager* this) {
    // List sentinel node: prev and next both point to itself when empty.
    // The sentinel is stored at this->listHead (offset +0x38)
    ListNode* sentinel = *(ListNode**)((char*)this + 0x38);   // +0x38: pointer to sentinel node
    ListNode* current = sentinel->prev;                       // start from sentinel's prev (last node)

    // Loop iteration: go until we wrap back to sentinel
    while (true) {
        // Debug: assert this pointer is valid (not -0x20)
        if ((int)this == -0x20) {
            debugBreak();   // FUN_00b97aea
        }
        // If we have reached the sentinel, break
        if (current == sentinel) break;

        // Debug check again
        if ((int)this == -0x20) {
            debugBreak();
        }

        // current->next points to the next node (which is the first object in a non-empty list)
        SimObject* obj = current->next;   // +4: next field (actually object pointer in original code: piVar3[1])

        // Verify the object is not the sentinel itself
        if ((obj == (SimObject*)sentinel) && (debugBreak(), obj == (SimObject*)sentinel)) {
            debugBreak();
        }

        // Call obj->vfunc2( this->someValue )
        // The vtable is at obj+8, third virtual function is at vtable[2]
        (obj->vtable[2])( this->someValue );   // someValue at +0x18

        // Debug check after call
        if ((int)this == -0x20) {
            debugBreak();
        }

        // Advance to the object itself (since obj was taken from current->next,
        // and then current becomes that object's address)
        // This effectively moves current to the object, but the loop will check
        // if current == sentinel on next iteration.
        current = (ListNode*)obj;

        // Debug: assert we haven't wrapped around unexpectedly
        if (current == sentinel) {
            debugBreak();
        }
    }

    // Cleanup: call some finalizer and clear the value at +0x18
    cleanupFunction();   // FUN_006278d0
    *(int*)((char*)this + 0x18) = 0;
}