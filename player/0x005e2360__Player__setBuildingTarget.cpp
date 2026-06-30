// FUNC_NAME: Player::setBuildingTarget
bool Player::setBuildingTarget(uint value)
{
    // Check if building targeting is allowed (flag at +0x1744)
    if (*(byte *)(this + 0x1744) != 0)
    {
        // Get a component (likely BuildingManager or similar)
        int *pComponent = (int *)FUN_005e2150();
        if (pComponent != (int *)0x0)
        {
            // Store the target value into component's field at +0x24c
            pComponent[0x24c / 4] = value;
            return true;
        }
    }
    return false;
}