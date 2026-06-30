// FUNC_NAME: FixedArray32::removeAtIndex
struct FixedArray32 {
    /* 0x00 */ int items[32];     // array of 32 elements
    /* 0x80 */ int count;         // number of valid elements
};

void __thiscall FixedArray32::removeAtIndex(int index) {
    // Validate index against current count
    if ((unsigned int)index >= (unsigned int)count)
        return;

    // Shift elements left to fill the gap, if not removing the last element
    if ((unsigned int)index < (unsigned int)(count - 1)) {
        do {
            items[index] = items[index + 1];
            ++index;
        } while (index < count - 1);
    }

    // Decrease element count
    --count;
}