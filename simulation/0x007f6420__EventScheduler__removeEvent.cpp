// FUNC_NAME: EventScheduler::removeEvent
void __thiscall EventScheduler::removeEvent(int thisPtr, uint eventId)
{
    uint bitMask = 1 << (eventId & 0x1f);
    // Check if the event is currently active in the bitfield at offset 0x8E0
    if ((*(uint *)(thisPtr + 0x8E0 + (eventId >> 5) * 4) & bitMask) != 0) {
        // Notify the registered event handler (vtable entry +0x28) with the constant 0x20
        (**(code **)(**(int **)(thisPtr + 0x58) + 0x28))(0x20);
    }
    // Clear the flag
    uint *flagWord = (uint *)(thisPtr + 0x8E0 + (eventId >> 5) * 4);
    *flagWord &= ~bitMask;
}