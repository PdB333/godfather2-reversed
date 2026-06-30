// FUNC_NAME: SomeEARSObject::destructor
// Address: 0x00749e70
// Role: Destructor for a class derived from EARS framework. Sets vtable, cleans up member at +0x68, calls global cleanup, then deletes if flag is set.

// Reconstructed C++ code
// Assumes the class has a vtable pointer at offset 0x00, and a pointer member at offset 0x68.

class SomeEARSObject {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Member at +0x68 (0x1a * 4)
    SomeOtherObject* subObject;

    // Destructor
    void* __thiscall destructor(byte flags) {
        // Set vtable to base class vtable (likely base destructor table)
        this->vtable = &PTR_LAB_00d63090;

        // Destroy sub-object if present
        if (this->subObject != 0) {
            // Call destructor for sub-object (function at 0x004daf90)
            subObject->destructor(); // assuming standard cleanup
        }

        // Call global cleanup function (e.g., disable/unregister)
        globalCleanup(); // function at 0x0080ea60

        // If the flags indicate this is a heap-allocated object, deallocate
        if ((flags & 1) != 0) {
            operatorDelete(this); // function at 0x00624da0
        }

        return this;
    }
};

// External helper functions
void globalCleanup(); // placeholder
void operatorDelete(void* ptr); // custom deallocation