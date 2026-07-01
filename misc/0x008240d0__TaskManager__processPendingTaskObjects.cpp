// FUNC_NAME: TaskManager::processPendingTaskObjects

#include <cstdint>

// Global variables representing the task object table and count
extern void** g_taskObjectTable; // DAT_0112db50 - array of 8-byte entries
extern uint32_t g_taskObjectCount; // DAT_0112db54 - number of entries

// Forward declarations of called functions
void PreUpdate(uint32_t unk);        // FUN_004df830
void PerformSystemUpdate();          // FUN_004df600
void ReleaseTaskObject(void** pObj); // FUN_004daf90 - releases wrapper pointer
void PostProcess();                  // FUN_00823e30

void TaskManager::processPendingTaskObjects() {
    uint32_t i = 0;
    
    if (g_taskObjectCount != 0) {
        do {
            // Each entry is an 8-byte structure: first 4 bytes = pointer to actual object
            uint32_t** ppTaskObject = (uint32_t**)(g_taskObjectTable + i * 8);
            uint32_t* pTaskObject = *ppTaskObject; // local_10
            
            // Save original value for later? Not used further.
            uint32_t originalField = 0;
            if (pTaskObject != nullptr) {
                originalField = pTaskObject[1];   // Field at offset 0x04
                pTaskObject[1] = (uint32_t)&pTaskObject; // Set field to address of stack variable (debug?)
            }
            
            // Perform pre-update and system update
            PreUpdate(0);
            PerformSystemUpdate();
            
            // Access reference count block at offset 0x1C (pTaskObject[7])
            uint32_t* pRefBlock = (uint32_t*)pTaskObject[7];
            if (pRefBlock != nullptr) {
                // Decrement reference count stored at pRefBlock[1]
                int* pRefCount = pRefBlock + 1;
                *pRefCount = *pRefCount - 1;
                if (*pRefCount == 0) {
                    // Call destructor via vtable at pRefBlock[0] + 4
                    void (*destructor)(void) = (void (*)(void))(* (uint32_t*)(*pRefBlock + 4));
                    destructor();
                }
            }
            
            // Call virtual method at vtable index 0 with argument 1
            if (pTaskObject != nullptr) {
                void (*virtualMethod)(uint32_t) = (void (*)(uint32_t))(*pTaskObject);
                if (virtualMethod != nullptr) {
                    virtualMethod(1);
                }
                // If still valid, release the wrapper pointer
                if (pTaskObject != nullptr) {
                    ReleaseTaskObject((void**)&pTaskObject);
                }
            }
            
            i++;
        } while (i < g_taskObjectCount);
    }
    
    PostProcess();
    return;
}