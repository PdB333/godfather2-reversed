// FUNC_NAME: SomeClass::constructor
// Address: 0x008f71b0
// This function appears to be a constructor for a class that calls a base initializer (FUN_008f7050)
// and conditionally calls a destructor-like function (FUN_009c8eb0) if param_2 bit 0 is set.
// param_1 is the implicit 'this' pointer, param_2 is a byte flag.
// Returns 'this' (param_1).

class SomeClass {
public:
    // Assumed constructor: initializes base and maybe handles a conditional cleanup.
    __thiscall SomeClass* constructor(byte flag) {
        // Call base class or member initialization (FUN_008f7050)
        this->baseInit();  // Placeholder for FUN_008f7050

        // If flag bit 0 is set, call destructor-like function (FUN_009c8eb0)
        if ((flag & 1) != 0) {
            this->cleanup();  // Placeholder for FUN_009c8eb0
        }

        return this;
    }

private:
    void baseInit();   // Actually FUN_008f7050 - likely initializes base members.
    void cleanup();    // Actually FUN_009c8eb0 - likely frees resources or performs destruction.
};