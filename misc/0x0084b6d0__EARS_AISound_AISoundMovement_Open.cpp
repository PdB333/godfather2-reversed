// Xbox PDB: EARS_AISound_AISoundMovement_Open
// FUNC_NAME: registerAISoundMovementMessage
void registerAISoundMovementMessage(void)
{
    // Register the AI sound movement message type with the global manager.
    // FUN_00408240 is likely MessageManager::registerMessage(manager, string)
    registerMessageType(&gAISoundMovementManager, "iMsgAISoundMovement");
    return;
}