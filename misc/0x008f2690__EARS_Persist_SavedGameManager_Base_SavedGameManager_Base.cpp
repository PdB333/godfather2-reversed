// Xbox PDB: EARS_Persist_SavedGameManager_Base_SavedGameManager_Base
// FUNC_NAME: GamePersistenceManager::Constructor
// Function address: 0x008f2690
// Role: Game persistence manager constructor – initializes fields and subscribes
// to engine messages for save/load game lifecycle events.

class GamePersistenceManager {
public:
    // Vtable pointer at +0x00
    // +0x04: int member1 (set to 1)
    // +0x08: int member2 (set to 0)
    // +0x0C: pointer member3 (set to 0)
    // +0x10: pointer member4 (set to 0)
    // +0x14: pointer to some message registry
    // +0x1C: pointer (set to 0)
    // +0x20: pointer (set to 0)
    // +0x24: pointer (set to 0)
    // +0x28: int m_state (initialized with param2)
    // +0x2C: int (set to 0)
    // +0x30: int (set to 0)
    // +0x34: int (set to 0)
    // ... (large gap, up to +0x2050)
    // +0x2050: char m_lastSaveFilePath[64] // +0x814*4 = 0x2050, 0x40 bytes
    // +0x208F: null terminator for above
};

GamePersistenceManager* __thiscall GamePersistenceManager::Constructor(GamePersistenceManager* this, int arg2) {
    messageId_t msgId;

    // Initialize vtable pointer
    *(void**)this = &PTR_FUN_00d81038;  // VTable for GamePersistenceManager

    this->member1 = 1;
    this->member2 = 0;
    this->member3 = 0;      // +0x0C
    this->member4 = 0;      // +0x10
    this->messageRegistry = GetMessageRegistry();  // FUN_00494d10() – obtains shared message registry

    // Clear various pointers
    this->somePtr1 = 0;     // +0x1C
    this->somePtr2 = 0;     // +0x20
    this->somePtr3 = 0;     // +0x24
    this->state = arg2;     // +0x28
    this->someInt1 = 0;     // +0x2C
    this->someInt2 = 0;     // +0x30
    this->someInt3 = 0;     // +0x34

    // Perform general persistence initialization
    InitPersistenceSystem(); // FUN_008f2600()

    // Clear save file path
    this->m_lastSaveFilePath[0] = 0;   // +0x2050
    _strncpy(this->m_lastSaveFilePath, "", 0x3F); // ensure null termination
    this->m_lastSaveFilePath[63] = 0;  // +0x208F

    // Look up message IDs for persistence events and subscribe to them
    // Note: these static global variables hold the message IDs (or handle to them)
    RegisterPersistenceMessages(); // FUN_00408240 is actually retrieving/registering message IDs
    sMsgGamePersistenceNewGame = GetMessageID("iMsgGamePersistenceNewGame");      // FUN_00408240(&DAT_0112fe10, ...)
    sMsgGamePersistenceRestored = GetMessageID("iMsgGamePersistenceRestored");    // DAT_0112fe38
    sMsgGamePersistenceSaved = GetMessageID("iMsgGamePersistenceSaved");          // DAT_0112fe20
    sMsgGamePersistenceLoaded = GetMessageID("iMsgGamePersistenceLoaded");        // DAT_0112fe30
    sMsgManualSaveDisable = GetMessageID("iMsgManualSaveDisable");                // DAT_0112fe40
    sMsgManualSaveEnable = GetMessageID("iMsgManualSaveEnable");                  // DAT_0112fe48
    sMsgFrontendRestoreDone = GetMessageID("iMsgFrontendRestoreDone");            // DAT_0112fe28
    sMsgInGameRestoreDone = GetMessageID("iMsgInGameRestoreDone");                // DAT_0112fe18

    // Subscribe to manual save messages and any additional messages
    if (sMsgManualSaveDisable != 0) {
        SubscribeToMessage(this, sMsgManualSaveDisable, 0x8000); // FUN_00408900
    }
    if (sMsgManualSaveEnable != 0) {
        SubscribeToMessage(this, sMsgManualSaveEnable, 0x8000);
    }
    if (sMsgSomeOther1 != 0) {    // DAT_01206a20 – likely additional message for persistence
        SubscribeToMessage(this, sMsgSomeOther1, 0x8000);
    }
    if (sMsgSomeOther2 != 0) {    // DAT_01206940
        SubscribeToMessage(this, sMsgSomeOther2, 0x8000);
    }

    return this;
}