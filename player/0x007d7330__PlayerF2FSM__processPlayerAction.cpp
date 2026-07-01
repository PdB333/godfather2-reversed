// FUNC_NAME: PlayerF2FSM::processPlayerAction
// Address: 0x007d7330
// This function handles player state actions (IDs 0x31 to 0x45) for the free-2-fight state machine.
// It dispatches to various subsystems based on the action code. The 'this' pointer (param_1) is a PlayerF2FSM, 
// param_2-4 are generic context parameters, param_5 is the action ID, param_6 is extra data.

#include <cstdint>

// Forward declarations for known EA EARS engine classes
class PlayerEntity; // offset 0x16 in PlayerF2FSM
class PlayerComponent; // obtained via FUN_0073b040

// Known globals (from decompiled)
extern float DAT_00e44748; // some scaling factor
extern uint32_t _DAT_00e53200; // some global handle/matrix

// Internal functions (renamed based on context)
bool isPlayerInCar();
bool canPlayerTriggerAction(); // FUN_007ab330
bool isCarDoorOpen(); // FUN_007f95d0 -> returns 0/1
bool isActionStateActive(uint32_t stateId); // FUN_0079e920
bool canPerformAction(uint32_t actionId); // FUN_00690150
bool canFinishAction(); // FUN_007ab350
bool isDialogPlaying(uint32_t dialogId); // FUN_00690210
bool isInCombat(); // FUN_007f7b90
bool isPlayerAlive(); // FUN_00732380
bool isPlayerDead(); // FUN_0078a7d0
bool isPlayerOnFoot(); // FUN_007a49d0
bool canPlayerDoActionX(); // FUN_007d63b0

uint32_t getActionState(uint32_t stateId); // FUN_00798f50
uint32_t getCurrentTarget(); // FUN_007ab710
uint32_t getMissionForTarget(uint32_t target, uint32_t magic); // FUN_006bc8d0
uint32_t getMissionObjective(uint32_t mission); // FUN_006ad770

void playSoundEffect(uint32_t soundEffectId); // FUN_007ab470
void stopSoundEffect(uint32_t soundEffectId); // FUN_007ab4d0
void loadAsset(uint32_t assetId); // FUN_007f63e0
void unloadAsset(uint32_t assetId); // FUN_007f6420

void setCameraTarget(PlayerEntity* entity, float speed); // FUN_00796ba0
void playAnimation(uint32_t animId, uint32_t flags); // FUN_0079f100

PlayerEntity* getPlayerEntity(); // FUN_00471610
void constructWorldPosition(uint8_t stackBuffer[76], PlayerEntity* entity, float offset); // FUN_00793b50 (construct a position vector)
bool isPlayerNearPoint(uint8_t stackBuffer[76]); // FUN_007abbc0 (checks proximity)
void playAudioEvent(uint32_t audioEventId); // FUN_006901b0

void playObjectSound(PlayerF2FSM* self, uint32_t soundId, uint32_t unk1, uint32_t unk2, uint32_t unk3, int boneIndex, float volume); // vtable call at offset 0x2c

float getPlayerSpeed(); // FUN_00716c30
float getVehicleSpeed(PlayerEntity* entity); // vtable call at offset 0x1c0

void triggerCinematicEffect(); // FUN_008de360

void beginStatEvent(uint32_t statType, uint32_t unk); // FUN_006fbc40
void addStatEvent(uint32_t statId, int32_t value, uint32_t context, uint32_t unk); // FUN_007f96a0
void endStatEvent(); // FUN_006fbc70

PlayerComponent* getPlayerComponent(PlayerEntity* entity); // FUN_0073b040
void showHUDMessage(); // FUN_00800960
void enterVehicle(PlayerEntity* entity); // FUN_0087c9f0
void setPlayerStateFlag(uint32_t flag); // FUN_00766470
void clearPlayerStateFlag(uint32_t flag); // FUN_00766440

void applyMovement(float speedDelta, uint32_t matrix, uint8_t* stackBuf, uint32_t* context); // FUN_007992a0
void someMatrixOp(uint32_t matrix, uint32_t param3, uint32_t* context, int zero); // FUN_00b9a9fa

