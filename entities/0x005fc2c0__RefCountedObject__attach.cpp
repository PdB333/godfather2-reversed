// FUNC_NAME: RefCountedObject::attach
// Function address: 0x005fc2c0
// Role: Attaches a reference to another object, managing internal pointer and handle.

class RefCountedObject {
public:
    // Virtual function table offsets (assumed):
    // vtable[0] = destructor
    // vtable[1] = someFunc1(void* param, int flag) // offset 4
    // vtable[2] = getInternalPtr() // offset 8, returns int*
    // vtable[3] = someFunc3() // offset 0xc

    virtual int* getInternalPtr();          // offset 8
    virtual void someFunc1(void* obj, int flag); // offset 4
    virtual void someFunc3();               // offset 0xc
};

// External functions from the engine
int duplicateHandle(void* obj, void* context); // FUN_004265d0
void releaseHandle(void* context, int handle); // FUN_005fc510

void __thiscall RefCountedObject::attach(void* param_2) {
    // Get internal pointer from this object (virtual call at vtable[2])
    int* internalObj = this->getInternalPtr();

    // Obtain a handle for param_2 (or zero if null)
    int handle;
    if (param_2 == 0) {
        handle = 0;
    } else {
        handle = duplicateHandle(param_2, this);
    }

    // Release previous handle and store new one
    releaseHandle(this, handle);

    // Set internal object's field at +0x8 to point back to this
    internalObj[2] = (int)this; // +0x8

    // Notify this object that attachment occurred (second call to vtable[2]? Possibly a different virtual)
    this->getInternalPtr(); // Note: This second call may be a different virtual at same offset; kept as per decompilation

    if (param_2 != 0) {
        // Obtain another handle using the internal object's stored pointer
        handle = duplicateHandle(param_2, (void*)internalObj[2]); // internalObj[2] is this
        internalObj[3] = handle; // +0xc

        // Call virtual at offset 4 with param_2 and flag 0
        this->someFunc1(param_2, 0);

        // Finalize with virtual at offset 0xc
        this->someFunc3();
        return;
    }

    // If param_2 is null, clear the handle and finalize
    internalObj[3] = 0;
    this->someFunc3();
}