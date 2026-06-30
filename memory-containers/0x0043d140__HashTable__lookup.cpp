// FUNC_NAME: HashTable::lookup
// Address: 0x0043d140
// This function performs a hash table lookup for a 16-byte key.
// The key is expected to be passed in the EAX register (pointer to 4 uint32_ts).
// The this pointer (hash table object) is passed via the stack (param_1 in Ghidra).
// Returns the first uint32_t of the found entry, or 0 if not found.

#include <cstdint>

int __fastcall HashTable::lookup(const uint32_t* key, HashTable* this_)   // key in EAX; this_ on stack
{
    // Local buffer: copy key + two hash constants (0x137726B7 and 0xFFFFFFFF)
    struct HashInput {
        uint32_t keyWords[4];   // +0x00 (16 bytes)
        uint32_t magic1;        // +0x10 = 0x137726B7
        uint32_t magic2;        // +0x14 = 0xFFFFFFFF
    } localHashInput;

    localHashInput.keyWords[0] = key[0];
    localHashInput.keyWords[1] = key[1];
    localHashInput.keyWords[2] = key[2];
    localHashInput.keyWords[3] = key[3];
    localHashInput.magic1 = 0x137726B7;
    localHashInput.magic2 = 0xFFFFFFFF;

    int index = hashFunction(&localHashInput);   // FUN_0043DB90 – returns an index or -1
    if (index >= 0)
    {
        // this_+0x10 points to the start of a hash table structure.
        // Inside that structure, at offset +0x18, there is an array of entries.
        // Each entry is 0x1C (28) bytes wide.
        uint32_t* entry = reinterpret_cast<uint32_t*>(
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this_) + 0x10)    // base pointer
            + 0x18 + index * 0x1C);                                                   // offset to entry
        if (entry != nullptr)
            return *entry;   // return first dword of the entry
    }
    return 0;
}