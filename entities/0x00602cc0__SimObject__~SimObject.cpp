// FUNC_NAME: SimObject::~SimObject

// Reconstructed destructor for SimObject (EARS engine base class)
// Address: 0x00602cc0
// Called from SimObject::destroy (0x00602ca0) and probably virtual destructor chain

struct SimObject {
    // +0x00: vtable pointer (e.g., PTR_FUN_00e40874)
    // +0x04: unknown
    // +0x08: secondary vtable pointer (e.g., PTR_LAB_00e40880)
    // +0x0C: unknown
    // +0x10: unknown
    // +0x14: tertiary vtable/function pointer (e.g., PTR_LAB_00e40890)
    // +0x18: pointer to interface vtable (e.g., ISomeInterface)
    // +0x1C: byte flag (set to 0 here, likely 'isDestroying')
    // +0x20: child object pointer (tested for non-zero)
    // +0x24: allocated memory block 1
    // +0x28: unknown
    // +0x2C: unknown
    // +0x30: allocated memory block 2
    // +0x34: unknown
};

// Forward declarations for functions called
void __thiscall FUN_00602db0(SimObject* child);  // recursively destroy child
void __fastcall FUN_004086d0(void* global);       // release global resource
void __fastcall FUN_00408310(void* global);       // release global resource (different pool)
void __fastcall FUN_009c8f10(void* ptr);          // free memory
void __thiscall FUN_004083d0();                    // engine shutdown step
void __thiscall FUN_0049c640();                    // engine shutdown step

// Virtual interface assumed
struct ISomeInterface {
    virtual void method0();  // +0x00
    virtual void method1();  // +0x04
    virtual void method2();  // +0x08
    virtual void onDestroy(); // +0x0C (called here)
};

void __thiscall SimObject::~SimObject(SimObject* this) {
    // ------------------------------------------
    // Start of destruction: switch vtable to "destroying" state
    // ------------------------------------------
    *(int*)this = (int)&PTR_FUN_00e40874;          // set base vtable to destroying variant
    *(int*)((char*)this + 0x08) = (int)&PTR_LAB_00e40880; // secondary vtable
    *(int*)((char*)this + 0x14) = (int)&PTR_LAB_00e40890; // tertiary function pointer (changed later)

    *((char*)this + 0x1C) = 0;                     // clear destroy-in-progress flag

    // If this object has a child, recursively destroy it
    if (*(SimObject**)((char*)this + 0x20) != 0) {
        FUN_00602db0(*(SimObject**)((char*)this + 0x20)); // child destruction
    }

    // Release global static resources (likely reference counters)
    // The order and matching of these suggest pairs of Acquire/Release
    FUN_004086d0(&DAT_01222230);
    FUN_004086d0(&DAT_01222248);
    FUN_004086d0(&DAT_01222238);
    FUN_004086d0(&DAT_01222258);
    FUN_00408310(&DAT_01222250);
    FUN_00408310(&DAT_01222240);
    FUN_00408310(&DAT_01222230);
    FUN_00408310(&DAT_01222248);
    FUN_00408310(&DAT_01222238);
    FUN_00408310(&DAT_01222258);

    // Call interface virtual method (likely final cleanup)
    ISomeInterface* iface = *(ISomeInterface**)((char*)this + 0x18);
    if (iface) {
        iface->onDestroy();  // virtual call at index 3 (offset +0x0C)
    }

    // Free two dynamically allocated memory blocks
    if (*(void**)((char*)this + 0x30) != 0) {
        FUN_009c8f10(*(void**)((char*)this + 0x30));
    }
    if (*(void**)((char*)this + 0x24) != 0) {
        FUN_009c8f10(*(void**)((char*)this + 0x24));
    }

    // Update tertiary vtable to indicate destruction is complete
    *(int*)((char*)this + 0x14) = (int)&PTR_LAB_00e40894;

    // Global engine state update
    DAT_012234a4 = 0;          // clear global flag (e.g., "isSimulating")
    FUN_004083d0();            // perform engine-level shutdown tasks
    FUN_0049c640();            // finalize destruction sequence
}