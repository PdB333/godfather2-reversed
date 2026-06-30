// FUNC_NAME: Entity::setActiveFlag
// Address: 0x006bc3b0
void __thiscall Entity::setActiveFlag(int actionIn, char setHighBit)
{
    // Check if the object's flags at +0x180 indicate it's not in a terminal state (bit 31 cleared)
    if (*(int*)(this + 0x180) >= 0) {
        // If we have a component pointer at +0x130
        if (*(int**)(this + 0x130) != nullptr) {
            // Normalize action: map 2 -> 1 (probably treating 2 as a boolean true)
            int action = actionIn;
            if (action == 2) {
                action = 1;
            }
            // Call the component's vtable function at offset 0x44
            // The constant 0xf86f4484 is likely a command identifier (e.g., "setActive")
            // Signature: void (__thiscall*)(int commandId, int action)
            (*(void (__thiscall**)(int, int))(**(int**)(this + 0x130) + 0x44))(0xf86f4484, action);
        }
        if (setHighBit != '\0') {
            // Set bit 31 of the flags at +0x180 (marks object as active/high state)
            *(uint*)(this + 0x180) |= 0x80000000;
        } else {
            // Clear bit 31
            *(uint*)(this + 0x180) &= 0x7fffffff;
        }
    }
}