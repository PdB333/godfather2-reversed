// FUNC_NAME: registerGameStateHandlers
// Address: 0x0091c860

// Helper functions – assumed from EARS event system
const char* getMessageString(int messageID);                          // FUN_00907680
EventManager* getEventManager(void* globalSingleton);                 // FUN_00916c70 – returns the event dispatcher from the global
void EventManager::registerMessages(const char** messages, int count, void (*handler)(void)); // FUN_00918b30 – register a batch of message handlers
void gameStateMessageHandler(void);                                   // FUN_0091aee0 – actual callback

// Global singleton for event management
extern void* g_EventManager; // DAT_00e54d0c

void registerGameStateHandlers(void) {
    // Retrieve string identifiers for each game state transition message
    const char* msgGameStart   = getMessageString(0);    // e.g., "GameStart"
    const char* msgGameEnd     = getMessageString(0x20); // e.g., "GameEnd"
    const char* msgLevelStart  = getMessageString(0x1d); // e.g., "LevelStart"
    const char* msgLevelEnd    = getMessageString(0x1e); // e.g., "LevelEnd"
    const char* msgCutscene    = getMessageString(0x1f); // e.g., "Cutscene"

    // Build array of messages to register
    const char* messages[5] = {
        msgGameStart,
        msgGameEnd,
        msgLevelStart,
        msgLevelEnd,
        msgCutscene
    };

    // Obtain the event manager singleton and register the handler for all five messages
    EventManager* eventMgr = getEventManager(g_EventManager);
    eventMgr->registerMessages(messages, 5, &gameStateMessageHandler);
}