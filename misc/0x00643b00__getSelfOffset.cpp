// FUNC_NAME: getSelfOffset
int getSelfOffset(void)
{
    // Function at 0x00643b00: Computes (int)self - *self, where self is in EAX.
    // This adjusts a pointer by subtracting the value stored at its start,
    // often used for offset calculations in multiple inheritance or vtable access.
    int *selfPtr; // this pointer (passed in register EAX)
    return (int)selfPtr - *selfPtr;
}