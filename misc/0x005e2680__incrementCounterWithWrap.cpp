// FUNC_NAME: incrementCounterWithWrap
// Address: 0x005e2680
// Role: Increments a counter at offset 0x1748 within the structure pointed to by param_2.
// If the result equals -1 (overflow safeguard), the counter is reset to 0.
// param_1 is unused; param_2 is a pointer to a large structure (likely a game object or manager).

void __fastcall incrementCounterWithWrap(undefined4 param_1, int param_2)
{
    int& counter = *(int*)(param_2 + 0x1748); // counter field at +0x1748
    int newVal = counter + 1;
    counter = newVal;
    if (newVal == -1) {
        counter = 0;
    }
}