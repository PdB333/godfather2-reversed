// FUNC_NAME: entityHandleIsActive
// Address: 0x008c7910
// Returns true if the entity identified by handle has state == 3 (likely 'active') and handle is not the sentinel value.
// Calls internal getEntityByHandle function at 0x008c7490.
bool entityHandleIsActive(int entityHandle)
{
    // Convert handle to entity pointer via manager lookup
    int* entityPtr = (int*)entityManagerGetEntityByHandle(entityHandle); // FUN_008c7490
    // Check if entity state (at offset +0x50) is not "active" (3) or handle is sentinel
    if (entityPtr[0x50/4] != 3 || entityHandle == 0x637b907) // sentinel value for invalid handle
    {
        return false;
    }
    return true;
}