// FUNC_NAME: StatModifierList::getTotalValueForItem
// Address: 0x004bb4e0
// Role: Sums up short values from a stat table for entries matching a given item ID,
//       using indices provided by the modifier list (this).
//       The stat table is accessed via the database object at offset 0x10 (pointer to array of 0x20-byte entries).
//       Index * 0x20 yields the entry offset.

// __fastcall: ecx = this (StatModifierList*), edx = db (StatDatabase*), stack = itemID
// Returns accumulated short value.

class StatDatabase; // forward declaration

struct StatEntry {
    /* +0x00 */ int field_0;
    /* +0x04 */ int field_4;
    /* +0x08 */ int itemID;
    /* +0x0C */ short value;
    /* +0x0E */ short padding; // likely part of alignment, size 0x20 total
};

class StatModifierList {
public:
    /* +0x00 */ int* indices;   // pointer to array of table indices
    /* +0x04 */ int count;      // number of indices

    // Returns total value for the given itemID from the stat table.
    short __fastcall getTotalValueForItem(StatDatabase* db, int itemID);
};

// Inline implementation for clarity
short __fastcall StatModifierList::getTotalValueForItem(StatDatabase* db, int itemID) {
    short total = 0;
    if (this->count != 0) {
        int* currentIndexPtr = this->indices;
        for (int i = 0; i < this->count; i++) {
            int index = *currentIndexPtr;
            // Table is at db + 0x10, each entry is 0x20 bytes
            StatEntry* entry = (StatEntry*)(*(int*)((char*)db + 0x10) + index * 0x20);
            if (itemID == entry->itemID) {
                total += entry->value;
            }
            currentIndexPtr++;
        }
        return total;
    }
    return 0;
}