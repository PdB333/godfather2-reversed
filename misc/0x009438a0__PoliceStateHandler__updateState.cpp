// FUNC_NAME: PoliceStateHandler::updateState
// Address: 0x009438a0
// Role: Updates the police chase state for a handler object, notifying script system if changed.

// Assuming class PoliceStateHandler with member at offset +0xb4 (m_policeChaseState)
// Global g_pGameState at DAT_0112af68 with member at +0x174 (m_gameMode or similar)

// Forward declarations (unknown prototypes)
int getPoliceChaseState(); // from 0x008fb420
void setScriptGlobal(const char* key, int type, void* data, int count, const char* value); // from 0x005a04a0

void __thiscall PoliceStateHandler::updateState(void) {
    int iVar1;
    char local_10[16];

    // Determine if police chase state is valid based on global game state
    if ((g_pGameState == nullptr) || (*(int*)(g_pGameState + 0x174) != 2)) {
        iVar1 = 0;
    } else {
        iVar1 = getPoliceChaseState();
    }

    // Only update if the state actually changed
    if (iVar1 != *(int*)(this + 0xb4)) {
        *(int*)(this + 0xb4) = iVar1;
        __snprintf(local_10, 0x10, "%d", iVar1);
        setScriptGlobal("SetPoliceChaseState", 0, &DAT_00d8b2cc, 1, local_10);
    }
    return;
}