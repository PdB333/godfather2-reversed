// FUNC_NAME: EADelayedInitObject::onProcessDelayedTick
class EADelayedInitObject {
public:
    // Virtual function table at +0x00
    // Offset 0x130 in vtable: some callback (e.g., onDelayedAction)
    // Offset 0x130 in object (param_1[0x4c]): a pointer or counter indicating pending action
    // Offset 0x184 (param_1[0x61] bit 6): flag indicating object should be added to global delayed list
    // Offset 0x161: one-byte counter for delay ticks

    // Called each frame/update; handles queuing and triggering delayed initialization
    void __fastcall onProcessDelayedTick() {
        // Check if bit 6 (0x40) of flags at offset 0x184 is set
        if (m_delayedFlags & 0x40) {
            // Global structure at 0x01206880 manages a dynamic list of delayed objects
            // Offset 0x14 is a pointer to the current insertion slot (int**)
            int** listSlot = (int**)(*(int*)0x01206880 + 0x14); // pointer to head pointer
            // Initialize the slot with a static sentinel (start of list)
            *listSlot = &PTR_LAB_0110b938; // static sentinel address
            // Advance one slot for this object
            (*listSlot)++; // move to next 4-byte slot
            **(int***)listSlot = this; // store this object pointer
            (*listSlot)++; // advance to next empty slot
            // Clear the flag so this object isn't added again
            m_delayedFlags &= ~0x40;
        }

        // Increment the delay counter at offset 0x161
        char& counter = *(char*)(this + 0x161); // actually: (char*)((int)this + 0x161)
        char previous = counter;
        counter = previous + 1;

        // On the first tick after the counter was zero, if there is a pending action
        // (field at offset 0x130 is non‑zero), call the virtual callback at vtable+0x130
        if (previous == 0 && *(int*)(this + 0x130) != 0) {
            (*(void (__thiscall**)(EADelayedInitObject*))(* (int*)this + 0x130))(this);
        }
    }

private:
    // Placeholder for the actual structure; offsets are as discovered by Ghidra
    char _pad0[0x130]; // up to offset 0x130 (field: pendingActionPtr or counter)
    int m_pendingAction; // +0x130
    char _pad1[0x2E]; // up to 0x161
    char m_delayCounter; // +0x161
    char _pad2[0x22]; // up to 0x184
    int m_delayedFlags; // +0x184
};