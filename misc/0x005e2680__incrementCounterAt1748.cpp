// FUNC_NAME: incrementCounterAt1748
void __fastcall incrementCounterAt1748(void* unusedParam, int* objWithCounter) {
    // Increments an integer counter at offset 0x1748 from the object pointer.
    // If the incremented value equals -1 (0xFFFFFFFF), it wraps to 0.
    // This is likely a sequence number or reference counter with a sentinel skip.
    int* counter = (int*)((char*)objWithCounter + 0x1748); // +0x1748: counter field
    int newValue = *counter + 1;
    *counter = newValue;
    if (newValue == -1) {
        *counter = 0;
    }
}