// FUNC_NAME: computeRelativePositionFromIndex
typedef unsigned int uint;
typedef int undefined4;

// Global reference position (likely world origin or camera center)
extern float DAT_00e2b1a4;

// Error handler: likely assertion failure or debug break
void assertIndexValid(int *pParam); // Actually takes address of local variable, not clear

// Core function that performs the actual relative transform
undefined4 computeRelativeTransform(undefined4 param1, void *data, int *array, float dx, float dy, uint flags, undefined4 extra);

undefined4 FUN_0058bae0(undefined4 param1, void *data, int *array, float offsetX, float offsetY, uint flags, undefined4 extra)
{
    short index;    // from data+2
    uint uIndex;
    void *originalData = data; // preserve original data pointer
    float fx, fy;

    // Check if the data structure is active (byte at +1)
    if (*(char *)(data + 1) == '\0') {
        return 0;
    }

    // Read the index from offset +2
    index = *(short *)(data + 2);
    uIndex = (uint)index;

    // Bounds check: array[1] is the size/count of the float array
    if ((uint)array[1] <= uIndex) {
        int zero = 0;
        assertIndexValid(&zero); // fails assertion
    }

    // Compute X relative offset
    fx = (*(float *)(*array + index * 4) - DAT_00e2b1a4) - offsetX;

    // Re-read index (though unchanged) for second computation
    uIndex = (uint)*(short *)(originalData + 2);
    if ((uint)array[1] <= uIndex) {
        int zero = 0;
        assertIndexValid(&zero);
    }

    // Compute Y relative offset
    fy = (*(float *)(*array + uIndex * 4) - DAT_00e2b1a4) - offsetY;

    // Call the core function with adjusted flags (XOR with 2)
    return computeRelativeTransform(param1, originalData, array, fx, fy, flags ^ 2, extra);
}