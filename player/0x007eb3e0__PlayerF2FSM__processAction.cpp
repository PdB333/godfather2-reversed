// FUNC_NAME: PlayerF2FSM::processAction
// Address: 0x007eb3e0
// Handles various action types (0x31-0x38) for the free-roam player state machine.
// Uses EA EARS engine structures and global game state checks.

typedef unsigned int uint;
typedef unsigned char byte;
typedef int int32;
typedef unsigned int uint32;

class Entity; // forward
class PlayerF2FSM; // forward

// External globals
extern uint32 DAT_01205224; // game time in ms? (e.g., GetTickCount)
extern void* DAT_01130950; // building manager or similar

// Known helper functions (renamed for clarity)
extern bool isGamePaused(); // 0x00481660 - checks if game is paused (e.g., menu or cutscene)
extern bool isFreeRoamActive(); // 0x00481640 - checks if player is in free roam mode
extern bool isInCombatOrMenu(); // 0x004ac260 - checks combat state or similar
extern bool canInteract(); // 0x007eb220 - checks if interaction allowed (based on timers etc.)
extern int32 getInteractionResult(); // 0x0090e2d0 - gets result of current interaction (e.g., target ID)
extern Entity* getEntityComponent(int* entity, int componentType); // 0x006bea40 - retrieves component from entity
extern bool isPlanEnabled(uint32 planID); // 0x00690150 - checks if a specific plan/state is enabled (planID=0x14)
extern void setupInteraction(int, PlayerF2FSM*, Entity*); // 0x007ea5e0 - prepares an interaction
extern void playSoundEvent(int soundID, int channel, bool, ...); // 0x0079fb90 - plays a sound event, soundID 0x16 or 0x18
extern void postAction(int actionCode); // 0x007f6420 - post action result (0x17 = something)
extern void hideUI(void* uiElement); // 0x0079dcc0 - hides a UI element
extern void* findBuildingByID(void* buildingManager, int id); // 0x0043b870 - finds a building object
extern void startHitmanMission(); // 0x00998270 - triggers hitman mission
extern void enterVehicleState(Entity* entity); // 0x007eb290 - handles entering a vehicle
extern void exitVehicleState(Entity* entity); // 0x007eb2d0 - handles exiting a vehicle
extern void endCurrentAction(); // 0x0079f100 - ends current action
extern byte baseClassProcessAction(void* param2, void* param3, void* param4, int actionId, void* param6); // 0x007abec0

byte PlayerF2FSM::processAction(int actionId, void* param2, void* param3, void* param4, void* param6)
{
    byte result = 1; // local_1d, default success
    int32 entityPtr; // param_1[0x16] = m_pEntity (offset +0x58)
    int* componentPtr; // piVar2
    int32 tempInt;
    bool flag; // bVar4
    float healthPercent; // fVar5
    byte soundId;

    switch (actionId - 0x31)
    {
        case 0: // Action: Update / Idle (0x31)
        {
            // Check if entity has a specific flag set (bit 0x14 at offset +0x8e0)
            if ((*(uint32*)(m_pEntity + 0x8e0) >> 0x14) & 1)
            {
                resetInteractionTimeout(); // FUN_007eb260
            }

            // Check if game is not paused and free roam is active
            if ((!isGamePaused() || !isFreeRoamActive()) && isInCombatOrMenu())
            {
                // Call virtual function at vtable+0x2c (likely Update or Process)
                (this->*(code*)this->vtable[0x2c])();
            }

            // Secondary condition: if not paused and canInteract() and time elapsed > threshold
            if (!isGamePaused() && canInteract() && 
                (DAT_01205224 + 5000U < (uint32)m_interactTimeout)) // m_interactTimeout at +0x74
            {
                m_interactTimeout = DAT_01205224 + 5000U;
                resetInteractionTimeout(); // FUN_007eb260
                tempInt = getInteractionResult(); // FUN_0090e2d0
                m_lastInteractionResult = tempInt; // +0x80
                return 1;
            }
            break;
        }
        case 1: // Action: Enter (0x32) - possibly entering vehicle or interacting
        {
            entityPtr = m_pEntity; // +0x58
            if (isGamePaused() || isFreeRoamActive())
            {
                componentPtr = getEntityComponent(entityPtr); // FUN_006bea40: returns some component pointer
                // Check a flag at entity offset +0x2454
                if (*(byte*)(entityPtr + 0x2454) == 0)
                {
                    // Call vtable+0x3c(0) on component (likely set state or animation)
                    (componentPtr->*(code*)componentPtr->vtable[0x3c])(0);
                }
                else
                {
                    if (isFreeRoamActive())
                    {
                        flag = false;
                        if (*(byte*)(entityPtr + 0x2400) == 0) // some lock flag
                            flag = false;
                        else
                            flag = true;
                    }
                    else
                    {
                        flag = false;
                    }

                    // Check if plan 0x14 is enabled, or flag is true
                    if (isPlanEnabled(0x14) || flag)
                    {
                        // Get vtable+0x2c (likely getHealthPercent or similar)
                        healthPercent = (componentPtr->*(code*)componentPtr->vtable[0x2c])();
                        (componentPtr->*(code*)componentPtr->vtable[0x3c])(healthPercent);
                    }
                    else
                    {
                        setupInteraction(0, this, entityPtr); // FUN_007ea5e0
                        (componentPtr->*(code*)componentPtr->vtable[0x3c])(0);
                        flag = false;
                    }

                    // Play sound based on flag
                    soundId = flag ? 0x16 : 0x18;
                    if (!isGamePaused())
                    {
                        playSoundEvent(soundId, 1, 0, 0, 0); // FUN_0079fb90
                    }
                }
            }
            resetInteractionTimeout(); // FUN_007eb260
            postAction(0x17); // FUN_007f6420
            return 1;
        }
        case 2: // Action: Show / Hide UI (0x33)
        {
            hideUI((void*)m_pUIElement); // +0x78
            if (isFreeRoamActive())
            {
                *(byte*)(m_pEntity + 0x2400) = 1; // set lock flag
                return 1;
            }
            break;
        }
        case 3: // Action: Start Mission (0x34) - maybe building interaction
        {
            if (m_pEntity != 0)
            {
                void* building = findBuildingByID(DAT_01130950, m_pEntity); // FUN_0043b870
                if (building != 0 && *(int32*)(building + 0x20) != 0)
                {
                    startHitmanMission(); // FUN_00998270
                    return 1;
                }
            }
            break;
        }
        case 4: // Action: Enter Vehicle (0x35)
        {
            enterVehicleState((Entity*)m_pEntity); // FUN_007eb290
            return 1;
        }
        case 5: // Action: Exit Vehicle (0x36)
        {
            exitVehicleState((Entity*)m_pEntity); // FUN_007eb2d0
            return 1;
        }
        case 6: // Action: Force Update / Return Status (0x37)
        {
            result = 0x3f; // 63, likely a special status code
            (this->*(code*)this->vtable[0x2c])(); // call update
            return result;
        }
        case 7: // Action: End Current (0x38)
        {
            endCurrentAction(); // FUN_0079f100
            return 1;
        }
        default:
        {
            result = baseClassProcessAction(param2, param3, param4, actionId, param6);
        }
    }
    return result;
}