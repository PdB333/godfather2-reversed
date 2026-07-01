// FUNC_NAME: Player::initDebugVariables
void __fastcall Player::initDebugVariables(int thisObj)
{
    // Call base initialization (likely sets defaults or clears data)
    FUN_005c1740();

    // Register first debug variable at offset +0x50 (e.g., m_fSpeedMultiplier or m_bDebugMode)
    FUN_005c01d0(&DAT_00d92144, thisObj + 0x50, 1, 0, 0, 1);

    // Register second debug variable at offset +0x58 (e.g., m_fHealthOverride)
    FUN_005c01d0(&DAT_00e40ec8, thisObj + 0x58, 1, 0, 0, 1);
}