// FUNC_NAME: StateMachine::handleFlagTransition
// Purpose: Evaluate and clear state flags at +0x0C, potentially setting a high-priority flag
//          before calling performTransition.  This is typically called from an update loop.

class StateMachine {
public:
    // +0x0C: uint32_t flags - bitfield controlling state transitions
    // +0x10: SomeObject* parentObj - linked object for additional conditions

    void handleFlagTransition() {
        uint32_t flags = *(uint32_t*)(this + 0x0C);

        // Check if bit 18 (0x40000) is set -> indicates a pending state change
        if ((flags & 0x40000) != 0) {
            // Clear bit 18 by default
            *(uint32_t*)(this + 0x0C) = flags & ~0x40000;

            // If bit 19 (0x80000) is also set, clear both bits 18 and 19
            // and possibly set bit 31 under additional conditions
            if ((flags & 0x80000) != 0) {
                // Clear bits 18 and 19 (mask = 0xFFF3FFFF = ~0xC0000)
                *(uint32_t*)(this + 0x0C) = flags & ~0xC0000;

                // Condition: bit 0 (enabled) is set AND a flag in parentObj is set
                if ((flags & 1) != 0) {
                    SomeObject* obj = *(SomeObject**)(this + 0x10);
                    if (obj && (*(uint32_t*)(obj + 0x14) & 0x20000000) != 0) {
                        // Set bit 31 (0x80000000) - high-priority action flag
                        *(uint32_t*)(this + 0x0C) = (flags & ~0xC0000) | 0x80000000;
                    }
                }
            }
            // Complete the transition by calling the associated action
            performTransition();
        }
    }

private:
    // Called after flags are updated to execute the actual transition logic
    void performTransition();
};