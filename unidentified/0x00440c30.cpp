// FUN_00440c30: TimerObject::tick
// Decrements a short timer at offset 0x16 and calls a global tick function.
void __thiscall TimerObject::tick()
{
    // Call global timer update function (FUN_00440b80) with argument 1
    FUN_00440b80(1); // Address 0x00440b80

    // Decrement the timer value stored at offset 0x16 (2 bytes)
    *reinterpret_cast<short*>(reinterpret_cast<uint8_t*>(this) + 0x16) -= 1;
}