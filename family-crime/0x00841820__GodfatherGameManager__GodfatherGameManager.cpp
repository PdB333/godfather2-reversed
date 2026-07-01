// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00841820
// Role: Constructor for GodfatherGameManager, handles singleton registration and subsystem initialization.

#include <cstdint>

// Forward declarations
void BaseClassConstructor(void); // FUN_00848d00
void SubSystemInit(void);        // FUN_005953b0
void* MemoryAllocator(int size, void* params); // FUN_009c8f80
void* ObjectFactoryAllocate(void); // FUN_00841140 (returns pointer to allocated block)
void OperatorDelete(void* ptr); // FUN_004daf90

// Global singleton pointer
static void* g_pSingletonInstance = nullptr; // DAT_0112dcb4
static void* g_pSingletonNextBackup = nullptr; // DAT_0112dcb8 (probably old next pointer)

class GodfatherGameManager {
public:
    // vtable pointers at certain offsets
    // +0x00: vtable pointer 1 (PTR_FUN_00d7468c)
    // +0x0C: vtable pointer 2 (set twice: PTR_LAB_00d745c0 then PTR_LAB_00d74670)
    // +0x48: offset for the actual singleton object within larger allocation block

    __thiscall GodfatherGameManager() {
        BaseClassConstructor();          // Initialize base class (FUN_00848d00)
        SubSystemInit();                 // Subsystem 1 init (called 7 times)
        SubSystemInit();
        SubSystemInit();
        SubSystemInit();
        SubSystemInit();
        SubSystemInit();
        SubSystemInit();

        // Set first vtable pointer at offset +0x0C? Actually param_1[3] is offset 12 bytes
        this->vtable2 = &PTR_LAB_00d745c0; // PTR_LAB_00d745c0 (vtable for base class A)
        this->vtable1 = &PTR_FUN_00d7468c; // Set primary vtable at +0x00
        this->vtable2 = &PTR_LAB_00d74670; // Set secondary vtable at +0x0C again (vtable for derived class B)

        // Check if singleton already exists and is not a marker value 0x48
        if (g_pSingletonInstance != nullptr && g_pSingletonInstance != (void*)0x48) {
            return; // Already initialized, just return this
        }

        // Allocate memory (size 0x6c) with allocator parameters
        struct AllocParams {
            uint32_t field0; // 2
            uint32_t field1; // 0x10
            uint32_t field2; // 0
        } params = {2, 0x10, 0};
        void* pAllocResult = MemoryAllocator(0x6c, &params); // returns a memory block pointer
        if (pAllocResult != nullptr) {
            void* pObject = ObjectFactoryAllocate(); // Returns pointer to an object inside block
            if (pObject != nullptr) {
                // The actual singleton is offset by 0x48 from the allocated block
                pObject = (uint8_t*)pObject + 0x48;
                goto CheckSingleton;
            }
        }
        pObject = nullptr;

CheckSingleton:
        if (g_pSingletonInstance != pObject) {
            // If old singleton exists and is not nullptr, delete it
            if (g_pSingletonInstance != nullptr) {
                OperatorDelete(&g_pSingletonInstance); // Actually FUN_004daf90 takes a pointer?
                // Note: The original code passes address of global variable, likely a cleanup routine
            }
            g_pSingletonInstance = pObject;
            if (pObject != nullptr) {
                // Link the new singleton into a chain: store old "next" pointer, then set new object's next to the global head address
                g_pSingletonNextBackup = *(void**)((uint8_t*)pObject + 4); // Save original next pointer
                *(void**)((uint8_t*)pObject + 4) = &g_pSingletonInstance; // Point to the global variable itself
            }
        }
        return;
    }

private:
    void* vtable1; // offset +0x00
    void* vtable2; // offset +0x0C (overlapping with other fields? actually param_1[3] is at +0x0C)
    // Other members follow
};

// External symbols for actual vtable addresses
extern void* PTR_LAB_00d745c0;
extern void* PTR_FUN_00d7468c;
extern void* PTR_LAB_00d74670;