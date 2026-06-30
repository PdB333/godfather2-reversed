// FUNC_NAME: Player::CanInteract
bool __thiscall Player::CanInteract(unsigned int targetEntity)
{
    // param_1 (this) is the Player object
    // Offset +0x18: pointer to an extended data block (likely PlayerData)
    int playerData = *(int*)(this + 0x18);

    // Check state at playerData+0x1b8c
    // States 2 and 3 are blocking conditions (e.g., dead, busy)
    unsigned char state = *(unsigned char*)(playerData + 0x1b8c);
    if (state == 2 || state == 3)
        return false;

    // offset +0x2004: pointer to current interactive object or vehicle
    int interactiveObj = *(int*)(playerData + 0x2004);
    if (interactiveObj == 0 || interactiveObj == 0x48) // 0x48 might be an invalid/empty handle
        return false;

    // offset +0xcc in interactive object: cooldown or timer
    // offset +0x2128 in playerData: required cooldown
    unsigned int objCooldown = *(unsigned int*)(interactiveObj + 0xcc);
    unsigned int requiredCooldown = *(unsigned int*)(playerData + 0x2128);
    if (objCooldown != 0 && objCooldown > requiredCooldown)
        return false;

    // Compute squared distance between targetEntity and something (likely player position)
    float sqDist = GetSquaredDistance(targetEntity); // FUN_007228c0
    // offset +0x364: squared interaction range threshold
    float interactionRange = *(float*)(this + 0x364);
    if (sqDist < interactionRange)
        return false;

    return true;
}