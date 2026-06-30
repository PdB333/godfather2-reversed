// FUNC_NAME: EARSObject::propagateEvent
void __thiscall EARSObject::propagateEvent(uint eventMask, bool stopAtChildren) {
    // +0x40: eventInputMask – mask of events this object propagates to children
    if (*(uint*)(this + 0x40) & eventMask) {
        // +0x20: pointer to head of child list (linked list)
        // +0x28: 'next' pointer offset within each child
        for (int child = *(int*)(this + 0x20); child != 0; child = *(int*)(child + 0x28)) {
            ((EARSObject*)child)->propagateEvent(eventMask, stopAtChildren);
        }
        // If stopAtChildren is true, do not set local flag after processing children
        if ((char)stopAtChildren != 0) {
            return;
        }
    }
    // +0x3C: eventOutputMask – mask of events this object wants to accumulate locally
    // +0x38: activeEvents – bitfield of currently active event flags
    if (*(uint*)(this + 0x3C) & eventMask) {
        *(uint*)(this + 0x38) |= eventMask;
    }
}