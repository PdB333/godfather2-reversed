// FUN_004bace0: ScoreboardManager::ScoreboardManager
// Constructor for the ScoreboardManager class. Initializes vtable, zeros member fields,
// and registers pre/post scoreboard update message IDs with the engine's messaging system.

class ScoreboardManager {
public:
    void* vtable;                     // +0x00
    int field_04;                     // +0x04
    int field_08;                     // +0x08
    int field_0C;                     // +0x0C
    int field_10;                     // +0x10
    int field_14;                     // +0x14
    int field_18;                     // +0x18
    int field_1C;                     // +0x1C
    int field_20;                     // +0x20
    int field_24;                     // +0x24
};

// Global message ID storage (externally defined)
extern int g_PreScoreboardUpdateMsgID;   // &DAT_01218048
extern int g_PostScoreboardUpdateMsgID;  // &DAT_01218040

// External engine functions
int StringToID(const char* name);            // FUN_004dafd0 - hashes string to message ID
void RegisterMessage(int* storage, int id);  // FUN_00408260 - registers the ID into the global slot

__thiscall ScoreboardManager* ScoreboardManager::ScoreboardManager(ScoreboardManager* this) {
    // Set vtable pointer
    this->vtable = &PTR_FUN_00e35c20;   // vtable address in .rdata

    // Zero out all member fields (9 dwords from +0x04 to +0x24)
    this->field_04 = 0;
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;

    // Register pre-scoreboard update message
    int preMsgID = StringToID("iMsgPreScoreboardUpdate");
    RegisterMessage(&g_PreScoreboardUpdateMsgID, preMsgID);

    // Register post-scoreboard update message
    int postMsgID = StringToID("iMsgPostScoreboardUpdate");
    RegisterMessage(&g_PostScoreboardUpdateMsgID, postMsgID);

    return this;
}