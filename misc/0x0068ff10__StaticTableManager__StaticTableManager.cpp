// FUNC_NAME: StaticTableManager::StaticTableManager
// Address: 0x0068ff10
// Purpose: Singleton manager constructor that initializes a sorted table from a static array of 0x10-byte entries (range 0x00e50258-0x00e50608).
// Structure (offsets relative to this):
//   +0x00: vtable (PTR_FUN_00d5c908)
//   +0x04: entryArray (pointer to array of void* pointers to static entries)
//   +0x08: entryCount
//   +0x0C: entryCapacity
//   +0x10: secondaryArray (unused, remains null)
//   +0x14: secondaryCount (0)
//   +0x18: secondaryCapacity (0)

#include <cstdint>

// External functions (alloc, sort, etc.)
extern void* FUN_0068e500(int size);              // allocates (likely malloc)
extern void  FUN_0068eca0(void** arrayPtr);       // sorts or prepares the pointer array
extern void  FUN_0068fe00(void* base, void* end, int count, void* compare);

// Comparison functions (labels)
extern void LAB_0068e390(void);  // Primary sort comparator
extern void LAB_0068e370(void);  // Secondary sort comparator

// Global instance pointer
StaticTableManager* gTableManager = nullptr;

class StaticTableManager {
public:
    void* vtable;               // +0x00
    void** entryArray;          // +0x04
    int    entryCount;          // +0x08
    int    entryCapacity;       // +0x0C
    void** secondaryArray;      // +0x10
    int    secondaryCount;      // +0x14
    int    secondaryCapacity;   // +0x18

    // Constructor (__fastcall, this in ECX)
    StaticTableManager* StaticTableManager() {
        gTableManager = this;               // DAT_01129bb4 = this

        this->vtable = &PTR_FUN_00d5c908;  // set vtable
        this->entryArray = nullptr;        // param_1[1] = 0
        this->entryCount = 0;              // param_1[2] = 0
        this->entryCapacity = 0;           // param_1[3] = 0
        this->secondaryArray = nullptr;    // param_1[4] = 0
        this->secondaryCount = 0;          // param_1[5] = 0
        this->secondaryCapacity = 0;       // param_1[6] = 0

        // Allocate initial array for pointers to static entries (0x3b = 59 slots)
        this->entryArray = (void**)FUN_0068e500(0x3b);
        this->entryCapacity = 0x3b;

        // Iterate over static table (0x10-byte entries from DAT_00e50258 to 0xe50608)
        uint8_t* current = (uint8_t*)&DAT_00e50258;
        uint8_t* end     = (uint8_t*)0x00e50608;
        while (current < end) {
            // Grow array if needed (exponential)
            if (this->entryCount >= this->entryCapacity) {
                int newCap = (this->entryCapacity == 0) ? 1 : this->entryCapacity * 2;
                this->entryArray = (void**)FUN_0068e500(newCap);
                this->entryCapacity = newCap;
            }
            this->entryArray[this->entryCount] = (void*)current;
            this->entryCount++;
            current += 0x10;  // step by 16 bytes per static entry
        }

        // Post-process the pointer list (likely sort or finalize)
        FUN_0068eca0(&this->entryArray);   // piVar1 = &entryArray

        // Sort the entry array using primary comparator
        int* base = (int*)this->entryArray;
        int* endPtr = base + this->entryCount;
        int elemCount = (endPtr - base); // = entryCount
        FUN_0068fe00(base, endPtr, elemCount, &LAB_0068e390);

        // Sort the (empty) secondary array using secondary comparator
        FUN_0068fe00(this->secondaryArray, this->secondaryArray, 0, &LAB_0068e370);

        return this;
    }
};