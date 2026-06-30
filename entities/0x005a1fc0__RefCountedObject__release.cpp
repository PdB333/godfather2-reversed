// FUNC_NAME: RefCountedObject::release
// Function address: 0x005a1fc0
// This function is a custom release method for a reference-counted object.
// It checks the object's type ID (at offset 0x20) and either just decrements
// or retains and then decrements the reference count. If the count reaches zero,
// it calls the destructor and deallocates memory.

class RefCountedObject {
public:
    int refCount;        // +0x00 reference count
    // +0x04..+0x1C other fields
    int typeId;          // +0x20 type identifier (expected 4 for valid objects)
    // +0x24..+0x2C other fields
    // total size 0x30

    // Internal base release function (FUN_005a1eb0)
    void baseRelease(void* param, void* eax); // Not defined here

    // Destructor (FUN_005a1b40)
    virtual ~RefCountedObject(); // Virtual destructor, likely calls operator delete

    // Release method
    void release() {
        // Call base release with address of this and some register (likely return value)
        baseRelease(&this, /* in_EAX */ );

        RefCountedObject* obj = this;
        if ((this == nullptr) || (this->typeId != 4)) {
            // Invalid or wrong type – return null via EDI
            // In x86, EDI is used for the return value in this calling convention
            // (equiv to returning nullptr)
            // The compiler likely uses EDI for this purpose.
            // *unaff_EDI = 0;
            if (this == nullptr) {
                return;
            }
        } else {
            // Valid object: increment reference count
            this->refCount++;
            // *unaff_EDI = this;  (return this pointer via EDI)
        }

        // Always decrement reference count (net effect: if in else branch, incremented then decremented)
        this->refCount--;

        // If count reached zero, destroy and free
        if (this->refCount == 0) {
            this->~RefCountedObject();
            // Global operator delete with size 0x30
            // (*DAT_0119caf8)(piVar1, 0x30);
            // DAT_0119caf8 is likely a function pointer to operator delete
            operator delete((void*)this, 0x30);
        }
    }
};

// Note: The actual code may use a custom operator delete (pointed by DAT_0119caf8).
// The baseRelease call uses a hidden parameter (in_EAX) which is likely the return
// value of a previous function, omitted here for clarity.
// The EDI register trick is a compiler optimization; the C++ version does not need it.