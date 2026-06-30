// FUNC_NAME: registerThrowableItemMessages

// Global string pointers for throwable item message names
// (defined elsewhere, perhaps in a string table)
extern char *msgThrowableItemLifeOver;      // actually &DAT_0112ac6c
extern char *msgReportCSAStatus;             // &DAT_0112ac5c
extern char *msgThrowableSettled;            // &DAT_0112ac64
extern char *msgThrowableItemCSAShouldDestroy; // &DAT_0112abd8
extern char *msgInternalThrowableAIPeriodicBroadcast; // &DAT_0112ac74

// Forward declaration of the message registration helper
// Likely stores the string address into the global pointer
void registerGameMessage(char **outStr, const char *msgName);

void registerThrowableItemMessages(void)
{
    registerGameMessage(&msgThrowableItemLifeOver, "iMsgThrowableItemLifeOver");
    registerGameMessage(&msgReportCSAStatus, "iMsgReportCSAStatus");
    registerGameMessage(&msgThrowableSettled, "iMsgThrowableSettled");
    registerGameMessage(&msgThrowableItemCSAShouldDestroy, "iMsgThrowableItemCSAShouldDestroy");
    registerGameMessage(&msgInternalThrowableAIPeriodicBroadcast, "iMsgInternalThrowableAIPeriodicBroadcast");
    return;
}