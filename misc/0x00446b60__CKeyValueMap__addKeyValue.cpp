// FUNC_NAME: CKeyValueMap::addKeyValue
// Address: 0x00446b60
// Class: CKeyValueMap - a fixed-size associative array (64 entries) keyed by int32, storing int32 values
// Offsets: +0xd0: MapEntry entries[64] (each entry: int key, int value; 8 bytes each)
//          +0x2d0: int entryCount (number of entries stored)
// Note: The function appears to have a bug: if a matching key is found with value=0, it breaks early
// but still appends a new entry (duplicate key) rather than overwriting the existing zero-value slot.
// This matches the decompiled assembly exactly.

class CKeyValueMap {
public:
    static const int kMaxEntries = 64;

    struct MapEntry {
        int key;    // +0x00
        int value;  // +0x04
    };

    void addKeyValue(int key, int value) const {
        int count = *(int*)((char*)this + 0x2d0); // entryCount
        int i = 0;
        if (count > 0) {
            MapEntry* entries = (MapEntry*)((char*)this + 0xd0);
            do {
                if (entries[i].key == key) {
                    if (entries[i].value != 0) {
                        // Key already has non-zero value; ignore request
                        return;
                    }
                    // Key found with zero value; break out early but still append a new entry.
                    break;
                }
                i++;
            } while (i < count);
        }
        if (count < kMaxEntries) {
            MapEntry* entries = (MapEntry*)((char*)this + 0xd0);
            entries[count].key = key;
            entries[count].value = value;
            *(int*)((char*)this + 0x2d0) = count + 1;
        }
    }
};