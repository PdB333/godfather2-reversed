// FUNC_NAME: PowerManager::updatePlayerPower

#include <cstdint>

// Globals (likely timing/state variables)
static int32_t g_GlobalTimer1 = 0;           // DAT_012058d0
static int32_t g_GlobalTimer2 = 0;           // DAT_00f15988
static int32_t g_GlobalStateFlags1 = 0;      // _DAT_011f3a34
static int32_t g_GlobalTimer3 = 0;           // DAT_012058d4
static int32_t g_GlobalTimer4 = 0;           // DAT_00f1598c
static int32_t g_GlobalStateFlags2 = 0;      // _DAT_011f3c78
static int32_t g_GlobalStateFlags3 = 0;      // _DAT_011f3cd0
static int32_t g_GlobalStateFlags4 = 0;      // _DAT_011f39f4
static int32_t g_GlobalStateFlags5 = 0;      // _DAT_011f3a30

// Forward declarations for helper functions
int32_t calculateDistance(uint8_t* a, uint8_t* b, int32_t mode);  // FUN_0042cd20
int32_t getPlayerTeam(int32_t playerIndex);                       // FUN_00417920
void resetPower(void* thisPtr);                                   // FUN_0042af40
void freeObject(void* obj);                                       // FUN_00412f90
void applyPowerEffect(void* powerObj, int32_t playerIndex);       // FUN_0042ad90
void syncWithServer();                                            // FUN_00619210
void playSound(int32_t soundId);                                  // FUN_0060a460 (param: unaff_ESI[1]+0x14)

class PowerManager {
public:
    // Vtable offsets (assuming standard layout)
    virtual bool isPowerActive();       // vtable+0x44 (cVar2)
    virtual void onActivate();          // vtable+0x20
    virtual void onUpdate();            // vtable+0x2c
    virtual void onDeactivate();        // vtable+0x30
    virtual void onSpecialAction();     // vtable+0x34

