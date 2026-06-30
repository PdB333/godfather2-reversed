// FUNC_NAME: Player::checkInteractionPermission
// Address: 0x0074fe60
// This function checks if the player is allowed to interact with a target entity.
// It uses a permission system via virtual calls on the entity's container object.
// Parameters: this (player), edxParam (target), stackParam1 (context1), stackParam2 (context2)
uint __fastcall Player::checkInteractionPermission(void* this, int target, int context1, int context2)
{
    // Get pointer to entity manager from player +0x110, then read a member at +0x24cc
    uint entityPtr = *(uint*)(*(int*)((char*)this + 0x110) + 0x24cc);
    if (entityPtr == 0) {
        return 0;
    }

    // Convert entityPtr to a container object by subtracting 0x48 (presumably offset of a member)
    int* container = (int*)(entityPtr - 0x48);
    if (container != (int*)0x0) {
        // Call virtual function at vtable offset 0x10 (index 4) with a magic value
        char permissionCheck1 = (**(char(__thiscall**)(int))(*(int*)container + 0x10))(0x55859efa);
        if ((permissionCheck1 != '\0') && (target != 0)) {
            // Compare target entity's container with this player's container
            uint targetContainerId = (*(int*)(target + 0x1c78) == 0) ? 0 : *(int*)(target + 0x1c78) - 0x48;
            uint playerContainerId = (*(int*)((char*)this + 0x48) == 0) ? 0 : *(int*)((char*)this + 0x48) - 0x48;
            if (targetContainerId == playerContainerId) {
                goto permissionGranted;
            }
        }

        // Call the same virtual function with another magic value and a stack parameter
        char permissionCheck2 = (**(char(__thiscall**)(int,void*))(*(int*)container + 0x10))(0x383225a1, &stack0xfffffff4);
        if ((permissionCheck2 != '\0') && (&stack0x00000000 != &DAT_00000004)) // This condition is suspicious, likely a decompiler artifact
        {
            // Compare context1's container with player's container
            uint context1ContainerId = (context1 == 0) ? 0 : context1 - 0x48;
            uint playerContainerId = (*(int*)((char*)this + 0x48) == 0) ? 0 : *(int*)((char*)this + 0x48) - 0x48;
            if (context1ContainerId != playerContainerId) {
                // Compare context2's container with player's container
                uint context2ContainerId = (context2 == 0) ? 0 : context2 - 0x48;
                uint playerContainerId2 = (*(int*)((char*)this + 0x48) == 0) ? 0 : *(int*)((char*)this + 0x48) - 0x48;
                if (context2ContainerId != playerContainerId2) {
                    goto permissionDenied;
                }
            }
permissionGranted:
            // Return true (low byte = 1) plus high bits from entityPtr
            return (entityPtr & 0xFFFFFF00) | 0x1;
        }
    }
permissionDenied:
    return entityPtr & 0xFFFFFF00;
}