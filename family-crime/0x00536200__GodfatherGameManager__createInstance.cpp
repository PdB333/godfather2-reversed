// FUNC_NAME: GodfatherGameManager::createInstance

#include <cstdint>

// Forward declaration of base initializer (likely parent class constructor)
extern void FUN_006126d0();

// Global singleton instance for the main game manager
// Object layout at 0x0121a1f0 (size: 0x128 bytes)
struct GodfatherGameManager {
    void** vtable;  // +0x00: virtual function table pointer
    int field_C0;   // +0xC0
    int field_C4;   // +0xC4
    int field_C8;   // +0xC8
    int field_CC;   // +0xCC
    int field_100;  // +0x100
    int field_104;  // +0x104
    int field_108;  // +0x108
    int field_10C;  // +0x10C
    int field_110;  // +0x110
    int field_114;  // +0x114
    int field_118;  // +0x118
    int field_11C;  // +0x11C
    int field_120;  // +0x120
    int field_124;  // +0x124
    int field_128;  // +0x128
};

// The global instance resides at a fixed address (0x0121a1f0)
static GodfatherGameManager g_GodfatherGameManager;

// Factory function that creates the global singleton
// Returns pointer to the initialized instance
GodfatherGameManager* __cdecl createGodfatherGameManager(void) {
    // Call base class constructor (possibly EARS::Framework::Object or similar)
    FUN_006126d0();
    
    // Set vtable to the class-specific table
    g_GodfatherGameManager.vtable = reinterpret_cast<void**>(0x00e38788);
    
    // Zero-initialize all member fields
    g_GodfatherGameManager.field_120 = 0;
    g_GodfatherGameManager.field_124 = 0;
    g_GodfatherGameManager.field_128 = 0;
    
    g_GodfatherGameManager.field_C0 = 0;
    g_GodfatherGameManager.field_C4 = 0;
    g_GodfatherGameManager.field_C8 = 0;
    g_GodfatherGameManager.field_CC = 0;
    
    g_GodfatherGameManager.field_100 = 0;
    g_GodfatherGameManager.field_104 = 0;
    g_GodfatherGameManager.field_108 = 0;
    g_GodfatherGameManager.field_10C = 0;
    g_GodfatherGameManager.field_110 = 0;
    g_GodfatherGameManager.field_114 = 0;
    g_GodfatherGameManager.field_118 = 0;
    g_GodfatherGameManager.field_11C = 0;
    
    return &g_GodfatherGameManager;
}