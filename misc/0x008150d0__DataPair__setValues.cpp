// FUNC_NAME: DataPair::setValues
// Function address: 0x008150d0
// Role: Sets two values (param_2, param_3) into the object, clears a field, and returns a stored previous value.
// If the low bit of the flags field (+0x10) is already set, calls a cleanup/reset function first.

class DataPair {
public:
    uint32_t flags;          // +0x10 (bit 0 indicates "initialized" state)
    uint32_t previousValue;  // +0x14 (returned after setting new values)
    uint32_t zeroField;      // +0x18 (cleared to 0)
    uint32_t value1;         // +0x1c (first new value)
    uint32_t value2;         // +0x20 (second new value)

    // Sets value1 and value2, marks as initialized, clears zeroField, returns previousValue.
    // If already initialized, calls resetPreviousValues() first.
    uint32_t setValues(uint32_t newVal1, uint32_t newVal2) {
        if (flags & 1) {
            resetPreviousValues(); // FUN_00814d90 – releases/cleans up old state
        }
        value1 = newVal1;
        value2 = newVal2;
        flags |= 1;               // mark as initialized
        zeroField = 0;
        return previousValue;     // return the old stored value
    }

private:
    void resetPreviousValues(); // defined elsewhere (0x00814d90)
};