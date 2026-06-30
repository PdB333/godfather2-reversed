// FUNC_NAME: EARSApplication::EARSApplication
class EARSApplication {
public:
    void* vtable;      // +0x00  (primary vtable pointer)
    void* secondaryVtable; // +0x04  (secondary vtable, e.g., for another base class)

    // Constructor-like initialization function, returns this pointer
    // param2: flags (bit 0 indicates heap-allocated, triggers deallocation)
    EARSApplication* construct(byte flags);
};

// Global data references
extern void* DAT_012069d4;            // global instance used by engine initialization
extern int _DAT_0122347c;             // global flag/resource counter

// External engine functions (inference based on context)
extern void engineInitSubsystem(void* globalRef);  // FUN_004086d0
extern void engineInitCore();                      // FUN_004083d0
extern void engineDeallocator(EARSApplication* obj); // FUN_009c8eb0

EARSApplication* EARSApplication::construct(byte flags) {
    // Set initial vtable pointers (base class vtables)
    this->vtable = (void*)0x00e327f0;          // +0x00 base class vtable
    this->secondaryVtable = (void*)0x00e327f4; // +0x04 secondary vtable

    // Initialize engine subsystems using global data
    engineInitSubsystem(&DAT_012069d4);
    engineInitCore();

    // Replace primary vtable with derived class vtable
    this->vtable = (void*)0x00e32804;           // +0x00 derived class vtable

    // Reset a global counter/flags
    _DAT_0122347c = 0;

    // If the object was heap-allocated (flag bit 0), invoke deallocation
    if (flags & 1) {
        engineDeallocator(this);
    }

    return this;
}