    // Main update function (__thiscall)
    void updatePlayerPower(void* playerObject, uint32_t param2, uint32_t param3, char forceFlag) {
        // +0x00: vtable pointer
        // +0x04: some data (playerObject+4 used)
        // +0x14: some data (playerObject+0x14 used)
        // +0x24: timer or counter
        // +0x28, +0x38: coordinates for distance
        // +0x3af8: flags bitfield
        // +0x108c, +0x1090: objects to free

        bool forceActivate = false;
        uint8_t actionFlags = 0;

        // Check force flag or a specific condition (likely AI decision)
        if (forceFlag != 0) {
            forceActivate = true;
        } else {
            // Check a TLS-based condition (thread-specific state)
            int32_t* tlsPtr = *(int32_t**)(*(int32_t*)(__readfsdword(0x2c) + 8) + 0x7c + *(int32_t*)(playerIndex + 0x18));
            if ((*(uint8_t*)(tlsPtr) & 0x10) != 0) {
                forceActivate = true;
            } else {
                forceActivate = false;
            }
        }

        // Calculate some distance/size metric
        int32_t distanceResult = calculateDistance((uint8_t*)playerObject, (uint8_t*)playerObject + 4, (uint8_t*)playerObject + 0x14, 0);
        // Check if current value + distance exceeds threshold
        if (0x4ff < (uint32_t)(*(int32_t*)(playerObject + 0x24) + distanceResult)) {
            actionFlags |= 1; // bit0 set
        }

        // Player team check (1 = enemy team?)
        int32_t playerIndex = playerObject; // Actually in_EAX; assume player index passed in EAX
        int32_t teamId = getPlayerTeam(playerIndex);
        if (teamId == 1) {
            // Check if ability flags allow and distance > 0x30
            uint32_t abilityFlags = *(uint32_t*)(playerObject + 0x3af8);
            if (((abilityFlags >> 4) & 1) != 0 || calculateDistance(playerObject, playerObject + 0x28, playerObject + 0x38, 1) > 0x30) {
                actionFlags |= 4; // bit2 set
            }
        }

        teamId = getPlayerTeam(playerIndex);
        if (teamId == 0) {
            uint32_t abilityFlags = *(uint32_t*)(playerObject + 0x3af8);
            if (((abilityFlags >> 4) & 1) == 0 || calculateDistance(playerObject, playerObject + 0x28, playerObject + 0x38, 1) > 0x30) {
                actionFlags |= 2; // bit1 set
            }
        }

        // Check if power/weapon is currently active
        bool isActive = isPowerActive();

        if (!isActive) {
            if (forceActivate) {
                // Forced activation path
                onActivate();
                onUpdate();
                freeObject(*(void**)(playerObject + 0x1090));
                applyPowerEffect(this, playerIndex);
                if (someReturnFlag == 0) { // unaff_retaddr
                    setGlobalTimer(0x17);
                    setGlobalState1(4);
                    freeObject(*(void**)(playerObject + 0x108c));
                } else {
                    setGlobalTimer(0x17);
                    setGlobalState1(8);
                }
                // Set additional timers and state
                if (g_GlobalTimer3 < 0xa8) g_GlobalTimer3 = 0xa8;
                if (g_GlobalTimer4 < 0xa8) g_GlobalTimer4 = 0xa8; // actually inverse check?
                g_GlobalStateFlags2 = 0xf;
                if (g_GlobalTimer3 < 0xbe) g_GlobalTimer3 = 0xbe;
                if (g_GlobalTimer4 < 0xbe) g_GlobalTimer4 = 0xbe;
                g_GlobalStateFlags3 = 0xf;
                playSound(*(int32_t*)(*(int32_t*)((uint8_t*)this + 4) + 0x14));
                onDeactivate();
                syncWithServer();
                if (anotherLocalFlag == 0) {
                    return;
                }
            } else {
                if (forceFlag == 0) {
                    // Normal deactivation
                    if (actionFlags != 0) {
                        resetPower(this);
                    }
                    onUpdate();
                    setGlobalTimer(0x17);
                    setGlobalState1(4);
                    freeObject(*(void**)(playerObject + 0x108c));
                    onDeactivate();
                    if (actionFlags == 0) {
                        return;
                    }
                    syncWithServer();
                    return;
                } else {
                    // forceFlag != 0 but not forceActivate? This branch only if forceFlag set but not entering forceActivate? Actually check: forceFlag != 0, but forceActivate false (since else if). 
                    if (actionFlags != 0) {
                        resetPower(this);
                    }
                    onActivate();
                    onUpdate();
                    setGlobalTimer(0x17);
                    setGlobalState1(8);
                    freeObject(*(void**)(playerObject + 0x1090));
                    onDeactivate();
                    if (actionFlags != 0) {
                        syncWithServer();
                    }
                }
            }
            // Common after reaching here: set globals again
            setGlobalTimer(0x17);
            setGlobalState1(4);
            freeObject(*(void**)(playerObject + 0x108c));
            return;
        } else {
            // Power is active - deactivation path
            if (actionFlags != 0) {
                resetPower(this);
            }
            // Set globals to low timer states
            if (g_GlobalTimer1 < 7) g_GlobalTimer1 = 7;
            if (g_GlobalTimer2 > 7) g_GlobalTimer2 = 7; // condition: if 7 < g_GlobalTimer2 then set to 7
            g_GlobalStateFlags4 = 0;
            if (g_GlobalTimer1 < 0x16) g_GlobalTimer1 = 0x16;
            if (g_GlobalTimer2 > 0x16) g_GlobalTimer2 = 0x16;
            g_GlobalStateFlags5 = 1;
            onActivate();
            onUpdate();
            onSpecialAction();
            if (actionFlags != 0) {
                syncWithServer();
            }
            freeObject(*(void**)(playerObject + 0x108c));
            if (g_GlobalTimer1 < 7) g_GlobalTimer1 = 7;
            if (g_GlobalTimer2 > 7) g_GlobalTimer2 = 7;
            g_GlobalStateFlags4 = 1;
            return;
        }
    }

private:
    // Helper to set the timers and state more cleanly
    void setGlobalTimer(int32_t value) {
        if (g_GlobalTimer1 < value) g_GlobalTimer1 = value;
        if (g_GlobalTimer2 > value) g_GlobalTimer2 = value; // condition: if value < g_GlobalTimer2 then set to value? Actually: if 0x17 < DAT_00f15988 then set to 0x17. So it's a clamp: ensure g_GlobalTimer2 <= value? Actually original: if (0x17 < DAT_00f15988) DAT_00f15988 = 0x17; So if g_GlobalTimer2 > 0x17, set to 0x17. So yes, clamp down.
    }

    void setGlobalState1(int32_t value) {
        g_GlobalStateFlags1 = value; // _DAT_011f3a34
    }

    // Additional member variables would be here (based on this pointer)
    int32_t someReturnFlag;  // unaff_retaddr
    int32_t anotherLocalFlag; // unaff_BP
    int32_t playerIndex;     // in_EAX
};