// FUNC_NAME: CriticalSectionManager::CriticalSectionManager
// Function address: 0x0065ceb0
// Constructor for the global critical section manager.
// Sets up two critical sections, stores a thread ID, and registers with the system.

#include <windows.h>  // for CRITICAL_SECTION and InitializeCriticalSection

class CriticalSectionManager {
public:
    // Virtual table at offset 0 (likely base class vtable)
    // +0x00: vtable pointer
    // +0x04: second vtable pointer (multiple inheritance)
    // +0x08: pointer to an internal object (probably a thread or mutex wrapper)
    // +0x0C: first CRITICAL_SECTION (24 bytes)
    // +0x24: second CRITICAL_SECTION (24 bytes)
    // +0x4C: ... (after critical sections)
    // +0x6C: param_2 stored here (thread ID or identifier)
    // +0x70: some DWORD (0)
    // +0x74: short (0)
    // +0x76: short (0)

    void* vtable1;           // +0x00
    void* vtable2;           // +0x04
    void* internalObject;    // +0x08
    CRITICAL_SECTION cs1;    // +0x0C
    CRITICAL_SECTION cs2;    // +0x24
    // ... padding/other data ...
    unsigned int threadID;   // +0x6C
    unsigned int field_70;   // +0x70
    unsigned short field_74; // +0x74
    unsigned short field_76; // +0x76
    // ... more may follow ...

    // Constructor
    CriticalSectionManager(unsigned int threadIDParam) {
        // Set up vtables (base and possibly derived)
        this->vtable1 = (void*)&PTR_FUN_00e43440;   // base vtable
        this->vtable2 = (void*)&PTR_LAB_00e434bc;   // second vtable (adjusted later)
        this->internalObject = (void*)DAT_01205a64; // global pointer to a subsystem

        // Initialize the two critical sections
        InitializeCriticalSection(&this->cs1);
        InitializeCriticalSection(&this->cs2);

        // Unused loop (just a delay or stub)
        unsigned int count = 4;
        do {
            count >>= 2;
        } while (count != 0);

        // Call internal init functions
        FUN_0065df10(); // likely initializes something global
        FUN_0065df10(); // called twice

        // Store the parameter (likely thread ID)
        this->threadID = threadIDParam;

        // Call a virtual function from the internal object (vtable offset 8, function index 2)
        void (*internalFunc)() = (void (*)())(*(int*)(this->internalObject) + 8);
        internalFunc();

        // Zero out some fields
        this->field_76 = 0;
        this->field_74 = 0;
        this->field_70 = 0;

        // Additional initialization
        FUN_0065d080(this);

        // Register with the system platform layer
        int* platformObj = (int*)FUN_00ad8d40();
        if (platformObj != nullptr) {
            // Call vtable+0x34 to get a function pointer, then call vtable+4 with this
            typedef void* (*GetFunc)(void*);
            typedef void (*RegisterFunc)(void*);
            void* funcObj = ((GetFunc)(*(int*)platformObj + 0x34))(platformObj);
            ((RegisterFunc)(*(int*)funcObj + 4))(this);
        } else {
            // Error path: call a null pointer function (likely crash)
            ((void (*)())(/* null */))();
        }
    }
};

// Global singleton pointer
extern CriticalSectionManager* DAT_0122355c; // set to this during construction

// External references
extern void* DAT_01205a64; // internal object pointer
extern void FUN_0065df10();
extern void FUN_0065d080(void*);
extern void* FUN_00ad8d40();

// Vtable symbols (defined elsewhere)
extern void* PTR_FUN_00e43440;
extern void* PTR_LAB_00e434bc;
extern void* PTR_LAB_00e434c0; // original vtable2 before overwrite