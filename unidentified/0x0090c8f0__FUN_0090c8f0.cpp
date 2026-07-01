// FUNC_NAME: UnknownClass::constructor (zeros 7 fields then calls init func)
// Address: 0x0090c8f0
// Role: Initializes a small structure (7 ints) and delegates further initialization to FUN_0090c800 with three parameters.

class UnknownClass {
public:
    // Fields: 7 ints (28 bytes)
    int field0;   // +0x00
    int field4;   // +0x04
    int field8;   // +0x08
    int field12;  // +0x0C
    int field16;  // +0x10
    int field20;  // +0x14
    int field24;  // +0x18

    // Constructor: zeros all fields, then calls an internal init function
    // __thiscall
    UnknownClass* __thiscall constructor(int param_2, int param_3, int param_4) {
        field0 = 0;
        field4 = 0;
        field8 = 0;
        field12 = 0;
        field16 = 0;
        field20 = 0;
        field24 = 0;
        // Call to another initialization function (likely sets up more complex state)
        FUN_0090c800(param_2, param_3, param_4);
        return this;
    }

private:
    void FUN_0090c800(int, int, int); // Internal initializer, not reconstructed
};