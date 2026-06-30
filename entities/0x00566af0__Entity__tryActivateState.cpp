// FUNC_NAME: Entity::tryActivateState
// Address: 0x00566af0
// Role: Checks conditions and transitions to a new state if allowed.
// Condition logic:
//   - Bit6 of flags at +0x2c must be 0 (not in cooldown/pause)
//   - Bit4 of flags must be 1 (active)
//   - Either Bit2 is 1 (has pending task) OR (Bit7 is 1 (idle) AND target at +0x20 is NULL)
// On success: resets state byte at +0x14, sets bit6 in flags, sets status at +0x10 to 1,
//             calls onStateEnter() if timer at +0xc is zero, then calls onStateUpdate()

typedef unsigned int uint;

struct Entity {
    /* +0x00 */ void* vtable;               // usually first field
    /* +0x04 */ int field_0x4;
    /* +0x08 */ int field_0x8;
    /* +0x0c */ int timer;                  // countdown or state timer
    /* +0x10 */ int status;                 // action status (1 = active)
    /* +0x14 */ unsigned char stateByte;     // sub-state or animation flag
    /* +0x18 */ int field_0x18;
    /* +0x1c */ int field_0x1c;
    /* +0x20 */ Entity* target;             // current target or interaction partner
    /* +0x24 */ int field_0x24;
    /* +0x28 */ int field_0x28;
    /* +0x2c */ uint flags;                 // bitfield: bit4=active, bit6=pause, bit2=hasTask, bit7=idle
};

// Forward declarations for called functions
void onStateEnter();           // FUN_00566d90
void onStateUpdate();          // FUN_00566e90

int __thiscall Entity::tryActivateState(Entity* this) {
    uint flags = this->flags;
    int result = 0;

    // Check activation conditions
    if (((flags >> 6 & 1) == 0) &&          // not paused
        ((flags >> 4 & 1) != 0) &&          // is active
        ((flags >> 2 & 1) != 0 ||           // has pending task
         (((flags >> 7 & 1) != 0 &&          // is idle
           this->target == 0))))             // no target
    {
        this->stateByte = 0;                 // reset sub-state
        this->flags = flags | 0x40;          // set pause/cooldown bit
        this->status = 1;                    // mark state as active

        if (this->timer == 0) {
            onStateEnter();                  // initialize state
        }
        onStateUpdate();                     // perform state update
        result = 1;                          // success
    }
    return result;
}