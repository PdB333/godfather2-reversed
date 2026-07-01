// FUNC_NAME: registerDestructibleMessages
void registerDestructibleMessages(void)
{
    // Register inter-module messages for destructible objects
    registerMessage(&g_msgFadeOutDestructible, "iMsgFadeOutDestructible");      // Message to fade out a destructible
    registerMessage(&g_msgBroadcastDestructibleDanger, "iMsgBroadcastDestructibleDanger"); // Broadcast danger from destructible
    return;
}