// FUNC_NAME: ObjectPool::registerObject

// This function registers an object in a global pool. It searches for an empty slot (inUse == 0)
// and fills it with fixed global type identifiers. It also stores the 'this' pointer and the
// second parameter (objectSizeMultiplier) to global variables and invokes a virtual factory method.
// The virtual call likely allocates or creates the actual object.
// Global pool structure: PoolSlot[?] at 0x011f6bb8, each 12 bytes (3 ints: objectPtr, type, inUse).
// The function iterates over slots, uses a static index counter (currentSlotIndex).

void __fastcall ObjectPool::registerObject(int objectSizeMultiplier)
{
    // Local struct passed to virtual function: (sizeType, flags, extra)
    struct PoolRequest {
        int sizeType;   // 2
        int flags;      // 16
        int extra;      // 0
    };
    
    // Static globals (likely file-scope or class statics)
    static int g_poolInitialized = 0;                       // DAT_01163edc - always set to 0 (redundant?)
    static void* g_storedThis = nullptr;                    // DAT_01163ed4
    static int g_storedMultiplier = 0;                      // DAT_01163ed8
    static void* g_allocatedObject = nullptr;               // DAT_01163ee0
    static int g_currentSlotIndex = 0;                      // DAT_01163ee4
    
    // Global pool array (static, 12 bytes per slot)
    struct PoolSlot {
        int* objectPtr;      // +0x00
        int* type;           // +0x04
        int inUse;           // +0x08
    };
    
    // Note: The pool is defined at fixed addresses. For clarity, treat it as an array.
    // Addresses: base +0x00 (DAT_011f6bb8), +0x04 (DAT_011f6bbc), +0x08 (DAT_011f6bc0)
    // The loop starts by checking the inUse of the first slot (at base+8).
    
    PoolSlot* pool = reinterpret_cast<PoolSlot*>(0x011f6bb8);
    
    g_poolInitialized = 0;
    
    PoolRequest request;
    request.sizeType = 2;    // local_c
    request.flags = 16;      // local_8
    request.extra = 0;       // local_4
    
    g_storedThis = this;
    g_storedMultiplier = objectSizeMultiplier;
    
    // Call virtual function 0 (factory method) with parameters (objectSizeMultiplier * 8, &request)
    // The vtable pointer is at the beginning of 'this'.
    typedef void* (__thiscall *FactoryMethod)(void*, int, PoolRequest*);
    FactoryMethod factory = reinterpret_cast<FactoryMethod>((void***)this)[0][0];
    g_allocatedObject = factory(this, objectSizeMultiplier * 8, &request);
    
    g_currentSlotIndex = 0;
    
    // Search for an empty slot in the pool (where inUse == 0)
    while (true) {
        PoolSlot* slot = &pool[g_currentSlotIndex];
        if (slot->inUse == 0) {
            // Found empty slot: fill with two global type identifiers and mark as used
            slot->objectPtr = reinterpret_cast<int*>(DAT_00e446dc);  // global constant
            slot->type = reinterpret_cast<int*>(DAT_00e2b1a4);       // global constant
            slot->inUse = 1;
            return;
        }
        g_currentSlotIndex++;
        if (g_currentSlotIndex >= 10) {  // assuming pool size = 10 (based on address range 0x011f6bc0 to 0x011f6bf0 = 48 bytes / 12 = 4 entries? Actually 0x11f6bf0 - 0x11f6bc0 = 0x30 = 48 bytes, so 4 slots. But loop condition uses pointer comparison: (int)pcVar1 < 0x11f6bf0, so at most 4 slots. We'll declare 4.
            g_currentSlotIndex = -1;
            return;
        }
    }
}