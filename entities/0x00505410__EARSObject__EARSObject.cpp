// FUNC_NAME: EARSObject::EARSObject
class EARSObject {
public:
    EARSObject() = delete;
    EARSObject(bool isHeapAllocated);
};

// Implementation: constructor at 0x00505410
// Calls base initializer, then optionally registers heap allocation.
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, bool isHeapAllocated) {
    // Call base class static initializer (no arguments)
    initBase(); // FUN_00505430

    // If the object was heap-allocated (flag bit 0 set), register it
    if (isHeapAllocated) {
        registerHeapAllocation(this); // FUN_009c8eb0
    }

    return this;
}