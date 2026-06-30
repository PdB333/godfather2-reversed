// FUNC_NAME: StateManager::StateManager
// Address: 0x00455cf0 - Constructor for game state manager (EA EARS engine)
// Allocates arrays for state objects (0x24 bytes each) and pairs (8 bytes each)
// Registers a callback via global function table

class StateManager {
public:
    // Vtable and data members offsets:
    // +0x00: vtable pointer (set to &PTR_FUN_00e319f0)
    // +0x04: field_4 (int) - set to 1
    // +0x08: field_8 (int) - set to 0
    // +0x0C: field_C (void*) - initially &PTR_FUN_00e3522c, later &PTR_LAB_00e31a00
    // +0x10: field_10 (int) - set to 0
    // +0x14: field_14 (void*) - initially &PTR_LAB_00e31a10, later &PTR_LAB_00e31a0c
    // +0x18: field_18 (void*) - parent object (param_2)
    // +0x1C: field_1C (int) - subStateCount (param_4)
    // +0x20: field_20 (int) - stateCount (param_3)
    // +0x24: field_24 (void*) - allocated array for subStates (size = subStateCount * 0x24)
    // +0x28: field_28 (int) - subStateCount2 (probably unused)
    // +0x2C: field_2C (int) - stateCount (repeated)
    // +0x30: field_30 (void*) - allocated array for states (size = stateCount * 0x24)
    // +0x34: field_34 (int) - stateIndex (probably current state)
    // +0x38: field_38 (void*) - allocated array for pairs (size = pairCount * 8)
    // +0x3C: field_3C (int) - pairIndex
    // +0x40: field_40 (int) - pairCount
    // +0x44: byte flag (set to 0)

    void* vtable;                              // +0x00
    int field_4;                                // +0x04
    int field_8;                                // +0x08
    void* field_C;                              // +0x0C
    int field_10;                               // +0x10
    void* field_14;                             // +0x14
    void* parentObject;                         // +0x18
    int subStateCount;                          // +0x1C
    int stateCount;                             // +0x20
    void* subStateArray;                        // +0x24
    int subStateCount2;                         // +0x28
    int stateCount2;                            // +0x2C
    void* stateArray;                           // +0x30
    int stateIndex;                             // +0x34
    void* pairArray;                            // +0x38
    int pairIndex;                              // +0x3C
    int pairCount;                              // +0x40
    byte flag;                                  // +0x44

    // Custom allocation function (likely EAHeap or similar)
    void* __thiscall operator new(size_t size);  // assumed, not shown

    // Constructor
    __thiscall StateManager(void* parentObject, int stateCount, int subStateCount, int pairCount);
};

// External functions (Ghidra unresolved, likely from engine)
extern void* __cdecl FUN_009c8e80(int size);  // custom heap allocator
extern void __thiscall FUN_0049c6e0(void* sink, int flag); // event sink registration

// Global pointer set in constructor
StateManager* DAT_012233f8;

// External symbols (vtable/labels)
extern void* PTR_FUN_00e319f0;  // initial vtable
extern void* PTR_FUN_00e3522c;  // temporary field_C pointer
extern void* PTR_LAB_00e31a00;  // final field_C pointer
extern void* PTR_LAB_00e31a10;  // temporary field_14 pointer
extern void* PTR_LAB_00e31a0c;  // final field_14 pointer
extern void* DAT_01223510;      // global function table
extern void* LAB_00456180;      // callback address (probably a function)

// Global sinks
extern void DAT_00e319d0;
extern void DAT_00e319d4;
extern void DAT_00e319d8;
extern void PTR_DAT_00e319dc;
extern void DAT_00e319e0;
extern void DAT_00e319e4;
extern void PTR_LAB_00e319e8;
extern void DAT_00e319ec;

__thiscall StateManager::StateManager(void* parent, int stateCount, int subStateCount, int pairCount) {
    // Initialize fields
    this->field_4 = 1;
    this->field_8 = 0;
    this->field_C = &PTR_FUN_00e3522c;
    this->field_10 = 0;
    this->field_14 = &PTR_LAB_00e31a10;
    DAT_012233f8 = this;  // store singleton

    // Set vtable
    this->vtable = &PTR_FUN_00e319f0;

    // Update pointers to final values
    this->field_C = &PTR_LAB_00e31a00;
    this->field_14 = &PTR_LAB_00e31a0c;

    // Store parent and counters
    this->parentObject = parent;
    this->subStateCount = subStateCount;
    this->stateCount = stateCount;
    this->pairCount = pairCount;

    // Allocate arrays (size per element = 0x24 = 36 bytes)
    this->subStateArray = FUN_009c8e80(subStateCount * 0x24);
    this->subStateCount2 = subStateCount;  // duplicate count
    this->subStateCount = 0;               // reset index?

    this->stateArray = FUN_009c8e80(stateCount * 0x24);
    this->stateCount2 = stateCount;         // duplicate count
    this->stateIndex = 0;

    // Allocate pair array (size per pair = 8 bytes)
    this->pairArray = FUN_009c8e80(pairCount * 8);
    this->pairIndex = 0;
    this->pairCount = pairCount;

    this->flag = 0;

    // If parent exists, call its method at vtable+8 (likely a notification)
    if (this->parentObject != nullptr) {
        void** parentVtable = *(void***)this->parentObject;
        ((void (__thiscall*)(void*))parentVtable[2])(this->parentObject);  // vtable index 2 (offset 0x8)
    }

    // Register a callback with the global engine
    void* globalTable = *(void**)DAT_01223510;
    ((void (__thiscall*)(void*, void*))((void**)globalTable)[3])(&LAB_00456180);  // offset 0x18

    // Register various sinks (likely event handlers or resource managers)
    FUN_0049c6e0(&DAT_00e319d0, 1);
    FUN_0049c6e0(&DAT_00e319d4, 1);
    FUN_0049c6e0(&DAT_00e319d8, 1);
    FUN_0049c6e0(&PTR_DAT_00e319dc, 1);
    FUN_0049c6e0(&DAT_00e319e0, 1);
    FUN_0049c6e0(&DAT_00e319e4, 1);
    FUN_0049c6e0(&PTR_LAB_00e319e8, 1);
    FUN_0049c6e0(&DAT_00e319ec, 1);

    return this;
}