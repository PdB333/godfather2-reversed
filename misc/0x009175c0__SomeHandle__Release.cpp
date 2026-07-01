// FUNC_NAME: SomeHandle::Release
// Address: 0x009175c0
// Likely a handle/reference release function. Clears internal pointer after calling a deallocation function.

class SomeHandle {
public:
    // Structure offsets:
    // +0x00: pointer to resource (void*)
    // +0x04: field1 (int, set to 0)
    // +0x08: field2 (int, set to 0)
    void* resourcePtr;    // +0x00
    int field1;           // +0x04
    int field2;           // +0x08

    // Destructor / release method
    void __thiscall Release(void) {
        field1 = 0;
        // Call deallocation function on the resource pointer
        FUN_009c8f10(resourcePtr);
        resourcePtr = 0;
        field2 = 0;
    }
};