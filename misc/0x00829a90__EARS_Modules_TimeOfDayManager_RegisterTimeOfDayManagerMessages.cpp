// Xbox PDB: EARS_Modules_TimeOfDayManager_RegisterTimeOfDayManagerMessages
// FUNC_NAME: registerGameTimeMessages
// Address: 0x00829a90
// Registers game time event messages for the message system.

#include <cstdint>

// Forward declaration or include for message registration function
// In EA EARS engine, likely a MessageSystem::registerMessage or similar
void registerMessage(uint32_t* messageId, const char* name);

// Global message ID variables (addresses from decompilation)
// +0x00: these are likely uint32_t values defined elsewhere
extern uint32_t gMsgGameTimeUpdated;      // DAT_0112db7c
extern uint32_t gMsgGameTimeMidnight;    // DAT_0112db6c
extern uint32_t gMsgGameTimeReset;       // DAT_0112db74
extern uint32_t gMsgGameTimeHourChanged; // DAT_0112db64

// Called during initialization to register game time messages
void registerGameTimeMessages()
{
    registerMessage(&gMsgGameTimeUpdated, "iMsgGameTimeUpdated");
    registerMessage(&gMsgGameTimeMidnight, "iMsgGameTimeMidnight");
    registerMessage(&gMsgGameTimeReset, "iMsgGameTimeReset");
    registerMessage(&gMsgGameTimeHourChanged, "iMsgGameTimeHourChanged");
}