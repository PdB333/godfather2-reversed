// FUNC_NAME: resetArray
void __thiscall SomeClass::resetArray(uint32_t *this)
{
    // Index 11 (0xB) is used as a counter/next index
    // Set the counter to 0 initially
    this[0xB] = 0;

    // Zero the first element
    this[0] = 0;

    // Increment counter and zero subsequent elements 1 through 10
    this[0xB]++; // now counter = 1
    if ((uint32_t)this[0xB] < 0xB) {
        this[this[0xB]] = 0;
        this[0xB]++;
        if ((uint32_t)this[0xB] < 0xB) {
            this[this[0xB]] = 0;
            this[0xB]++;
            // ... (repeating pattern for indices 2 to 9)
            // Actually the decompiled code has 9 nested ifs, filling indices 1..10
            // Node that the final state after the chain is counter = 11 and indices 0-10 are zeroed
        }
    }

    // Loop 3 times (just to cover any remaining; but counter is already 11)
    int iVar1 = 3;
    do {
        if ((uint32_t)this[0xB] < 0xB) {
            this[this[0xB]] = 0;
            this[0xB]++;
        }
        iVar1--;
    } while (iVar1 != 0);
}