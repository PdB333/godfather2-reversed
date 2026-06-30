// FUNC_NAME: initializeEngineSingleton

#include <cstdint>

// Binary constants (pointed to by data references)
extern uint32_t DAT_00e2b118;
extern uint32_t DAT_00e2b1a4;
extern uint32_t DAT_00e446c4;

// Global structures at fixed addresses
// Static data block at 0x01197d70 (9 ints)
struct StaticData {
    uint32_t field0;  // +0x00
    uint32_t field1;  // +0x04
    uint32_t field2;  // +0x08
    uint32_t field3;  // +0x0C
    uint32_t field4;  // +0x10
    uint32_t field5;  // +0x14
    uint32_t field6;  // +0x18
    uint32_t field7;  // +0x1C
    uint32_t field8;  // +0x20
};

// Engine singleton managed by a linked list
struct EngineSingleton { // at 0x01125aa0
    void** vtable;       // +0x00 (PTR_PTR_01125aa0)
    EngineSingleton* next; // +0x04
    uint32_t someResult;   // +0x08
    uint32_t id;           // +0x0C
};

// Linked list head and counter
extern EngineSingleton* g_singletonHead; // DAT_012058ec
extern uint32_t g_singletonCounter;      // DAT_012058f8

// Helper function (FUN_0060d740)
extern uint32_t transformValue(uint32_t input);

// The global engine singleton instance at 0x01125aa0
extern EngineSingleton g_engineSingleton;

// External function (FUN_0053bed0, FUN_0053bf60) – not directly used here

void initializeEngineSingleton(void) {
    // Initialize static data block
    StaticData* dataBlock = reinterpret_cast<StaticData*>(0x01197d70);
    dataBlock->field0 = 0;
    dataBlock->field1 = 0;
    dataBlock->field2 = 0;
    dataBlock->field3 = 0;
    dataBlock->field4 = DAT_00e2b118;
    dataBlock->field5 = DAT_00e2b1a4;
    dataBlock->field6 = DAT_00e446c4;
    dataBlock->field7 = DAT_00e2b1a4;
    dataBlock->field8 = 0;

    // Call virtual function at vtable+4 (returns uint32)
    uint32_t vfRet = reinterpret_cast<uint32_t (*)()>(g_engineSingleton.vtable[1])();
    g_engineSingleton.someResult = transformValue(vfRet);

    // Call virtual function at vtable+0x10 (void)
    reinterpret_cast<void (*)()>(g_engineSingleton.vtable[4])();

    // Register this singleton into the global linked list
    g_engineSingleton.next = g_singletonHead;
    g_singletonCounter++;
    g_singletonHead = &g_engineSingleton;
    g_engineSingleton.id = g_singletonCounter;
}