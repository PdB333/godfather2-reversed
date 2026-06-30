// FUNC_NAME: FixedArray32::removeElement
// Address: 0x00451de0
// Description: Removes the first occurrence of a value from a fixed-size array (max 32 elements).
// Expects: ECX = this pointer to structure (elements[0], count at +0x80), EDI = value to remove, EAX = flags (low byte cleared on failure, low byte set to 1 on success).
// Returns: Modified flags with low byte indicating success (1) or failure (0), and high 24 bits set to the index of the last shifted element (old count - 1).

struct FixedArray32 {
    uint32 elements[32]; // +0x00: array of 32 uint32 elements
    uint32 count;        // +0x80: number of valid elements (0..32)
};

uint32 __fastcall FixedArray32::removeElement(uint32 this_ptr, uint32 value, uint32 flags) {
    // Note: this_ptr in ECX, value in EDI, flags in EAX
    uint32 result = flags & 0xFFFFFF00;  // preserve high 24 bits from flags
    uint32 count = *(uint32*)(this_ptr + 0x80);
    uint32 index = 0;

    if (count != 0) {
        // Search for the element matching 'value'
        while (*(uint32*)(this_ptr + index * 4) != value) {
            index++;
            if (index >= count) {
                // Not found, return flags with low byte cleared
                return result;
            }
        }
        // Found at index
        if (index < count - 1) {
            // Shift remaining elements left to fill the gap
            do {
                *(uint32*)(this_ptr + index * 4) = *(uint32*)(this_ptr + (index + 1) * 4);
                index++;
            } while (index < count - 1);
        }
        // Decrease count
        (*(uint32*)(this_ptr + 0x80))--;
        // Set result high bytes to the index after shifting (old count - 1)
        result = index;  // index now equals count - 1 after loop
    }
    // Set low byte to 1 to indicate success
    result = (result & 0xFFFFFF00) | 0x01;
    return result;
}