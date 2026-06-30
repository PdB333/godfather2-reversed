// FUNC_NAME: GameObject::GameObject
// Address: 0x00420d20
// This constructor performs basic initialization (via initFields) and optionally
// registers the instance with a global manager (via registerWithManager) if
// the low bit of flags is set. The manager is likely responsible for tracking
// active objects (e.g., for memory management or update scheduling).

class GameObject {
public:
    // Constructor: allocates/initializes object and conditionally registers it.
    // Flags bit 0: if set, call registerWithManager after init.
    __thiscall GameObject(byte flags) {
        // Call internal initialization routine (sets vtable, zeroes fields, etc.)
        initFields();                            // FUN_00420d50

        // Check if we need to register with the component/object manager.
        if (flags & 1) {
            registerWithManager();               // FUN_009c8eb0
        }
        // Return 'this' (implicitly, as per __thiscall convention).
    }

private:
    // Initializes all member fields to defaults.
    // (No offsets shown – typical layout: vtable at +0x00, then data members.)
    void initFields();                           // FUN_00420d50

    // Registers this object with the global manager (e.g., adds to a linked list).
    void registerWithManager();                  // FUN_009c8eb0
};