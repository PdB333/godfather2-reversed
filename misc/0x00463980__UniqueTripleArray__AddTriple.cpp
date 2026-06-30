// FUNC_NAME: UniqueTripleArray::AddTriple
// Function address: 0x00463980
// Adds a triple (a, b, c) to the container if not already present based on key 'a'.
// The container stores 12-byte entries: [key, value1, value2] (three uint32).
// Uses a dynamic resizing strategy: doubles capacity when full.

// Class layout (offsets from this):
// +0x0c: uint32* m_data         // pointer to array of entries
// +0x10: int32  m_count         // current number of entries
// +0x14: int32  m_capacity      // allocated capacity (in entries)

void UniqueTripleArray::AddTriple(uint32 a, uint32 b, uint32 c)
{
    // Check if an entry with key 'a' already exists.
    // FUN_00463a80 returns 0 if not found, non-zero if found.
    if (FUN_00463a80(a, &a) != 0)
    {
        return; // already present, do nothing
    }

    // If the array is full (count == capacity), resize.
    if (this->m_count == this->m_capacity)
    {
        int32 newCapacity;
        if (this->m_capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = this->m_capacity * 2;
        }
        // FUN_00463b90 reallocates the data array to hold newCapacity entries.
        // Each entry is 12 bytes (3 * uint32).
        FUN_00463b90(newCapacity);
    }

    // Insert the new entry at the end of the array.
    uint32* entry = this->m_data + (this->m_count * 3); // each entry is 3 uint32s
    this->m_count++;
    entry[0] = a;
    entry[1] = b;
    entry[2] = c;
}