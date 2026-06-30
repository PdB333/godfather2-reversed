// FUNC_NAME: checkAnyInChunk
// Function at 0x006d12b0: Iterates over an array of 16-byte elements, calling a predicate on each.
// If any element matches (returns non-zero), returns 1; otherwise returns 0.

extern char checkElementCondition(int element, int value, int param); // from FUN_006d0ee0

char checkAnyInChunk(int array, int count, int value)
{
    int i = 0;
    for (; count != 0; count--) {
        i = array;
        if (checkElementCondition(i, value, 0) != '\0') {
            return 1;
        }
        array += 0x10; // each element is 16 bytes
    }
    return 0;
}