void toggleActionMode1(bool mode); // FUN_009ac7f0
void toggleActionMode2(bool mode); // FUN_009ace50

// Default handler
bool handleDefaultAction(uint32_t param2, uint32_t param3, uint32_t param4, int actionId, uint32_t param6); // FUN_007abec0

bool __thiscall PlayerF2FSM::processPlayerAction(int actionId, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param6)
{
    // +0x16 (offset 0x58) -> pointer to PlayerEntity (the player's entity)
    PlayerEntity* playerEntity = reinterpret_cast<PlayerEntity*>(this->m_playerEntity);
    bool result = true; // return 1 by default

    switch (actionId - 0x31) // action IDs start at 0x31
    {
    case 0: // action 0x31: Play sound effect
        playSoundEffect(3);
        return true;

    case 1: // action 0x32: Stop sound effect
        stopSoundEffect(3);
        return true;

    case 2: // action 0x33: Load asset
        loadAsset(0xc);
        return true;

    case 3: // action 0x34: Unload assets
        unloadAsset(0xc);
        unloadAsset(0xd);
        return true;

    case 4: // action 0x35: Enter vehicle interaction
    {
        // Check if player is in car and can trigger action
        if (isPlayerInCar() && canPlayerTriggerAction())
        {
            // Get vehicle speed from entity vtable (+0x1c0)
            float speed = reinterpret_cast<float (*)(PlayerEntity*)>(*reinterpret_cast<uintptr_t*>(playerEntity) + 0x1c0)();
            setCameraTarget(playerEntity, speed);
            playAnimation(0x1b, 0); // e.g., "enter car" animation

            PlayerEntity* player = getPlayerEntity();
            uint8_t positionBuffer[76]; // used to construct world position
            constructWorldPosition(positionBuffer, player, 0x30); // offset +0x30 is position
            if (isPlayerNearPoint(positionBuffer))
            {
                playAudioEvent(0x4a); // play "car door" audio
                return true;
            }
        }
        break;
    }

    case 5: // action 0x36: Car door sound
    {
        int doorState = isCarDoorOpen(); // returns 0 (closed) or 1 (open)
        if (doorState == 0)
        {
            // Car door closed sound
            this->m_soundEventId = 0xD42BC284; // some sound event ID
            // +0x2c vtable call: playObjectSound(this, soundId, 1, 1, 0, boneIndex, 1.0f)
            reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(this) + 0x2c)(0xD42BC284, 1, 1, 0, playerEntity->boneIndex, 1.0f);
        }
        else
        {
            // Car door open sound
            this->m_soundEventId = 0xA3C283C1;
            reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(this) + 0x2c)(0xA3C283C1, 1, 1, 0, playerEntity->boneIndex, 1.0f);
        }
        return true;
    }

    case 6: // action 0x37: Handle weapon/ammo state
    {
        uint32_t state = getActionState(0xc);
        if (isActionStateActive(state) && canPerformAction(0x32))
        {
            unloadAsset(0x32);
            return true;
        }
        break;
    }

    case 7: // action 0x38: Trigger cinematic effect
    {
        if (canFinishAction())
        {
            triggerCinematicEffect();
            return true;
        }
        break;
    }

    case 8: // action 0x39: Unused action
        break;

    case 9: // action 0x3a: Mission objective completion
    {
        int target = getCurrentTarget();
        if (target != 0 && !isDialogPlaying(0xf))
        {
            int mission = getMissionForTarget(target, 0x369ac561);
            int objective = getMissionObjective(mission);
            if (mission != 0 && objective != 0 && !isInCombat())
            {
                if (*(int*)(objective + 0x1c) != 0 && *(int*)(objective + 0x1c) != 0x3c && isPlayerAlive())
                {
                    // Award stats for completion
                    uint32_t context = 0;
                    uint32_t statContext = beginStatEvent(0, 0);
                    addStatEvent(0x5300dd7b, 100, statContext, context);
                    endStatEvent();

                    PlayerComponent* playerComp = getPlayerComponent(playerEntity);
                    reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(playerComp) + 0x28)(0xe87ed379, 0, 0xffffffff, 0);

                    if (isPlayerDead())
                    {
                        context = 0;
                        statContext = beginStatEvent(0, 0);
                        addStatEvent(0x53fe2879, 100, statContext, context);
                        endStatEvent();
                    }
                }
                // Always award some stat
                uint32_t context = 0;
                uint32_t statContext = beginStatEvent(0, 0);
                addStatEvent(0, 0, statContext, context);
                endStatEvent();
                return true;
            }
        }
        break;
    }

    case 10: // action 0x3b: Show HUD message based on player state
    {
        // Check bit 10 of some player data at offset +0x8E0 (0x238 * 4)
        if ((playerEntity->flags[0x238] & (1 << 10)) != 0)
        {
            showHUDMessage();
            return true;
        }
        break;
    }

    case 11: // action 0x3c: Enter vehicle (if on foot)
    {
        uint32_t context = 0;
        uint32_t statContext = beginStatEvent(0, 0);
        addStatEvent(0x6801c6be, 0, statContext, context);
        endStatEvent();

        if (isPlayerOnFoot())
        {
            enterVehicle(playerEntity);
            setPlayerStateFlag(0x20000); // set in-vehicle flag
            return true;
        }
        break;
    }

    case 12: // action 0x3d: Exit vehicle (if in vehicle)
    {
        if (isPlayerOnFoot())
        {
            clearPlayerStateFlag(0x20000); // clear in-vehicle flag
            return true;
        }
        break;
    }

    case 13: // action 0x3e: Apply movement/dodge
    {
        PlayerEntity* player = getPlayerEntity();
        if (getPlayerSpeed() != 0)
        {
            float positionDiff = getPlayerSpeed() - player->position; // simplified; actual code uses offsets
            uint32_t context = 0;
            uint32_t matrix = _DAT_00e53200; // some world matrix
            someMatrixOp(matrix, param3, &context, 0);
            applyMovement(positionDiff * DAT_00e44748, matrix, &context, context);
            return true;
        }
        break;
    }

    case 14: // action 0x3f: Enter cover
    {
        enterCover(playerEntity); // FUN_007eb290
        return true;
    }

    case 15: // action 0x40: Exit cover
    {
        exitCover(playerEntity); // FUN_007eb2d0
        return true;
    }

    case 16: // action 0x41: Toggle action mode 1 (on)
    {
        uint32_t state = getActionState(0x45);
        if (isActionStateActive(state) && !canPerformAction(0x30))
        {
            getPlayerComponent(playerEntity);
            toggleActionMode1(true);
            return true;
        }
        break;
    }

    case 17: // action 0x42: Toggle action mode 1 (off)
    {
        uint32_t state = getActionState(0x43);
        if (isActionStateActive(state) && !canPerformAction(0x30))
        {
            getPlayerComponent(playerEntity);
            toggleActionMode1(false);
            return true;
        }
        break;
    }

    case 18: // action 0x43: Toggle action mode 2 (on)
    {
        uint32_t state = getActionState(0x46);
        if (isActionStateActive(state) && !canPerformAction(0x30))
        {
            getPlayerComponent(playerEntity);
            toggleActionMode2(true);
            return true;
        }
        break;
    }

    case 19: // action 0x44: Toggle action mode 2 (off)
    {
        uint32_t state = getActionState(0x44);
        if (isActionStateActive(state) && !canPerformAction(0x30))
        {
            getPlayerComponent(playerEntity);
            toggleActionMode2(false);
            return true;
        }
        break;
    }

    case 20: // action 0x45: Perform reload/switch weapon action
    {
        if (canPlayerDoActionX())
        {
            playAnimation(0x35, 0); // e.g., reload animation
            return true;
        }
        break;
    }

    default:
        // Unhandled actions go to default handler
        result = handleDefaultAction(param2, param3, param4, actionId, param6);
    }

    return result;
}