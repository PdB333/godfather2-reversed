// FUNC_NAME: EntryManager::findEntryById
// Function address: 0x00896a50
// Role: Looks up an entry by ID in a parallel array of IDs and entries.
// Returns pointer to entry if found and not expired (unless ignoreTimeout is true).
// Global g_currentTime is compared against entry's time stamp plus base offset.

struct Entry {
    char name[0x28]; // +0x00: first byte indicates validity (non-zero if active)
    int timeStamp;   // +0x28: expiration time stamp
};

class EntryManager {
public:
    int* m_idArray;      // +0x04
    Entry* m_entryArray; // +0x08
    int m_count;         // +0x0C
    int m_timeBase;      // +0x14: added to entry timeStamp for expiration check
};

extern int g_currentTime; // DAT_01205220

Entry* __thiscall EntryManager::findEntryById(EntryManager* this, int entryId, bool ignoreTimeout)
{
    Entry* result = nullptr;
    uint index = 0;

    if (this->m_count != 0) {
        int* idPtr = this->m_idArray;
        int offset = 0;

        while (true) {
            if (*idPtr != entryId ||
                (result = reinterpret_cast<Entry*>(reinterpret_cast<uintptr_t>(this->m_entryArray) + offset),
                 result->name[0] == '\0') ||
                (!ignoreTimeout &&
                 (static_cast<uint>(result->timeStamp + this->m_timeBase) < g_currentTime)))
            {
                index++;
                idPtr++;
                offset += 0x2c;
                if (this->m_count <= index) {
                    return nullptr;
                }
            } else {
                break;
            }
        }
    }
    return result;
}