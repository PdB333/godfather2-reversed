// FUNC_NAME: sendNpcRequesterLoadedMessage
void sendNpcRequesterLoadedMessage(void)
{
    // Post the "iMsgNpcRequesterLoaded" message to the global message manager (DAT_0112a6ac)
    FUN_00408240(&DAT_0112a6ac, "iMsgNpcRequesterLoaded");
    return;
}