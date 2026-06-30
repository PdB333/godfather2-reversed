// FUNC_NAME: EventTypeTable::getHashForEventType
// Address: 0x0054c080
// Searches the event type table (array at +0x74, count at +0x78) for a given event type ID.
// If found, converts the ID to a hash via FUN_004af8c0 and writes it to outHash.
// If not found, writes the sentinel value 0xfe16702f.
// Returns outHash.

#define EVENT_HASH_NOT_FOUND 0xfe16702f

// Helper function that converts an event type integer to a 4-byte hash.
// Defined at 0x004af8c0.
extern int* convertEventTypeToHash(int* outHash, int eventType);

int* EventTypeTable::getHashForEventType(int* outHash, int eventType) {
    int count = *(int*)(this + 0x78);
    *outHash = EVENT_HASH_NOT_FOUND;
    if (count > 0) {
        int* typeArray = *(int**)(this + 0x74);
        for (int i = 0; i < count; i++) {
            if (typeArray[i] == eventType) {
                convertEventTypeToHash(outHash, eventType); // overwrite outHash with real hash
                break;
            }
        }
    }
    return outHash;
}