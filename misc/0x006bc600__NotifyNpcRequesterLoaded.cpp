// FUNC_NAME: NotifyNpcRequesterLoaded
void NotifyNpcRequesterLoaded(void)
{
    // Send a notification message indicating the NPC requester has finished loading.
    // The message string "iMsgNpcRequesterLoaded" is used for event dispatch.
    sendNotification(g_pMsgManager, "iMsgNpcRequesterLoaded");
    return;
}