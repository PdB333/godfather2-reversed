// FUNC_NAME: setClampedTimerValue

// 0x006063b0 - Sets a 12-bit value in global timer array with clamping and sync.
// Parameters:
//   value in EAX - timer value (0xFFFFFFFF mapped to 0xFFF)
//   index in EDI - target slot in gTimerValues array
// Uses global gTimerOverrideFlag (DAT_011a0f28) to conditionally skip update when value is 0.

void setClampedTimerValue(void)
{
    uint value;
    int timerIndex;
    
    // Clamp invalid sentinel value (likely -1) to maximum 0xFFF (4095)
    if (in_EAX == 0xffffffff) {
        in_EAX = 0xfff;
    }
    
    // Branching based on value and global game state flag
    if (in_EAX == 0) {
        if (gTimerOverrideFlag != 0x04) {   // DAT_011a0f28: game state flag (4 = paused/suspended)
            goto doUpdate;
        }
    }
    else if (in_EAX > 0xfff) {
        goto doUpdate;
    }
    
    // Normal path: sync and store
    FUN_00618d40();                          // likely markDirty() or applyUpdate()
    (&gTimerValues)[unaff_EDI] = in_EAX;    // DAT_011d912c: global timer array
    return;

doUpdate:
    FUN_00618d40();
    (&gTimerValues)[unaff_EDI] = in_EAX;
    return;
}