// FUNC_NAME: Entity::ctorWithFlag
// Function address: 0x006f5570
// Role: Constructor with a boolean flag for additional initialization

class Entity {
public:
    // This is a __thiscall method.
    // param_2: flag where bit 0 indicates whether to call extra init (FUN_009c8eb0)
    Entity* ctorWithFlag(byte param_2) {
        // Call base constructor or common initialization routine
        this->commonInit();  // likely calls FUN_006f54e0

        // If flag's lowest bit is set, perform additional initialization
        if ((param_2 & 1) != 0) {
            this->conditionalInit();  // calls FUN_009c8eb0, unknown purpose
        }

        return this;
    }

    // Stub for the called functions – real implementation is at the given addresses
    void commonInit() {
        // Implementation at 0x006f54e0
    }

    void conditionalInit() {
        // Implementation at 0x009c8eb0
    }
};