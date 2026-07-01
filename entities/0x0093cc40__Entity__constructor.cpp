// FUNC_NAME: Entity::constructor
// Address: 0x0093cc40
// Role: Constructor that performs base initialization and optionally calls cleanup based on a flag

int __thiscall Entity::constructor(int thisPtr, byte flags)
{
    // Call base class initialization (FUN_0093bd90)
    Entity::baseInit();

    // If the least significant bit of flags is set, call cleanup (FUN_005c4480)
    // This pattern may be used for reinitialization after destruction or for conditional behavior
    if (flags & 1) {
        Entity::cleanup(thisPtr);
    }

    return thisPtr;
}