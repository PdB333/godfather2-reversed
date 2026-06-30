// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x0074c9f0
// Role: Destructor for EARSObject. Releases member pointers and chains to base destructor.

// Forward declarations of helper functions
// FUN_004daf90: Releases a sub-object pointer (sets to null)
extern void __cdecl releaseSubObject(void** ptrToPtr);
// FUN_009c8eb0: Operator delete or destructor chaining
extern void __cdecl deleteObject(void* obj);

// Vtable symbols
extern void* PTR_FUN_00d64720; // Derived class vtable
extern void* PTR_LAB_00d64708; // Base class vtable

class EARSObject {
public:
    void* vtable;          // +0x00
    void* member1;         // +0x04 — pointer to sub-object
    // Possibly padding or other members at +0x08 and +0x0C
    void* member2;         // +0x10 — pointer to sub-object

    // Destructor
    // __thiscall implied; param_2 is deletion flag (bit0 = delete memory)
    EARSObject* __thiscall ~EARSObject(unsigned char deletionFlag) {
        // Set vtable to derived class vtable (own destructor step)
        this->vtable = &PTR_FUN_00d64720;

        // Release member at offset +0x10 (if non-zero)
        if (this->member2 != 0) {
            releaseSubObject(&this->member2);
        }

        // Release member at offset +0x04 (if non-zero)
        if (this->member1 != 0) {
            releaseSubObject(&this->member1);
        }

        // Set vtable to base class vtable (chaining to base destructor)
        this->vtable = &PTR_LAB_00d64708;

        // If deletion flag's lowest bit is set, deallocate the object
        if ((deletionFlag & 1) != 0) {
            deleteObject(this);
        }

        return this;
    }
};