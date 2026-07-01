// FUNC_NAME: SomeClass::SomeClass
// Reconstructed constructor for a class in the EA EARS engine.
// Calls base initializer unconditionally, then conditionally calls a heavy initializer based on a flag.
class SomeClass {
public:
    // Constructor at 0x008d3b80
    // @param createFlags: bit 0 triggers heavyInit (e.g., full initialization vs. lightweight reuse)
    SomeClass(byte createFlags) {
        // Base class/component init (likely sets up vtable and base members)
        baseInit(); // FUN_008d3b10

        // Optional additional initialization (e.g., allocate resources, register with manager)
        if (createFlags & 1) {
            heavyInit(); // FUN_009c8eb0
        }
    }

private:
    // Internal initializer – base construction
    void baseInit(); // Address 0x008d3b10

    // Heavy initialization – may set up derived or extended state
    void heavyInit(); // Address 0x009c8eb0
};