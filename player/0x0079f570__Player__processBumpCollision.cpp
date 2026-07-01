// FUNC_NAME: Player::processBumpCollision

// Address: 0x0079f570
// Role: Handles collision bump events for the player character (soft/hard object bumps with cooldown)

#include <cstdint>

// Global variables (defined elsewhere)
extern uint32_t g_globalTime; // DAT_01205224 - global time in milliseconds (e.g., render frame count)
extern float g_minBumpSpeed; // DAT_00d5780c - minimum speed to consider bump
extern float g_hardBumpThreshold; // DAT_00d6a548 - speed threshold for hard/soft bump
extern uint32_t g_impactMask; // DAT_00e44680 - mask for impact force bits
extern float g_impactForceThreshold; // DAT_00d6a7c8 - threshold for impact force

// Forward declarations of called functions
uint32_t* getEntityFromHandlePair(uint32_t handleLow, uint32_t handleHigh); // FUN_005566a0
void profileBegin(uint32_t eventId); // FUN_005403e0 (0xCE = bump event)
void profileEnd(uint32_t eventId); // FUN_00540410
void playBumpSound(const char* soundName, uint32_t* entity, const float* position, int32_t unknownId); // FUN_00805a10

// External string pointers (global)
extern char* g_soundPlayerBumpSoft; // PTR_s_player_bump_object_soft_00e52840
extern char* g_soundPlayerBumpHard; // PTR_s_player_bump_object_hard_00e5283c

// Struct representing collision impact data (parameter 2)
struct CollisionImpactData {
    float normalX;       // param_2[0]
    float normalY;       // param_2[1]
    float normalZ;       // param_2[2]
    float forceOrSpeed;  // param_2[3]
    float dotProduct;    // param_2[4]
    float impactForce;   // param_2[5]  // The one used in mask comparison
    float padding;       // param_2[6]  // Multiplied by 0
    uint32_t entityHandleLow;  // param_2[10]
    uint32_t entityHandleHigh; // param_2[11]
};

void __thiscall Player::processBumpCollision(CollisionImpactData* impactData)
{
    uint32_t currentTime = g_globalTime;

    // Check if player has a valid entity and if speed exceeds minimum
    if ( (*(uint32_t*)(this + 0x04) != 0) && (g_minBumpSpeed < *(float*)(this + 0x0C)) )
    {
        // Wrap protection: if current time < last bump time, reset to 0
        if (g_globalTime < *(uint32_t*)(this + 0x08))
        {
            *(uint32_t*)(this + 0x08) = 0;
        }

        // Cooldown check: at least 2000ms since last bump
        if ( (2000 < (currentTime - *(uint32_t*)(this + 0x08))) &&
             // Impact force (from impactData[5]) masked and compared to threshold
             ( ((uint32_t)impactData->impactForce & g_impactMask) < (uint32_t)g_impactForceThreshold) )
        {
            // Get the bumped object from handle
            uint32_t* bumpedEntity = getEntityFromHandlePair(impactData->entityHandleLow, impactData->entityHandleHigh);
            if (bumpedEntity != nullptr)
            {
                // Save the impact position from collision normal (first three fields)
                float position[3] = {
                    impactData->normalX,
                    impactData->normalY,
                    impactData->normalZ
                };

                profileBegin(0xCE); // Start profiling bump event

                // Decide between soft and hard bump sound
                const char* bumpSound;
                if (*(float*)(this + 0x0C) >= g_hardBumpThreshold) {
                    bumpSound = g_soundPlayerBumpHard;
                } else {
                    bumpSound = g_soundPlayerBumpSoft;
                }

                // Play sound at the impact position
                playBumpSound(bumpSound, bumpedEntity, position, 0xFFFFFFFF);

                // Update last bump time
                *(uint32_t*)(this + 0x08) = currentTime;

                profileEnd(0xCE); // End profiling bump event
            }
        }
    }
}