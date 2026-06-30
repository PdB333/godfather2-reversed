// FUNC_NAME: SortedArrayMap::findOrAddKey

#include <cstdint>

// Represents a sorted array-based map of uint32 key-value pairs.
// Structure offsets:
//   +0x00: uint32* entries (array of {key, value} pairs, each 8 bytes)
//   +0x04: int32 count (number of entries currently stored)
// Entries are maintained in ascending order by key.

uint32_t* SortedArrayMap::findOrAddKey(const uint32_t* keyPtr)
{
    // Dereference the input pointer to get the key we are looking for
    uint32_t key = *keyPtr;

    // Get the internal array pointer and element count from 'this'
    uint32_t* entries = reinterpret_cast<uint32_t*>(this);           // +0x00
    int32_t count = *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 4); // +0x04

    int32_t index = 0;
    if (count > 0)
    {
        uint32_t* currentEntry = entries;
        do
        {
            if (key == *currentEntry)
            {
                // Key already exists; return null to indicate no new slot
                return nullptr;
            }
            if (key < *currentEntry)
            {
                // Found insertion point (key should go before this entry)
                break;
            }
            index++;
            currentEntry += 2; // move to next entry (each entry is two uint32s)
        } while (index < count);
    }

    // Key not present – allocate a new map entry slot
    uint32_t* newEntry = reinterpret_cast<uint32_t*>(allocateMapEntry()); // calls FUN_004437a0
    *newEntry = key;                    // store the key in the first half
    return newEntry + 1;                // return pointer to the value half (caller will fill it)
}