// FUNC_NAME: Entity::Entity (constructor with allocation flag)
// Function address: 0x0094e6e0
// Constructs an Entity object. If param_2 bit 0 is set (allocated flag),
// calls the cleanup function (likely free/destroy) after base initialization.
// This pattern is typical for placement new where the flag indicates ownership.

class Entity {
public:
    // Constructor: initializes base class, then optionally cleans up if flag indicates allocation
    // +0x00: vtable pointer, etc.
    // param_2: bit 0 = 1 if object was allocated (e.g., from heap) and should be freed on exception
    void* __thiscall constructor(byte allocationFlag) {
        // Call base class initializer (likely sets up vtable, members)
        this->initializeBase(); // 0x0094e380

        // If the object was allocated (bit 0 set), call the cleanup/destroy function
        if ((allocationFlag & 1) != 0) {
            this->cleanup(); // 0x005c4480
        }

        return this;
    }

private:
    void initializeBase(); // 0x0094e380
    void cleanup();        // 0x005c4480
};