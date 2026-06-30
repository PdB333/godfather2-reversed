// FUNC_NAME: Entity::Entity
// Address: 0x005048a0
// Role: Constructor for the Entity class.
// Calls the base constructor (likely NetObject or SimObject) at 0x005048c0,
// then conditionally invokes a destruction/cleanup routine (0x009c8eb0) if
// the low bit of `initFlags` is set. This pattern is often used to support
// placement or conditional object creation.

class Entity {
public:
    // Constructs the Entity object.
    // @param initFlags - bitmask: if bit 0 is set, the object is immediately
    //                    destroyed after base construction (e.g., error cleanup).
    Entity(byte initFlags) {
        // Base class initialization (e.g., NetObject/SimObject constructor)
        FUN_005048c0(/*this* reverting*/ this);

        // If the flag requests destruction, clean up the object
        if (initFlags & 1) {
            FUN_009c8eb0(/*this*/ this);
        }
    }
};