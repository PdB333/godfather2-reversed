// FUNC_NAME: Entity::isEnabled
// Function address: 0x008deda0
// Checks if this entity is enabled (not disabled) and passes additional validity check
// Offset 0x161: m_bDisabled (byte, 1 = disabled, 0 = enabled)
bool Entity::isEnabled()
{
    // Early out if null or disabled
    if (this == nullptr || *(char*)(this + 0x161) != '\0')
        return false;

    // Call internal check (likely more specific validity/compatibility)
    return FUN_008dae50(this) != 0;
}