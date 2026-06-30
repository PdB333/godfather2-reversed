// FUNC_NAME: EventDispatcher::dispatchMessage
void __thiscall EventDispatcher::dispatchMessage(EventDispatcher* this, uint32_t messageHash)
{
    // Group 1: hashes that check handler at +0x20f0
    if (messageHash < 0x4937909f) {
        if (messageHash == 0x4937909e || messageHash == 0x2fd81222) {
            // +0x20f0: pointer to first event handler/flag
            if (*(int*)((uint8_t*)this + 0x20f0) != 0) {
                FUN_007fff40();  // process or forward event
            }
        }
        else if (messageHash == 0x23f3d3fd) {
            goto check_20f8;
        }
        // else ignore
    }
    else {
        // Group 2: hashes 0x7b35500e, 0xb6988728
        if (messageHash != 0x7b35500e && messageHash != 0xb6988728) {
            return;
        }
check_20f8:
        // +0x20f8: pointer to second event handler/flag
        if (*(int*)((uint8_t*)this + 0x20f8) != 0) {
            FUN_007fff40();
        }
    }
}