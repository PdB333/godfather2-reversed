// FUNC_NAME: StreamManager::StreamManager
// Constructor for StreamManager class - manages up to 8 stream slots
// Address: 0x006aa870
// EARS engine stream management

#include <cstdint>

// Forward declarations
struct StreamSlotInit;
void StreamManager_initSlots(StreamManager* self, int count);
void StreamSlotInit_construct(StreamSlotInit* init, int param);
void StreamSlotInit_destruct(StreamSlotInit* init);

// Known base class constructor
void Object_constructor(void* obj, int param);

// Known vtable symbols
extern void* g_vtable_StreamManager;   // PTR_FUN_00d5d9dc
extern void* g_vtable_StreamManagerSub1; // PTR_LAB_00d5d9cc
extern void* g_vtable_StreamManagerSub2; // PTR_LAB_00d5d9c8
extern void* g_vtable_StreamSlotInit;   // PTR_FUN_00d5d9b0

struct StreamManager {
    // +0x00 vtable pointer (set to g_vtable_StreamManager)
    void* vtable;
    
    // +0x3C (offset 0x0F in uint32 units) sub-object vtable1
    void* subVtable1;
    
    // +0x48 (offset 0x12 in uint32 units) sub-object vtable2
    void* subVtable2;
    
    // +0x50 (offset 0x14) unknown fields
    int field_0x50;
    int field_0x54;
    uint16_t field_0x58;   // +0x58
    // padding?
    uint16_t field_0x5A;   // +0x5A
    int field_0x5C;        // +0x5C
    uint16_t field_0x60;   // +0x60
    // padding?
    uint16_t field_0x62;   // +0x62
    
    // +0x64+ presumably more fields
    
    // +0xF1 (offset 0x3C4) slot counter (max 8)
    uint32_t slotCount;
    
    // +0xF2 (byte) flag
    uint8_t someFlag;
    
    // ... rest of class (array of 8 slots)
};

// Temporary struct for passing slot initialization data
struct StreamSlotInit {
    // +0x00 vtable
    void* vtable;
    
    // Group 0: offset +0x04
    int int_0x04;
    uint32_t uint_0x08;
    uint32_t uint_0x0C;
    void (*callback_0x10)(void*);
    
    // Group 1: offset +0x14
    int int_0x14;
    uint32_t uint_0x18;
    uint32_t uint_0x1C;
    void (*callback_0x20)(void*);
    
    // Group 2: offset +0x24
    int int_0x24;
    uint32_t uint_0x28;
    uint32_t uint_0x2C;
    void (*callback_0x30)(void*);
    
    // Group 3: offset +0x34
    int int_0x34;
    uint32_t uint_0x38;
    uint32_t uint_0x3C;
    void (*callback_0x40)(void*);
    
    // Additional fields (used for data)
    uint32_t dataField1;    // +0x44
    uint16_t shortField1;   // +0x48
    uint16_t shortField2;   // +0x4A
    uint32_t dataField2;    // +0x4C
    uint16_t shortField3;   // +0x50
    uint16_t shortField4;   // +0x52
    uint32_t dataField3;    // +0x54
    uint16_t shortField5;   // +0x58
    uint16_t shortField6;   // +0x5A
    uint32_t dataField4;    // +0x5C
    uint16_t shortField7;   // +0x60
    uint16_t shortField8;   // +0x62
    uint32_t priority;      // +0x64 (initialized to 100)
    uint8_t flag;           // +0x68 (initialized to 0)
};

StreamManager* __thiscall StreamManager::StreamManager(StreamManager* this, int someParam) {
    // Call base class constructor
    Object_constructor(this, someParam);
    
    // Set vtable pointers
    this->vtable = &g_vtable_StreamManager;
    this->subVtable1 = &g_vtable_StreamManagerSub1;
    this->subVtable2 = &g_vtable_StreamManagerSub2;
    
    // Initialize fields to zero
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    *(uint16_t*)((char*)this + 0x58) = 0;
    *(uint16_t*)((char*)this + 0x5A) = 0;
    this->field_0x5C = 0;
    *(uint16_t*)((char*)this + 0x60) = 0;
    *(uint16_t*)((char*)this + 0x62) = 0;
    
    // Sub-initialization (likely sets up timer or callback structure)
    StreamManager_initSlots(this, 0);
    
    // Clear flag
    this->someFlag = 0;
    
    // Initialize 8 stream slots
    int loopCount = 8;
    do {
        // Create temporary structure on stack
        StreamSlotInit init;
        init.vtable = &g_vtable_StreamSlotInit;
        init.int_0x04 = 0;
        init.uint_0x08 = 0;
        init.uint_0x0C = 0;
        init.callback_0x10 = nullptr;
        init.int_0x14 = 0;
        init.uint_0x18 = 0;
        init.uint_0x1C = 0;
        init.callback_0x20 = nullptr;
        init.int_0x24 = 0;
        init.uint_0x28 = 0;
        init.uint_0x2C = 0;
        init.callback_0x30 = nullptr;
        init.int_0x34 = 0;
        init.uint_0x38 = 0;
        init.uint_0x3C = 0;
        init.callback_0x40 = nullptr;
        init.dataField1 = 0;
        init.shortField1 = 0;
        init.shortField2 = 0;
        init.dataField2 = 0;
        init.shortField3 = 0;
        init.shortField4 = 0;
        init.dataField3 = 0;
        init.shortField5 = 0;
        init.shortField6 = 0;
        init.dataField4 = 0;
        init.shortField7 = 0;
        init.shortField8 = 0;
        init.priority = 100;
        init.flag = 0;
        
        // If slot count < 8, add this slot
        if (this->slotCount < 8) {
            this->slotCount++;
            StreamSlotInit_construct(&init, this->slotCount);
        }
        
        // Clean up the temporary structure
        // Check each group's 'int' field and call the corresponding callback if non-zero
        if (init.int_0x34 != 0) {
            init.callback_0x40((void*)init.int_0x34);
        }
        if (init.int_0x24 != 0) {
            init.callback_0x30((void*)init.int_0x24);
        }
        if (init.int_0x14 != 0) {
            init.callback_0x20((void*)init.int_0x14);
        }
        if (init.int_0x04 != 0) {
            init.callback_0x10((void*)init.int_0x04);
        }
        
        loopCount--;
    } while (loopCount != 0);
    
    return this;
}