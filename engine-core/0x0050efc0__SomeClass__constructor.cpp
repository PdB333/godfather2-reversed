// FUNC_NAME: SomeClass::constructor
// Function address: 0x0050efc0
// Role: Constructor with optional additional initialization based on a flag bit

class SomeClass {
public:
    // Constructor that returns 'this' (consistent with __thiscall)
    void* constructor(byte initFlag) {
        // Base class or member initialization
        baseInitialize();  // FUN_0050efe0

        // If the lowest bit of initFlag is set, perform extra setup
        if ((initFlag & 1) != 0) {
            extraInitialize(this);  // FUN_009c8eb0
        }

        return this;
    }

private:
    void baseInitialize();   // FUN_0050efe0
    void extraInitialize(void* obj);  // FUN_009c8eb0
};