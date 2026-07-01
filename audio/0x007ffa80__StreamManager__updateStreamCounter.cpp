// FUNC_NAME: StreamManager::updateStreamCounter
// 0x007ffa80 - updates a lock counter and state flags, then logs or broadcasts event
// Used for stream resource locking/unlocking in EARS engine.
// this +0x5fc: lock counter (int32)
// this +0x1b94: state flags (uint32), bits 0x60000 = 0b0110_0000_0000_0000_0000_0000 (two bits)
// DAT_0112d860: global stream manager context or event name
// DAT_00d71b00: global parameter
// FUN_00440590: likely a debug print or event dispatcher (void func(void*, void*, int, int, int))

void __fastcall StreamManager::updateStreamCounter(int thisPtr)
{
    int* lockCounter = (int*)(thisPtr + 0x5fc);
    *lockCounter = *lockCounter + 1;

    if (*lockCounter == 0) {
        // counter wrapped to zero -> clear lock flags
        *(unsigned int*)(thisPtr + 0x1b94) &= 0xfff9ffff;
    } else {
        // set flags to indicate active lock
        *(unsigned int*)(thisPtr + 0x1b94) |= 0x60000;
    }

    // notify stream manager or log event
    FUN_00440590(&DAT_0112d860, (void*)(thisPtr + 0x3c), DAT_00d71b00, 0, 4);
}