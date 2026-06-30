// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

void __thiscall GodfatherGameManager::~GodfatherGameManager() {
    // Set vtable pointer to the most derived class's vtable for destruction
    // +0x00: vtable pointer
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d5fdbc; // vtable

    // Set function pointers at offsets 0x3C (0x0F*4) and 0x48 (0x12*4)
    // +0x3C: callback/function pointer 1
    reinterpret_cast<FuncPtr*>(this)[0x0F] = &PTR_LAB_00d5fdac;
    // +0x48: callback/function pointer 2
    reinterpret_cast<FuncPtr*>(this)[0x12] = &PTR_LAB_00d5fda8;

    // Destroy subobject at offset 0x60 (0x18*4)
    // +0x60: SubObject3
    FUN_00408310(reinterpret_cast<void*>(reinterpret_cast<uint8*>(this) + 0x60));

    // Destroy subobject at offset 0x50 (0x14*4) – first pass
    // +0x50: SubObject1
    FUN_004086d0(reinterpret_cast<void*>(reinterpret_cast<uint8*>(this) + 0x50));

    // Destroy subobject at offset 0x50 again? Possibly a second step for SubObject1
    FUN_00408310(reinterpret_cast<void*>(reinterpret_cast<uint8*>(this) + 0x50));

    // Destroy subobject at offset 0x58 (0x16*4) – first pass
    // +0x58: SubObject2
    FUN_004086d0(reinterpret_cast<void*>(reinterpret_cast<uint8*>(this) + 0x58));

    // Destroy subobject at offset 0x58 again? Possibly a second step for SubObject2
    FUN_00408310(reinterpret_cast<void*>(reinterpret_cast<uint8*>(this) + 0x58));

    // Destroy a global object at DAT_012069c4 (e.g., shared resource)
    FUN_004086d0(&DAT_012069c4);

    // If this instance is the global singleton, clear the pointer
    // g_pGodfatherGameManager is DAT_0112a9c0
    if (this == reinterpret_cast<GodfatherGameManager*>(DAT_0112a9c0)) {
        DAT_0112a9c0 = nullptr;
    }

    // Final cleanup (global static data, logging, or memory management)
    FUN_0046c640();
}