// FUN_004c8f50: ConnectionMappingTable::addMapping
// This function adds a mapping entry (id, value) to a fixed-size table of 32 entries.
// Each entry is 20 bytes (5 ints). The table stores a combination of id and value as a key,
// with an additional timestamp from a global. Returns 1 on success, 0 if duplicate or table full.
// Table structure:
//   +0x00: count (int) - number of valid entries
//   +0x04: entry[0].id
//   +0x08: entry[0].value
//   +0x0C: entry[0].timestamp
//   +0x10: entry[0].unknown1
//   +0x14: entry[0].unknown2
//   Then entry[1] at +0x18, etc.

int __fastcall ConnectionMappingTable::addMapping(int id, int value)
{
    // Search for an existing entry with the same id and value
    for (int i = 0; i < 32; i++)
    {
        if (this->entries[i].id == id && this->entries[i].value == value)
        {
            // Duplicate key found – insertion fails
            return 0;
        }
    }

    // Find an empty slot (id == 0 marks empty)
    for (int i = 0; i < 32; i++)
    {
        if (this->entries[i].id == 0)
        {
            // Fill entry with provided id, value, and global timestamp
            this->count++;
            this->entries[i].id = id;
            this->entries[i].value = value;
            this->entries[i].timestamp = g_globalTimestamp; // DAT_01205224
            FUN_004c9040(this); // Update/notify after insertion
            return 1;
        }
    }

    // No empty slot available
    return 0;
}