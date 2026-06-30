// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00750c60
// Role: Constructor with optional extra initialization based on flag

class BaseClass {
public:
    __thiscall BaseClass();
};

class SomeClass : public BaseClass {
private:
    // Additional initialization function, called conditionally
    __thiscall void performExtraInit();

public:
    // Constructor - takes an initialization flag (byte, checks LSB)
    // If (initFlag & 1) is true, extra setup is performed
    __thiscall SomeClass(byte initFlag) : BaseClass() {
        if (initFlag & 1) {
            // E.g., allocate resources, register with manager, etc.
            performExtraInit();
        }
    }
};