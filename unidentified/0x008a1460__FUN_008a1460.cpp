// FUNC_NAME: SomeClass::Constructor
// Function address: 0x008a1460
// Role: Constructor for a class of size 0x58 with vtable, two static pointers, and a subobject at offset 0x50

// Known class candidates: possibly DialogTreeManager, ChatterPlaybackManager, or similar
// Offsets:
// +0x00: vtable pointer
// +0x3C: pointer to static data (PTR_LAB_00d78bb4)
// +0x48: pointer to static data (PTR_LAB_00d78bb0)
// +0x50: subobject (initialized via FUN_004086d0 and FUN_00408310)
// Size: 0x58

class SomeClass {
public:
    // Vtable at +0x00
    void* vtable;               // +0x00
    // Padding or unknown members up to +0x3C
    void* somePointer1;         // +0x3C
    void* somePointer2;         // +0x48
    // Subobject at +0x50 (likely of type SubObject)
    SubObject subObj;           // +0x50 (size? 8 bytes? but class total 0x58)

    // Constructor
    // param_2: flag (if bit 0 set, deallocate with operator delete)
    __thiscall SomeClass(byte flag) {
        // Set vtable
        vtable = &PTR_FUN_00d78bc4;

        // Initialize static pointers
        somePointer1 = &PTR_LAB_00d78bb4;  // +0x3C
        somePointer2 = &PTR_LAB_00d78bb0;  // +0x48

        // Initialize subobject at +0x50
        // FUN_004086d0 is likely SubObject::SubObject() (constructor)
        SubObject_Constructor(&subObj);
        // FUN_00408310 is likely SubObject::init() or similar
        subObj.init();

        // Global function call (maybe singleton manager init)
        GlobalInitializationFunction();

        // If flag indicates allocation, deallocate with operator delete
        if (flag & 1) {
            operator_delete(this, 0x58);
        }
    }
};