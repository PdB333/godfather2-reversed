// FUNC_NAME: Entity::registerNetworkProperties
void __fastcall Entity::registerNetworkProperties(Entity* this)
{
    // +0x50, +0x54, +0x58, +0x5c, +0x60, +0x64 are member offsets being registered with the framework
    initializeBase(); // FUN_005c1740 - base initialization

    // Register property at +0x50 (read-only, no callback)
    registerProperty(g_propName1, &this->field_0x50, nullptr, 0, true);
    // Register property at +0x54 with a change callback
    registerProperty(g_propName2, &this->field_0x54, &Entity::onPropertyChanged, 0, false);
    // Register flags property at +0x58 (read-only)
    registerFlagsProperty(g_propName3, &this->field_0x58, nullptr, 0, true);
    // Register property at +0x60 (read-only)
    registerProperty(g_propName4, &this->field_0x60, nullptr, 0, true);
    // Register integer property at +0x64 (read-only)
    registerIntProperty(g_propName5, &this->field_0x64, nullptr, 0, true);
    // Register flags property at +0x5c (read-only)
    registerFlagsProperty(g_propName6, &this->field_0x5c, nullptr, 0, true);
}