// FUNC_NAME: BaseGameObject::BaseGameObject
// Address: 0x006fab10
// Constructor: performs common initialization, then optionally custom setup if the low bit of the flag is set.

class BaseGameObject {
public:
    // Constructor with a boolean-like flag (bit 0 controls additional setup)
    BaseGameObject(uint8_t initFlags) {
        // Common initialization (e.g., base class constructor, engine-wide defaults)
        baseInitialize();

        // If flag bit 0 is non-zero, perform extra initialization
        if (initFlags & 1) {
            // Custom setup (e.g., allocate dynamic memory, register with manager)
            customInitialize(this);
        }
    }

private:
    // Internal common initializer (likely zeros fields, sets defaults)
    void baseInitialize();

    // Internal custom initializer (separate function, called with this pointer)
    friend void customInitialize(BaseGameObject* obj);
};