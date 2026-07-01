// FUNC_NAME: Sentient::canExecuteAction
bool __thiscall Sentient::canExecuteAction(Sentient* this, int param_2, undefined4 param_3, undefined4 param_4)
{
    uint flags = *(uint*)((int)this + 0x18c); // +0x18c: bitfield flags (bit12=canAct?, bit11=isBusy?, bit13=isStunned?)
    bool result = true;

    if ((flags >> 0xc & 1) == 0) {
        // Bit 12 clear: entity is not in a state that restricts actions
        if (param_2 == 0) {
            return true;
        }
        // Delegate to a generic action check (possibly animation or command validation)
        result = FUN_00471990(param_2, param_3, param_4);
        return result;
    }

    // Bit 12 set: entity is in a restricted state
    if ((flags >> 0xb & 1) == 0) {
        // Bit 11 clear: not busy, so allow action
        return true;
    }

    // Bit 11 set: entity is busy
    if ((flags >> 0xd & 1) != 0) {
        // Bit 13 set: entity is stunned or incapacitated, block action
        return true;
    }

    // Entity is busy but not stunned: attempt to interrupt current action
    FUN_005403e0(200); // Start a 200ms timer (maybe for action timeout)

    if (param_2 != 0) {
        char byteAtParam2_0x15E = *(char*)(param_2 + 0x15e);
        if (byteAtParam2_0x15E >= 0) {
            int lookupResult = FUN_006c9470(param_2, 0x383225a1); // Hash lookup (e.g., animation name hash)
            if (lookupResult != 0) {
                goto LAB_008bbb27;
            }
            // If lookup fails, call a function to set up the new action
            FUN_008b9a60(param_2, param_4);
        }
    }

    // Clear any pending action state
    FUN_008bb780();
    result = false;

LAB_008bbb27:
    FUN_00540410(200); // Stop the 200ms timer
    return result;
}