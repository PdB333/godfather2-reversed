// FUNC_NAME: FixedSizeArray32::pushBack
// Address: 0x00411f00
// Role: Adds a 4-byte element to a fixed-size array (max 32 elements). Returns 1 on success, 0 if full.
// Class layout (offsets relative to this):
//   +0x00: uint32 elements[32] (total 128 bytes)
//   +0x80: uint32 count (number of elements stored)

int __thiscall FixedSizeArray32::pushBack(uint32 *valuePtr) {
    // Read current element count from offset +0x80
    uint32 count = *(uint32 *)((uint8 *)this + 0x80);
    
    // Check if array is not full (max 32 elements)
    if (count < 32) {
        // Write the value pointed to by valuePtr into the array at index count
        // Array starts at offset 0x00, each element is 4 bytes
        *(uint32 *)((uint8 *)this + count * 4) = *valuePtr;
        
        // Increment count
        (*(uint32 *)((uint8 *)this + 0x80))++;
        
        return 1; // Success
    }
    
    return 0; // Array full
}