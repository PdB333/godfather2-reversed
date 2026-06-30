// FUNC_NAME: EntryTable::allocateEntry
// Reconstructed from Ghidra at 0x00671870
// Manages a fixed-size table of entries (128 slots, each 0x3c bytes).
// Each entry contains a key, a slot index (used as marker), and 16 bytes of data.
// Returns slot index (0-127) on success, 0xffff on failure.
// Sets *outError to status code.

class EntryTable {
public:
    // Offsets (from this):
    // +0x10: maxKey (ushort) - maximum allowed key value
    // +0x18: nextSlot (ushort) - circular counter for slot search
    // +0x1a: count (ushort) - current number of occupied slots
    // +0x1e: entries[] - array of Entry of size 0x3c * 128

    struct Entry {
        // Offset from entry base:
        // +0x00: ..? (unknown, part of 0x1c bytes before visible fields)
        // +0x1c: key (ushort) - the key value stored
        // +0x1e: slotIndex (short) - the slot index; -1 means free
        // +0x20: data0 (uint64) - user data part 1
        // +0x28: data1 (uint64) - user data part 2
        // +0x30: field30 (undefined4) - cleared to 0
        // +0x34: field34 (undefined4) - cleared to 0
        // Total size 0x3c (60 bytes)
        char _pad[0x1c];
        ushort key;
        short slotIndex;
        uint64 data0;
        uint64 data1;
        uint32 field30;
        uint32 field34;
    };

    // Status codes (passed back via outError)
    enum Error {
        ERR_NONE = 0,
        ERR_MAX_COUNT_EXCEEDED = 0x4e22,     // count > 127
        ERR_KEY_OUT_OF_RANGE = 20000         // key >= maxKey
    };
};

uint __thiscall EntryTable::allocateEntry(ushort key, uint *outError) {
    ushort currentCount = this->count;  // +0x1a

    // If count already exceeds 127, cannot allocate
    if (currentCount > 0x7f) {
        *outError = ERR_MAX_COUNT_EXCEEDED;
        return 0xffff;
    }

    ushort maxKey = this->maxKey;  // +0x10
    if (key < maxKey) {
        // Search for a free slot using circular counter
        ushort slotCandidate;
        do {
            slotCandidate = this->nextSlot;  // +0x18
            this->nextSlot = slotCandidate + 1;

            // Handle wrap-around (0xffff -> 1, with flag *in_EAX? unclear)
            if (slotCandidate == 0xffff) {
                // *in_EAX = 1;  // Global flag? Not relevant to structure.
                slotCandidate = 0;
                this->nextSlot = 1;
            }
        } while (this->entries[slotCandidate & 0x7f].slotIndex != -1);

        uint slotIndex = slotCandidate & 0x7f;  // Wrap to 0-127

        Entry &entry = this->entries[slotIndex];

        // Store key and data passed via unaff_EDI (assumed to be two uint64 values)
        entry.key = key;                          // +0x1c
        entry.slotIndex = (short)slotCandidate;   // +0x1e (actually short, but stores the raw slotCandidate)
        entry.data0 = *reinterpret_cast<uint64*>(unaff_EDI[0]);  // +0x20
        entry.data1 = *reinterpret_cast<uint64*>(unaff_EDI[1]);  // +0x28
        entry.field30 = 0;                        // +0x30
        entry.field34 = 0;                        // +0x34

        // Increment occupied count
        this->count = this->count + 1;

        *outError = ERR_NONE;
        return slotIndex;
    }

    *outError = ERR_KEY_OUT_OF_RANGE;
    return 0xffff;
}