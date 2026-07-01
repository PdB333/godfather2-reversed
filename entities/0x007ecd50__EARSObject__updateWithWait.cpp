// FUNC_NAME: EARSObject::updateWithWait
void EARSObject::updateWithWait(int thisPtr)
{
    short remainingWait;
    
    remainingWait = *(short *)(thisPtr + 0x1a); // +0x1a: wait/hold timer (ticks)
    *(undefined ***)(thisPtr + 8) = &PTR_FUN_00d6ffac; // +0x08: vtable pointer, likely set to some "updating" state
    
    while (remainingWait != 0) {
        FUN_00408090(); // likely EARSObject::processWaitTimer or similar helper that decrements the timer
        remainingWait = *(short *)(thisPtr + 0x1a);
    }
    
    // Check if there's a pending callback/continuation and it hasn't been cancelled
    if ((*(undefined4 **)(thisPtr + 0x10) != (undefined4 *)0x0) && // +0x10: callback/continuation function pointer
       ((*(byte *)(thisPtr + 0x20) & 1) == 0)) { // +0x20: flags, bit 0 = cancelled flag
        // Execute the continuation callback
        (**(code **)**(undefined4 **)(thisPtr + 0x10))();
        return;
    }
    return;
}