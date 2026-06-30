// FUNC_NAME: calculatePackedArraySize
// Function at 0x0066b910: computes the number of bytes needed to store a packed array structure,
// where the first field is a count of elements, each element except the last uses 28 bits,
// and the last element's size in bits is determined by its value (highest set bit position).
// The structure layout at param_2:
//   +0x00: uint count (number of elements)
//   +0x0C: uint* pArray (pointer to array of uint elements)
// Returns: ceil(totalBits / 8)   (number of bytes to hold the packed array)

int __fastcall calculatePackedArraySize(int unused, uint* pStruct)
{
    uint count;
    uint totalBits;
    uint value;
    uint temp;

    count = *pStruct;
    totalBits = 0;
    if (count != 0) {
        // Base size: 28 bits per element except the last (so 28*(count-1) bits)
        totalBits = count * 0x1c - 0x1c; // 28 * (count - 1)
        // Access the last element of the array (index count-1)
        // pStruct[3] is the array pointer, subtract 4 to adjust for indexing from 1? Actually:
        // pStruct[3] - 4 + count*4 = pArray + (count-1)*4, pointing to last element
        value = *(uint*)((pStruct[3] - 4) + count * 4);
        // Count the number of bits needed to represent this value (bit length)
        while (value != 0) {
            totalBits++;
            value >>= 1;
        }
    }
    // Round totalBits up to the next byte (ceil(totalBits / 8))
    return ((int)(totalBits + ((int)totalBits >> 0x1f & 7)) >> 3) + (uint)((totalBits & 7) != 0);
}