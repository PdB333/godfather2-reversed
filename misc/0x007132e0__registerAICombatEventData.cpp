// FUNC_NAME: registerAICombatEventData
// Function address: 0x007132e0
// Role: Registers AICombatEventData class with the engine's type/reflection system.
// Calls a registration function (FUN_00408240) with a pointer to the type info table and the class name string.
// Likely invoked during static initialization or engine startup.

void registerAICombatEventData(void)
{
    // FUN_00408240 is likely registerType or registerClassInfo, takes a pointer to a global type table
    // and a string identifier for the class.
    FUN_00408240(&DAT_0112ac90, "AICombatEventData*");
    return;
}