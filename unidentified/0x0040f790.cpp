// Function address: 0x0040f790
// Role: Constructor/initializer for a game object with conditional sub-object initialization.
// Uses __thiscall convention; returns 'this' pointer (implicit in C++ constructors).
// The flag byte parameter controls whether to call a secondary initialization routine.

class GameObject {
public:
    // Constructor: performs base initialization and optionally a sub-object init.
    // param1: flag byte (bit 0 = invoke SubObjectInit)
    GameObject(uint8_t flags) {
        Construct(flags);
    }

private:
    // Internal construct logic
    void Construct(uint8_t flags) {
        BaseConstruct();      // 0x0040f7b0 - base class / core initialization
        if (flags & 1) {
            SubObjectInit(); // 0x009c8eb0 - conditional sub-object initialization
        }
    }

    void BaseConstruct();   // FUN_0040f7b0 - placeholder
    void SubObjectInit();   // FUN_009c8eb0 - placeholder
};