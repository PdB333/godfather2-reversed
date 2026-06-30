// FUNC_NAME: spinDelay
// Function at 0x004ad440: Busy-wait loop that decrements a counter from a structure field at offset +0x4.
void __fastcall spinDelay(void* thisPtr)
{
    int count = *(int*)((char*)thisPtr + 4); // offset +0x4: delay count
    for (; count != 0; count--) {
        // empty loop to waste cycles
    }
}