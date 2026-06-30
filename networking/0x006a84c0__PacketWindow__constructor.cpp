// FUNC_NAME: PacketWindow::constructor
// Address: 0x006a84c0
// Reconstructed C++ for constructor of PacketWindow class (32-slot packet history buffer)

// Structure fields (offsets from this):
// +0x00: vtable pointer
// +0x04: unknown int (param2) - possibly network sequence or size
// +0x08: unknown int (param3) - possibly another ID or flags
// +0x0C: PacketEntry array[32] (each entry is 12 bytes: pointer, int, int)
//   - Entry[0].ptr   at +0x0C
//   - Entry[0].field1 at +0x10
//   - Entry[0].field2 at +0x14
//   - ...
//   - Entry[31] ends at +0x18C (0x0C + 32*12 = 0x18C)
// +0x190: sentinel int (set to 0)

// Each PacketEntry: struct { void* dataPointer; int field1; int field2; }

// External free function used to deallocate an entry's data pointer
extern void freePacket(void* ptr);  // FUN_004daf90

class PacketWindow {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Unknown fields at +0x04 and +0x08
    int param2;
    int param3;

    // Array of 32 entries, each 12 bytes
    struct PacketEntry {
        void* dataPtr;   // +0x0C, +0x18, ...
        int field1;      // +0x10, +0x1C, ...
        int field2;      // +0x14, +0x20, ...
    } entries[32];       // +0x0C

    int sentinel;        // +0x190 (33rd entry? Actually it's after the 32 entries)

    // Constructor
    PacketWindow(int param2_val, int param3_val) {
        // Set vtable
        vtable = &PTR_FUN_00d5d8c8;  // external symbol

        // Store parameters
        param2 = param2_val;
        param3 = param3_val;

        // Initialize all entries to zero (first loop)
        PacketEntry* entry = entries;
        for (int i = 0; i < 32; i++) {
            entry->dataPtr = nullptr;
            entry->field1 = 0;
            entry->field2 = 0;
            entry++;
        }

        // Clear any existing data in entries (second loop)
        // This loop is redundant for a fresh constructor, but handles re-initialization
        // It frees any non-null data pointers and zeros field2
        entry = entries;
        for (int i = 0; i < 32; i++) {
            if (entry->dataPtr != nullptr) {
                freePacket(entry->dataPtr);
                entry->dataPtr = nullptr;
            }
            entry->field2 = 0;
            entry++;
        }

        // Set sentinel field
        sentinel = 0;
    }
};