// FUNC_NAME: PlayerSM::processAction
// Address: 0x007d5e70
// Role: Dispatches player actions based on action ID (range 0x31-0x36), checking flags and state, then calling specific handlers.

// Globals (known floats from game data)
extern float g_someMultiplier1; // 0x00e4486c
extern float g_someMultiplier2; // 0x00d5e28c

// Forward declarations of helper functions (likely members of same or related classes)
bool isPlayerAlive();                          // 0x00481620 – checks if player is alive
bool isPlayerInVehicle();                      // 0x008a4380 – checks if player is in a vehicle (or similar)
bool isPlayerInCover();                        // 0x007f7c60 – checks if player is in cover
int  getPlayerStateManager();                  // 0x007ab160 – returns pointer to global state manager
void startEnterVehicleAction();                // 0x007ac3a0 – begin enter vehicle sequence
void startExitVehicleAction(int arg1, float arg2);   // 0x007d5870 – begin exit vehicle sequence
void startMeleeAction(float arg2);             // 0x007d5d10 – begin melee/ground action
void startCoverAction(int arg1, float arg2);   // 0x007d5960 – begin cover action
void startInteractAction();                   // 0x007d5b30 – begin interaction (pickup, talk, etc.)
void applyForceToPlayer(float speedLimit, float force, int flags); // 0x00894e50 – apply force/speed to player
float getCurrentSpeed();                      // virtual call at +0x1c0, returns current speed
bool defaultActionHandler(int arg1, float arg2, int arg3, int actionID, int arg4); // 0x007abec0 – base class handler

bool __thiscall PlayerSM::processAction(int arg1, float arg2, int arg3, int actionID, int arg4)
{
    bool result = true; // default return value (success)
    switch (actionID - 0x31) {
    case 0: // Action 0x31 – Enter vehicle?
        if ((*(byte*)(*(int*)(this + 0x74) + 4) & 2) != 0   // check local flag bit 1 (some state)
            && (*(byte*)(getPlayerStateManager() + 4) & 0x10) != 0 // check global state bit 4
            && isPlayerAlive())
        {
            startEnterVehicleAction();
            return true;
        }
        break;

    case 1: // Action 0x32 – Exit vehicle?
        if (isPlayerAlive() && isPlayerInVehicle()) {
            startExitVehicleAction(arg1, arg2);
            return true;
        }
        break;

    case 2: // Action 0x33 – Melee or quick action?
        startMeleeAction(arg2);
        return true;

    case 3: // Action 0x34 – Take cover?
        if ((*(byte*)(*(int*)(this + 0x74) + 4) & 8) != 0) { // check local flag bit 3
            startCoverAction(arg1, arg2);
            return true;
        }
        break;

    case 4: // Action 0x35 – Interaction?
        if (isPlayerAlive()) {
            startInteractAction();
            return true;
        }
        break;

    case 5: // Action 0x36 – Speed boost or impulse?
    {
        int* pData = *(int**)(this + 0x58); // pointer to some component (e.g., vehicle or speed data)
        if (pData != nullptr && !isPlayerInCover() && isPlayerAlive()) {
            float currentSpeed = (**(float (__thiscall**)(int*))(*(int*)pData + 0x1c0))(pData);
            applyForceToPlayer(76.306f,  // max speed limit ~76.3
                               currentSpeed * g_someMultiplier1 * g_someMultiplier2 * arg2,
                               0);
            return true;
        }
        break;
    }

    default:
        result = defaultActionHandler(arg1, arg2, arg3, actionID, arg4);
    }

    return result;
}