// FUNC_NAME: CommandHandler::handleCommand
void CommandHandler::handleCommand(uint32 param1, uint32 param2, uint32 entityID, uint32 param4, uint32 param5, uint32* commandData)
{
    // local_58 holds pointer to entity object (or null)
    void* entityObject = nullptr;

    // If an entity ID is provided, look it up via getObjectFromId (FUN_0040add0)
    if (entityID != 0) {
        entityObject = (void*)getObjectFromId(entityID);
        if (entityObject != nullptr) {
            // Check if entity has the "locked" flag (bit 1 at offset +0xAC)
            if ((*(uint8*)((uint32)entityObject + 0xAC) & 2) != 0) {
                return; // Entity is busy/locked, ignore command
            }
        }
    }

    // Get current tick count (twice actually; second two calls may be different values)
    uint32 currentTick = getTickCount();           // iVar1
    uint32 tick2 = getTickCount();                 // uVar2
    uint32 tick3 = getTickCount();                 // uVar3

    if (currentTick != 0) {
        // Copy command data (16 uint32 = 64 bytes) into local buffer
        uint32 localBuffer[16];
        for (int i = 0; i < 16; ++i) {
            localBuffer[i] = commandData[i];
        }

        // Dispatch the command via command manager with all parameters
        dispatchCommand(g_pCommandManager, currentTick, tick2, tick3, localBuffer,
                        param2, entityObject, param4, param5);
    }
}