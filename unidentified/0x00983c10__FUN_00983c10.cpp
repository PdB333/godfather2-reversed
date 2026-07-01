// FUNC_NAME: SomeManager::setFlagForId

struct SomeManagerEntry {
    char unknown_0x00[0x20]; // +0x00
    char flag;               // +0x20
    int id;                  // +0x24
};

class SomeManager {
public:
    SomeManagerEntry* entries;   // +0xB8
    int entryCount;              // +0xBC

    // Sets the flag byte at +0x20 to newFlag for all entries whose id matches *idPtr,
    // but only if the current flag is different from newFlag.
    void setFlagForId(int* idPtr, char newFlag) {
        if (entryCount == 0) return;

        for (int i = 0; i < entryCount; i++) {
            SomeManagerEntry* entry = &entries[i];
            if (entry->id == *idPtr && entry->flag != newFlag) {
                entry->flag = newFlag;
            }
        }
    }
};