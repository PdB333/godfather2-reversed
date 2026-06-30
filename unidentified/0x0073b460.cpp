// FUN_0073b460: Entity::getHandleIfValid
// Function address: 0x0073b460
// Checks if the entity's state field (+0x78) is non-zero and not equal to 0x48 (likely a "dead" or "inactive" state).
// If valid, queries a global manager (DAT_0112af98) for an associated handle; otherwise returns 0.

int __thiscall Entity::getHandleIfValid(void)
{
    // this + 0x78 is the state/status field
    if ( *(int *)(this + 0x78) != 0 && *(int *)(this + 0x78) != 0x48 ) {
        // FUN_0043b870 likely retrieves a handle or resource from a global manager
        return FUN_0043b870(DAT_0112af98);
    }
    return 0;
}