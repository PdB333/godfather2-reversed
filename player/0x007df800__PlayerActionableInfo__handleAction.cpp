// FUNC_NAME: PlayerActionableInfo::handleAction
// Function at 0x007df800: Dispatches player actions based on action ID (param_4).
// param_2, param_3, param_5 are additional parameters passed to the default handler.
// The class likely represents a per-player action state, with a pointer at +0x58 to a large flag/data structure.
// +0x58: pointer to a data structure (e.g., PlayerActionData)
// +0x8e0: within that structure, a 32-bit bitfield (action flags)
// Cases:
//   0x13 (19): check bit 10 of the flag dword (e.g., canPerformAction)
//   0x14 (20): static helper function FUN_007df190 (returns availability/status)
//   0x15 (21): static helper function FUN_007df630 (returns something)
//   0x16 (22): attempt to create an action object (size 0x38), return success
//   default: delegate to generic handler FUN_007ab790

bool __thiscall PlayerActionableInfo::handleAction(void *this, uint32_t param_2, uint32_t param_3, uint32_t actionId, uint32_t param_5)
{
    bool result;
    uint32_t *flagsPtr; // pointer to the nested flag structure

    switch(actionId) {
    case 0x13: // Action ID 19: check a specific flag bit
        // Dereference this+0x58 to get pointer to a larger structure, then read dword at +0x8e0; check bit 10
        flagsPtr = *(uint32_t **)((char *)this + 0x58); // +0x58: pointer to flags/data
        return ((*(flagsPtr + 0x238) >> 0xA) & 1) == 1; // +0x8e0 / 4 = 0x238 (dword index)
        // Note: 0x8e0 is byte offset, so dword offset = 0x8e0/4 = 0x238
    case 0x14: // Action ID 20: delegate to a static function
        return (bool)FUN_007df190();
    case 0x15: // Action ID 21: delegate to another static function
        return (bool)FUN_007df630();
    case 0x16: // Action ID 22: attempt to create a new action object (size 0x38)
        break; // fall through to creation logic below
    default:
        // For all other action IDs, call a generic dispatcher (likely base class or global handler)
        return (bool)FUN_007ab790(param_2, param_3, actionId, param_5);
    }

    // Handle case 0x16: allocate memory for an action object (size 0x38 = 56 bytes)
    void *actionObj = (void *)FUN_00798f50(0x38); // e.g., operator new(56)
    bool canCreate = FUN_0079e920(actionObj); // e.g., some validation or constructor check
    if (canCreate == false) {
        return false;
    }
    return true;
}