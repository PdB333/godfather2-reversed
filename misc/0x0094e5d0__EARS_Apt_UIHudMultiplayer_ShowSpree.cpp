// Xbox PDB: EARS_Apt_UIHudMultiplayer_ShowSpree
// FUNC_NAME: SpreeManager::displaySpreeMessage
#include <cstddef>

// External engine functions
void formatStringIntoBuffer(char* dest, const char* format, int maxLen, int value);
void sendUIEvent(const char* eventName, int param1, int param2, int param3);
void startStateMachine(void* stateMachineAddr, void* stateFunction, int initialState);

class SpreeManager {
public:
    // Offsets:
    // +0x10: stateMachine (void*)
    // +0x6c: spreeCounter (int)
    // +0x70: messageBufferPtr (char*)

    void displaySpreeMessage(const char* formatString, int value) {
        const char* format = (formatString != nullptr) ? formatString : (const char*)0x0120546e;
        formatStringIntoBuffer(*(char**)((char*)this + 0x70), format, 0x80, value);
        sendUIEvent("UpdateMessage", 0, 0x00d8b7d4, 0);
        *(int*)((char*)this + 0x6c) = 0;
        sendUIEvent("ShowSpree", 0, 0x00d8b7d4, 0);
        startStateMachine((char*)this + 0x10, (void*)0x0094e340, 1);
    }
};