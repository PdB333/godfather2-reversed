// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x006d5e00
// Role: Constructor for the main game manager (GodfatherGameManager). Initializes vtable, interface pointers, and a sub-object at offset 0x50.

void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this) {
    // Set vtable pointer for the class (first field at offset 0)
    *reinterpret_cast<uint32_t*>(this) = reinterpret_cast<uint32_t>(&PTR_FUN_00d5f42c);

    // Set two additional pointer fields at offsets 0x3C (60) and 0x48 (72)
    // These likely point to secondary vtable or interface tables for multiple inheritance.
    this->field_0x3C = reinterpret_cast<uint32_t*>(&PTR_LAB_00d5f41c); // +0x3C
    this->field_0x48 = reinterpret_cast<uint32_t*>(&PTR_LAB_00d5f418); // +0x48

    // Initialize sub-object at offset 0x50 (80 bytes from this) with a two-step construction.
    // The sub-object is probably a string, container, or another embedded object.
    void* subObj = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(this) + 0x50);
    FUN_004086d0(subObj); // First initialization (likely constructor)
    FUN_00408310(subObj); // Second initialization (likely post-constructor setup)

    // Global initialization call (e.g., initialize singleton systems)
    FUN_0046c640();
}