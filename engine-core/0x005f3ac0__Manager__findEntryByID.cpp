// FUNC_NAME: Manager::findEntryByID
int __fastcall Manager::findEntryByID(int this, int key)
{
    // Array of 10 entries at offset +0x82ac, each 0x5c bytes
    // Entry structure: +0x00 = key (int), +0x04 = active flag (>=0 means valid)
    struct Entry {
        int key;   // +0x00
        int active;// +0x04
    };

    Entry* entry = reinterpret_cast<Entry*>(this + 0x82ac);

    for (int i = 0; i < 10; ++i)
    {
        if (entry->active >= 0 && entry->key == key)
        {
            return i;
        }
        entry = reinterpret_cast<Entry*>(reinterpret_cast<uint8_t*>(entry) + 0x5c);
    }

    return -1; // not found
}