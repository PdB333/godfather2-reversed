// FUNC_NAME: 0x006b0580 - BricknMortarManager::shutdownCleanup (destructor-like cleanup)
// Address: 0x006b0580
// Role: Cleans up all BricknMortar (building resource) subsystems, destroys component array, releases sub-objects, resets vtable and global singleton pointer.

#include <cstdint>

// Forward declarations for called functions (guessed names based on EA EARS patterns)
extern void ResourceManager::registerResource(uint32_t hash);
extern void StringTable::registerString(const char* str);
extern void GlobalObject::release(uint32_t* globalAddr);
extern void GlobalObject::addRef(uint32_t* globalAddr);
extern void MemoryManager::free(void* ptr);
extern void SystemManager::shutdown();
extern void GlobalCleanup::finalize();

// Known global singleton pointer for BricknMortarManager
extern BricknMortarManager* g_pBricknMortarManager; // DAT_0112a558

// vtable pointers (symbols from Ghidra)
extern void* PTR_FUN_00d5e1dc; // initial vtable slot 0
extern void* PTR_LAB_00d5e1cc; // vtable slot 1
extern void* PTR_LAB_00d5e1c0; // vtable slot 4
extern void* PTR_LAB_00d5e1b0; // vtable slot 6
extern void* PTR_LAB_00e30fe0; // vtable slot 6 (after cleanup)
extern void* PTR_LAB_00d5dfd8; // final vtable slot 0

// Global static objects (DAT_ addresses)
extern uint32_t DAT_0112a620;
extern uint32_t DAT_0112a5e0;
extern uint32_t DAT_0112a600;
extern uint32_t DAT_0112a650;
extern uint32_t DAT_0112a660;
extern uint32_t DAT_0112a628;
extern uint32_t DAT_0112a5b4;
extern uint32_t DAT_0112a5f0;
extern uint32_t DAT_0112a5e8;
extern uint32_t DAT_0112a5d8;
extern uint32_t DAT_0112a610;
extern uint32_t DAT_0112a648;
extern uint32_t DAT_0112a640;
extern uint32_t DAT_0112a5a4;
extern uint32_t DAT_0112a5c4;
extern uint32_t DAT_0112a5bc;
extern uint32_t DAT_0112a5ac;
extern uint32_t DAT_0112a5cc;
extern uint32_t DAT_0112a618;
extern uint32_t DAT_0112a630;
extern uint32_t DAT_0112a594;
extern uint32_t DAT_0112a638;
extern uint32_t DAT_0112a608;
extern uint32_t DAT_0112a59c;
extern uint32_t DAT_0112a5f8;
extern uint32_t DAT_0112a658;

class BricknMortarManager {
public:
    // Offset 0: vtable pointer
    // Offset 1: secondary vtable? (param_1[1])
    // Offset 4: another vtable? (param_1[4])
    // Offset 6: another vtable? (param_1[6])
    // Offset 0x0d: object pointer (released if non-null)
    // Offset 0x10: object pointer (released if non-null)
    // Offset 0x07: object pointer (released if non-null)
    // Offset 0x3E-0x41: array of 10 component structs (each 4 bytes? actually pairs of function pointer and object pointer)
    // Offset 0x42: start of component array? (used as base for puVar1)

    // This is the cleanup method (not a true destructor but called during destruction)
    void shutdownCleanup();
};

void BricknMortarManager::shutdownCleanup()
{
    uint32_t* componentObjPtr;
    int componentCount;

    // Set initial vtable pointers
    this->vtable0 = &PTR_FUN_00d5e1dc; // *param_1
    this->vtable1 = &PTR_LAB_00d5e1cc; // param_1[1]
    this->vtable4 = &PTR_LAB_00d5e1c0; // param_1[4]
    this->vtable6 = &PTR_LAB_00d5e1b0; // param_1[6]

    // Register a resource and string (likely for identification)
    ResourceManager::registerResource(0x32b7d466);
    StringTable::registerString("BricknMortarRes");

    // Release all global static objects (order matches the original)
    GlobalObject::release(&DAT_0112a620);
    GlobalObject::release(&DAT_0112a5e0);
    GlobalObject::release(&DAT_0112a600);
    GlobalObject::release(&DAT_0112a650);
    GlobalObject::release(&DAT_0112a660);
    GlobalObject::release(&DAT_0112a628);
    GlobalObject::release(&DAT_0112a5b4);
    GlobalObject::release(&DAT_0112a5f0);
    GlobalObject::release(&DAT_0112a5e8);
    GlobalObject::release(&DAT_0112a5d8);
    GlobalObject::release(&DAT_0112a610);
    GlobalObject::release(&DAT_0112a648);
    GlobalObject::release(&DAT_0112a640);
    GlobalObject::release(&DAT_0112a5a4);
    GlobalObject::release(&DAT_0112a5c4);
    GlobalObject::addRef(&DAT_0112a5bc);   // special: increment ref before release
    GlobalObject::release(&DAT_0112a5bc);  // then release
    GlobalObject::addRef(&DAT_0112a5ac);   // same pattern
    GlobalObject::release(&DAT_0112a5ac);
    GlobalObject::release(&DAT_0112a5cc);
    GlobalObject::release(&DAT_0112a618);
    GlobalObject::release(&DAT_0112a630);
    GlobalObject::release(&DAT_0112a594);
    GlobalObject::release(&DAT_0112a638);
    GlobalObject::release(&DAT_0112a608);
    GlobalObject::release(&DAT_0112a59c);
    GlobalObject::release(&DAT_0112a5f8);
    GlobalObject::release(&DAT_0112a658);

    // Iterate through an array of 10 component entries (each entry is 4 bytes? seems like pair of 4-byte fields)
    // Entry structure: at offset -4 from base: object pointer; at offset -1: function pointer
    // Base offset: 0x42 (0x42 * 4 = 0x108 from object start? Actually param_1 is uint32_t*, so offset in units of 4 bytes)
    // param_1[0x42] is the start of the array. The loop processes 10 entries backwards.
    componentCount = 9;
    componentObjPtr = &this->componentArray[0x42]; // param_1 + 0x42

    do {
        if (componentObjPtr[-4] != 0) {
            // Call the destructor function stored at offset -1 with the object pointer at -4
            (*(void (*)(uint32_t*))componentObjPtr[-1])(componentObjPtr[-4]);
        }
        componentCount--;
        componentObjPtr -= 4; // move to previous entry (multi-element array)
    } while (componentCount >= 0);

    // Release additional sub-objects if they exist
    if (this->subObject1 != 0) { // param_1[0xd]
        MemoryManager::free(this->subObject1);
    }
    if (this->subObject2 != 0) { // param_1[0x10]
        MemoryManager::free(this->subObject2);
    }
    if (this->subObject3 != 0) { // param_1[0x7]
        MemoryManager::free(this->subObject3);
    }

    // Change vtable slot 6 to a new table (after cleanup)
    this->vtable6 = &PTR_LAB_00e30fe0;

    // Final global shutdown calls
    SystemManager::shutdown();
    GlobalCleanup::finalize();

    // Set final vtable slot 0
    this->vtable0 = &PTR_LAB_00d5dfd8;

    // Reset global singleton pointer to null
    g_pBricknMortarManager = 0;
}