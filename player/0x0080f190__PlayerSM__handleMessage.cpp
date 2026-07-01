// FUNC_NAME: PlayerSM::handleMessage

#include <cstdint>

// Decompiled from 0x0080f190 - EA EARS engine (Godfather 2)
// Message handler for player state machine. Handles messages 0x12 and 0x14.
// Class has embedded sub-state object at +0x14 (vtable pointer), position data at +0x17..+0x22, flag at +0x26.

typedef int (*HashLookupFunc)(void*, uint32_t, int*);
typedef int (*StateSwitchFunc)(void*);
typedef void (*PlayStateAnimFunc)(void*, uint32_t, int, int, int, float, float);
typedef void (*SetSubStateFlagFunc)(void*, int, int);

extern uint32_t FUN_00481620();                    // Player::isInConversation?
extern void*   FUN_00471610();                     // Player::getController (returns PlayerController*)
extern void    FUN_007e95c0(void*, void*, void*, void*, float, float); // Position update/lerp
extern float   FUN_007fd800();                     // Time delta?
extern uint32_t FUN_0080e8e0(int, int, int, int, int); // Base handler (fallback)
extern int     FUN_00800b60();                     // Some global state (3 values)
extern void    FUN_007f6420(int);                  // Set input blocking?

// Hash constants (likely derived from string hashes like "player_aim", "idle", etc.)
const uint32_t HASH_AIM_EVENT   = 0x383225a1;
const uint32_t HASH_STATE_IDLE  = 0x46f5c7b4;
const uint32_t HASH_STATE_RUN   = 0xc4405102;
const uint32_t HASH_STATE_CROUCH = 0xf1cd124a;
const uint32_t HASH_STATE_JUMP  = 0x54141790;
const uint32_t HASH_STATE_FALL  = 0x5e9d04d7;

uint32_t __thiscall PlayerSM::handleMessage(int* this_, uint32_t param_2, int param_3, uint32_t param_4, int messageType, uint32_t param_6)
{
    undefined1 uVar1;
    char cVar2;
    uint32_t hash;
    int iVar4;
    float10 fVar5;

    if (messageType == 0x12) // e.g., EPlayerMessage::AIM
    {
        messageType = 0; // Reset?
        // Lookup event via sub-state object's vtable (offset 0x10)
        HashLookupFunc lookupFunc = *(HashLookupFunc*)(*(int*)this_[0x14] + 0x10);
        cVar2 = lookupFunc(HASH_AIM_EVENT, &messageType);
        if ((cVar2 != 0) && (param_3 != 0))
        {
            cVar2 = FUN_00481620(); // Check if player is in conversation
            if (cVar2 == 0)
            {
                // Get controller and copy position/rotation data
                iVar4 = FUN_00471610(); // PlayerController*
                // Copy 3 ints (x,y,z) from controller offsets 0x30,0x34,0x38 to this_+0x20
                *(uint64_t*)(this_ + 0x20) = *(uint64_t*)(iVar4 + 0x30);
                this_[0x22] = *(int*)(iVar4 + 0x38);
                return 1;
            }
            // If in conversation, perform position update with lerp
            FUN_007e95c0(param_3 + 0x2b20, this_ + 0x20, this_ + 0x17, this_ + 0x1a, 0x10000, 0x80);
            return 1;
        }
        // If event not handled, do smooth interpolation
        fVar5 = (float10)FUN_007fd800(); // Time delta
        this_[0x20] = (int)(float)((float10)(float)this_[0x1a] * fVar5 + (float10)(float)this_[0x17]);
        this_[0x21] = (int)(float)((float10)(float)this_[0x1b] * fVar5 + (float10)(float)this_[0x18]);
        this_[0x22] = (int)(float)(fVar5 * (float10)(float)this_[0x1c] + (float10)(float)this_[0x19]);
        // Override Y from controller
        iVar4 = FUN_00471610();
        this_[0x21] = *(int*)(iVar4 + 0x34);
    }
    else if (messageType == 0x14) // e.g., EPlayerMessage::ANIMATION_STATE_CHANGE
    {
        if ((char)this_[0x26] != 0) // Some flag (active? enabled?)
        {
            hash = 0x46f5c7b4; // Default state hash (idle)
            // Query sub-state object's current state via vtable offset 0x270
            StateSwitchFunc stateFunc = *(StateSwitchFunc*)(*(int*)this_[0x14] + 0x270);
            uVar1 = stateFunc(); // Returns state index 0..4
            switch(uVar1)
            {
            case 1: // Running
                hash = 0xc4405102;
                break;
            case 2: // Crouching (maybe)
                iVar4 = FUN_00800b60(); // Global state check
                if (((iVar4 == 3) || (iVar4 == 2)) || (iVar4 == 4)) {
                    hash = 0xf1cd124a;
                }
                break;
            case 3: // Jumping
                hash = 0x54141790;
                break;
            case 4: // Falling
                hash = 0x5e9d04d7;
                break;
            }
            // Play animation via own vtable at offset 0x2c
            PlayStateAnimFunc animFunc = *(PlayStateAnimFunc*)(*this_ + 0x2c);
            animFunc(hash, 1, 1, 0, 0x3f800000, 0x3f800000); // params: hash, loop?, blend?, ..., scale
            FUN_007f6420(1); // Set input blocking?
            // Notify sub-state object via vtable offset 0x234
            SetSubStateFlagFunc flagFunc = *(SetSubStateFlagFunc*)(*(int*)this_[0x14] + 0x234);
            flagFunc(0, 1);
            return 1;
        }
    }
    else
    {
        // Unknown message, delegate to base handler
        return FUN_0080e8e0(param_2, param_3, param_4, messageType, param_6);
    }
    return 1;
}