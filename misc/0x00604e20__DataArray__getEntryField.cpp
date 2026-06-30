// FUNC_NAME: DataArray::getEntryField
// Address: 0x00604e20
// Role: Accessor function that returns a 4-byte field from an array of 12-byte entries.
// The 'this' pointer points to a structure containing a pointer to the array at offset +0x8.
// Each element in the array is 0xC bytes; the returned field is at offset +0x4 within the element (i.e., skipping the first 4 bytes).
// param_2 is the index into the array.

class DataArray {
public:
    // +0x8: pointer to the start of the element array (each element 12 bytes)
    int* m_pElementArray; // offset 0x8

    // Returns the 4-byte value at offset 0x4 within the element at the given index.
    // Index is zero-based.
    int getEntryField(int index) {
        // Dereference the pointer at this+0x8 to get the array base
        int* arrayBase = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x8);
        // Each element is 12 bytes, the field we want is at offset 4 within the element.
        return *reinterpret_cast<int*>(
            reinterpret_cast<char*>(arrayBase) + 4 + index * 0xC
        );
    }
};
// Note: The array layout per element (12 bytes):
// +0x0: unknown (4 bytes, possibly another field or padding)
// +0x4: the returned 4-byte value (int or pointer)
// +0x8: unknown (4 bytes)