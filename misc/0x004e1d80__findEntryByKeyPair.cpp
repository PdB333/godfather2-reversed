// FUNC_NAME: findEntryByKeyPair
// Function searches an array of entries (each 0x56 bytes) with two short keys.
// Returns 1 and sets *outIndex on match, else 0.
// Global data:
//   sEntryCount at 0x012054d8
//   sEntryArrayBase (key2 of first entry) at 0x0119455a

int findEntryByKeyPair(uint *outIndex, short key1, short key2)
{
    uint count;
    short *psEntry; // points to key2 of current entry

    count = *(uint *)0x012054d8; // sEntryCount
    if (count == 0) {
        return 0;
    }
    psEntry = (short *)0x0119455a; // points to key2 of first entry
    for (uint i = 0; i < count; i++) {
        // entry layout: [key1 (short), key2 (short), ... , padding up to 0x56 bytes]
        // key1 is at offset -2 from psEntry, key2 at offset 0
        if (*(psEntry - 1) == key1 && *psEntry == key2) {
            *outIndex = i;
            return 1;
        }
        // move to next entry (0x56 bytes forward)
        psEntry = (short *)((char *)psEntry + 0x56);
    }
    return 0;
}