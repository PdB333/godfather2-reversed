// FUNC_NAME: BoneMatrixArray::BoneMatrixArray
// Function at 0x006f19f0: Constructor for BoneMatrixArray class.
// Initializes a fixed-size array of 8 matrices (4x4, stored as 8 groups of 4 uint32 each?)
// and several control members. The matrix data is filled with sentinel magic values:
//   0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911 repeating 8 times.
// These likely represent an initial state (e.g., identity or uninitialized).
// Inheritance: calls base class constructor FUN_0046c590 with param_2 (probably an allocator or parent pointer).

#include <cstdint>

class BoneMatrixArray
{
public:
    // Vtable pointer at +0x00
    void *vfptr;

    // Base class data? Offsets 0x04-0x0C? Not set here.

    // Interface pointers (possibly for multiple inheritance or COM)
    // +0x3C (offset 0x0F * 4 = 0x3C)
    void *pointer_0x3C;
    // +0x48 (offset 0x12 * 4 = 0x48)
    void *pointer_0x48;

    // +0x50: byte - set to 1. Possibly a flag (e.g., "isValid")
    uint8_t byte_0x50[1]; // actually a single byte, but alignment may cause padding

    // +0x54 (offset 0x15 * 4): int32 - initialized to 7
    int32_t field_0x54; // maybe "matrixCount" or "blendWeightCount"

    // Offsets between 0x58 and 0x68: not explicitly set, likely padding.

    // +0x68 (offset 0x1A * 4): int32 - initialized to 2
    int32_t field_0x68;
    // +0x6C (offset 0x1B * 4): int32 - initialized to 2
    int32_t field_0x6C;
    // +0x70 (offset 0x1C * 4): int32 - initialized to 3
    int32_t field_0x70;

    // +0x74 to +0xF0: matrix data (32 uint32 = 128 bytes)
    // Organized as 8 groups of 4 consecutive uint32:
    //   Group i: [bad, beef, eac1, 9110] at offsets 0x1D+i*4, 0x1E+i*4, 0x1F+i*4, 0x20+i*4 (i=0..7)
    uint32_t matrixData[8][4];

    // +0xF4 to +0x114: zeroed fields (9 uint32)
    uint32_t padding_0xF4[9]; // or other members

    // Constructor
    BoneMatrixArray(uint32_t param_2) // param_2 passed to base
    {
        // Call base class constructor
        FUN_0046c590(param_2);

        // Set vtable
        vfptr = &PTR_FUN_00d605b8; // vtable pointer at +0x00
        pointer_0x3C = &PTR_LAB_00d605a8;
        pointer_0x48 = &PTR_LAB_00d605a4;

        // Zero out fields at offsets 0x58,0x5C,0x60,0x64? Not set here, but may be zero by default.

        // Initialize control members
        byte_0x50[0] = 1; // set to 1
        field_0x54 = 7;
        field_0x68 = 2;
        field_0x6C = 2;
        field_0x70 = 3;

        // Initialize matrix data with sentinel patterns
        for (int32_t i = 0; i < 8; ++i)
        {
            uint32_t *row = &matrixData[i][0]; // each row is 4 uint32
            row[0] = 0xbadbadba; // bad
            row[1] = 0xbeefbeef; // beef
            row[2] = 0xeac15a55; // eac1
            row[3] = 0x91100911; // 9110
        }

        // Zero out the trailing fields
        for (int32_t j = 0; j < 9; ++j)
        {
            padding_0xF4[j] = 0;
        }
    }
};
```