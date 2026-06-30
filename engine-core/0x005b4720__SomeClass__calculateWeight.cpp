// FUNC_NAME: SomeClass::calculateWeight
// Function address: 0x005b4720
// Role: Computes a weighted sum based on input range and object fields at offsets 1, 5, 7.
// Uses global byte table DAT_00e2bb88 for lookup.

extern unsigned char DAT_00e2bb88[256]; // Global lookup table

int SomeClass::calculateWeight(int input)
{
    // Switch on input to determine which fields contribute to the sum.
    switch (input)
    {
        default:
            // Add value from table indexed by byte at this+0x07
            input += DAT_00e2bb88[*(unsigned char*)((char*)this + 7)];
            // Fall through to case 6/7
        case 6:
        case 7:
            // Add value from table indexed by byte at this+0x05
            input += DAT_00e2bb88[*(unsigned char*)((char*)this + 5)];
            // Fall through to case 2-5
        case 2:
        case 3:
        case 4:
        case 5:
            // Return final sum including value from table indexed by byte at this+0x01
            return DAT_00e2bb88[*(unsigned char*)((char*)this + 1)] + input;
    }
}