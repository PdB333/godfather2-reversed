// FUNC_NAME: InputManager::shutdownControllerSlots
void InputManager::shutdownControllerSlots(void)
{
    // Shutdown each controller slot by calling the cleanup function
    // DAT_0112e104 through DAT_0112e134 are likely controller slot objects (0x44 bytes each)
    // The addresses are spaced 0x10 apart, suggesting an array of 16 controller slots
    FUN_00408310(&DAT_0112e104); // Slot 0
    FUN_00408310(&DAT_0112e0f4); // Slot 1
    FUN_00408310(&DAT_0112e054); // Slot 2
    FUN_00408310(&DAT_0112e04c); // Slot 3
    FUN_00408310(&DAT_0112e124); // Slot 4
    FUN_00408310(&DAT_0112e028); // Slot 5
    FUN_00408310(&DAT_0112e12c); // Slot 6
    FUN_00408310(&DAT_0112e13c); // Slot 7
    FUN_00408310(&DAT_0112e05c); // Slot 8
    FUN_00408310(&DAT_0112e030); // Slot 9
    FUN_00408310(&DAT_0112e11c); // Slot 10
    FUN_00408310(&DAT_0112e018); // Slot 11
    FUN_00408310(&DAT_0112e038); // Slot 12
    FUN_00408310(&DAT_0112e064); // Slot 13
    FUN_00408310(&DAT_0112e040); // Slot 14
    FUN_00408310(&DAT_0112e10c); // Slot 15
    FUN_00408310(&DAT_0112e06c); // Slot 16 (extra? or misaligned)
    FUN_00408310(&DAT_0112e134); // Slot 17 (extra? or misaligned)
}