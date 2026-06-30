// FUNC_NAME: Entity::handleDeactivation

#define DEACTIVATE_MSG 0x55859efa
#define ACTIVE_FLAG_BIT 0x40

void __thiscall Entity::handleDeactivation(Entity* thisPtr, int* componentPtr)
{
    int* componentBaseVtable;
    if (componentPtr != 0) {
        // componentPtr points into a derived class member; subtract 0x58 to reach base object vtable
        componentBaseVtable = (int*)((uint)componentPtr - 0x58);
    } else {
        componentBaseVtable = 0;
    }

    int resultCode = 0;
    // Check if the component can process the deactivation message (vtable+0x10)
    char handled = ((char (*)(int, int*))(*componentBaseVtable + 0x10))(DEACTIVATE_MSG, &resultCode);

    // Clear the active flag (bit 6) in the entity's state field at +0x1d0
    thisPtr->stateFlags &= ~ACTIVE_FLAG_BIT;

    // If the component handled the message, call the deactivation callback (vtable+0x248) on this entity
    if (handled) {
        void (*onDeactivationCallback)(Entity*) = (void (*)(Entity*))(*(*(void***)thisPtr + 0x248));
        onDeactivationCallback(thisPtr);
    }
}