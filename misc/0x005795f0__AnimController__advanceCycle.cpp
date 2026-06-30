// FUNC_NAME: AnimController::advanceCycle
// Function at 0x005795f0: Advances an animation or cyclic timer, updating index/modulus and returning a combined value.
// Offsets: +0x2e0 = some initial value (start?), +0x2e4 = modulus (limit), +0x2e8 = current index, +0x2c = active flag, +0x18 = current start value

int __thiscall AnimController::advanceCycle(void)
{
    int modulus;
    int newIndex;
    int quotient;
    
    // Validate state via base class check
    if (FUN_00579170() == 0) {
        return 0;
    }
    
    // Call secondary update function (likely tick or prepare)
    FUN_00582090();
    
    modulus = *(int *)(this + 0x2e4);
    newIndex = *(int *)(this + 0x2e8) - 1 + modulus; // cycle backwards: newIndex = current - 1 + modulus
    *(int *)(this + 0x2c) = 1;                        // mark as active
    *(int *)(this + 0x18) = *(int *)(this + 0x2e0);   // reset start value
    *(int *)(this + 0x2e8) = newIndex % modulus;      // wrap index modulo modulus
    
    quotient = newIndex / modulus;
    // Return a value with low byte = 1 (likely a flag) and upper 24 bits = quotient >> 8
    return ((quotient >> 8) << 8) | 1;
}