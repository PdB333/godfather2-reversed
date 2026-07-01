// FUNC_NAME: GameObject::GameObject
// Address: 0x009867e0
// Role: Constructor for a basic game object with allocation flag.
// The byte parameter (flag) indicates whether the object is heap-allocated.
// If bit 0 is set, additional initialization is performed via HeapInit().
// This function calls the base initialization function BaseInit() (FUN_00986490)
// then conditionally calls HeapInit() (FUN_005c4480).

class GameObject {
public:
    // Constructor: takes an allocation flag
    __thiscall GameObject(byte flag) {
        // Call base initialization (FUN_00986490)
        BaseInit();

        // If flag indicates heap allocation, perform additional setup
        if (flag & 1) {
            // Setup for heap-allocated objects (FUN_005c4480)
            HeapInit();
        }
    }

private:
    // Base initialization (FUN_00986490)
    void BaseInit() {
        // Implementation not shown; likely initializes basic members and vtable
    }

    // Additional heap allocation setup (FUN_005c4480)
    void HeapInit() {
        // Implementation not shown; likely sets memory tracking or registers with manager
    }
};