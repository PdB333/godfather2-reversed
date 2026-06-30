// FUNC_NAME: ManagerRegistry::registerManager

#include <cstdint>

// Global variable declarations (from Ghidra analysis)
extern void* DAT_0121be88;          // +0x00: Manager vtable pointer
extern uint32_t DAT_0121be90;       // +0x04: Result from manager creation
extern void* DAT_0121be8c;          // +0x08: Next manager in list
extern uint32_t DAT_0121be94;       // +0x0C: Manager ID
extern void* DAT_012058ec;          // +0x00: Head of manager list
extern uint32_t DAT_012058f8;       // +0x00: Next free manager ID

// External function declarations
extern void* FUN_0060d740(void* param);  // Converts manager handle to structure?
extern void FUN_0052e5f0(void);          // Post-registration initialization

void ManagerRegistry::registerManager(void)
{
    void* uVar1;
    
    // Call virtual function offset 0x04 on the vtable (likely creates manager instance)
    uVar1 = (*(code**)(DAT_0121be88 + 4))();
    
    // Convert result and store as manager handle
    DAT_0121be90 = (uint32_t)FUN_0060d740(uVar1);
    
    // Call virtual function offset 0x10 (e.g., start)
    (*(code**)(DAT_0121be88 + 0x10))();
    
    // Link current head as next in list
    DAT_0121be8c = DAT_012058ec;
    
    // Increment global ID counter
    DAT_012058f8 = DAT_012058f8 + 1;
    
    // Set head to this manager's vtable pointer
    DAT_012058ec = &DAT_0121be88;
    
    // Assign unique ID to this manager
    DAT_0121be94 = DAT_012058f8;
    
    // Call post-registration initializer
    FUN_0052e5f0();
    
    return;
}