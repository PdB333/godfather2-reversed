// FUNC_NAME: Player::calculateWeaponSpread

// 0x007f50e0
// Player::calculateWeaponSpread - Computes weapon spread offsets and sets a cooldown timer
// Based on weapon data flags, random numbers, and previous spread state.
// Offsets:
//   param_1 (this):
//     +0x60: flags (bit 11 = canShoot?)
//     +0x64: flags2 (bit 11 = other condition?)
//     +0x6c8: float spreadHorizontal
//     +0x6cc: float spreadVertical
//     +0x6d8: uint spreadTimer (cooldown frame count)
//     +0x6dc: byte spreadFlags (bit0: spreadActive, bit1: recoilRecovery)
//   param_2 (weaponData):
//     +0x204: float baseSpreadX (time? angle?)
//     +0x208: float baseSpreadY
//     +0x20c: float spreadResetX
//     +0x210: float spreadResetY
//     +0x214: float spreadMinX (or negative max)
//     +0x218: float spreadMaxX
//     +0x21c: float spreadMaxY
//     +0x220: float spreadRandomScaleX
//     +0x224: float spreadChanceX
//     +0x228: float recoilThreshold

// Constants:
//   g_currentFrameCount (0x01205224) - Global frame counter
//   spreadBaseMin (0x00d577a0) - Minimum vertical spread threshold
//   spreadInvertValue (0x00e44564) - Value to invert spread (e.g., 360 degrees or 1.0)
//   spreadScaleFactor (0x00e44590) - Random scaling factor (likely 1.0f / RAND_MAX)
//   spreadInvertChance (0x00d5c458) - Probability threshold for inverting spread

#include <cstdlib>  // for rand()

// Forward declarations
class WeaponData; // Provided by game code
class Player;

// Random float helper - returns random float in [0, 1] perhaps
static float __fastcall GetRandomFloat(float maxValue);  // FUN_006b6f90

// Random int helper - returns random int based on input
static int __fastcall GetRandomIntOffset(int base);   // FUN_006eb670

// Global variables (externals)
extern uint32_t g_currentFrameCount;  // DAT_01205224
extern float g_spreadBaseMin;         // DAT_00d577a0
extern float g_spreadInvertValue;     // DAT_00e44564
extern float g_spreadScaleFactor;     // DAT_00e44590 (typically 1.0f / RAND_MAX)
extern float g_spreadInvertChance;    // _DAT_00d5c458

void __thiscall Player::calculateWeaponSpread(int thisPtr, WeaponData* weaponData)
{
    byte spreadFlags;
    int randomValue1, randomValue2, randomValue3;
    float randomFloat1, randomFloat2;
    float fVar5, fVar6;
    int roundedX, roundedY;

    // Check if weapon data is null or if player can't shoot (bits 11 of two flag fields)
    if ((weaponData == nullptr) ||
        (((*(uint32_t*)(thisPtr + 0x60) >> 0xb) & 1) == 0) ||
        (((*(uint32_t*)(thisPtr + 100) >> 0xb) & 1) == 0))
    {
        *(float*)(thisPtr + 0x6c8) = 0.0f;
        *(float*)(thisPtr + 0x6cc) = 0.0f;
        return;
    }

    // Check cooldown timer
    if (g_currentFrameCount <= *(uint32_t*)(thisPtr + 0x6d8))
        return;

    spreadFlags = *(byte*)(thisPtr + 0x6dc);

    // If spread is already active (bit0 set)
    if ((spreadFlags & 1) != 0)
    {
        if ((spreadFlags & 2) == 0)
        {
            // No recoil recovery: reset spread to zero
            *(float*)(thisPtr + 0x6cc) = 0.0f;
            *(float*)(thisPtr + 0x6c8) = 0.0f;

            // Read reset spread values and clear bit0
            roundedX = (int)(longlong)roundf(*(float*)(weaponData + 0x20c));
            roundedY = roundedX;
            fVar6 = *(float*)(weaponData + 0x210);
            *(byte*)(thisPtr + 0x6dc) = spreadFlags & 0xfe;
            roundedY = (int)(longlong)roundf(fVar6);
        }
        else
        {
            // Recoil recovery: adjust vertical spread based on threshold
            if (*(float*)(thisPtr + 0x6cc) <= g_spreadBaseMin)
            {
                *(float*)(thisPtr + 0x6cc) = g_spreadInvertValue - *(float*)(weaponData + 0x214);
            }
            else
            {
                *(float*)(thisPtr + 0x6cc) = *(float*)(weaponData + 0x214);
            }

            // Read base spread values and clear bit1
            roundedX = (int)(longlong)roundf(*(float*)(weaponData + 0x204));
            roundedY = roundedX;
            fVar6 = *(float*)(weaponData + 0x208);
            *(byte*)(thisPtr + 0x6dc) = spreadFlags & 0xfd;
            roundedY = (int)(longlong)roundf(fVar6);
        }
        goto LAB_SPREAD_TIMER;
    }

    // --- Spread not active, generate new random spread ---

    randomValue1 = rand();
    fVar5 = (float)randomValue1 * g_spreadScaleFactor;  // random value in [0,1)

    randomValue2 = rand();
    randomValue3 = rand();

    fVar6 = g_spreadScaleFactor;
    *(byte*)(thisPtr + 0x6dc) = spreadFlags & 0xfd;  // Clear bit1

    // Determine vertical spread based on random chance
    if (*(float*)(weaponData + 0x224) <= (float)randomValue2 * fVar6)
    {
        *(float*)(thisPtr + 0x6cc) = *(float*)(weaponData + 0x214);  // Use min spread
    }
    else
    {
        *(float*)(thisPtr + 0x6cc) = *(float*)(weaponData + 0x218);  // Use max spread
        // Check if recoil threshold passed -> set bit1
        float10 randomRecoil = GetRandomFloat(1.0f);
        if (randomRecoil < (float10)*(float*)(weaponData + 0x228))
        {
            *(byte*)(thisPtr + 0x6dc) |= 2;  // Set recoil recovery flag
        }
    }

    // Random chance to invert vertical spread
    if ((float)randomValue3 * fVar6 < g_spreadInvertChance)
    {
        *(float*)(thisPtr + 0x6cc) = g_spreadInvertValue - *(float*)(thisPtr + 0x6cc);
    }

    // Determine horizontal spread
    if (fVar5 < *(float*)(weaponData + 0x220) || fVar5 == *(float*)(weaponData + 0x220))
    {
        fVar6 = 0.0f;
    }
    else
    {
        *(float*)(thisPtr + 0x6c8) = *(float*)(weaponData + 0x21c);
        float10 randomInv = GetRandomFloat(1.0f);
        if (randomInv < (float10)g_spreadInvertChance)
        {
            fVar6 = g_spreadInvertValue - *(float*)(thisPtr + 0x6c8);
        }
        else
        {
            fVar6 = *(float*)(thisPtr + 0x6c8);
        }
    }
    *(float*)(thisPtr + 0x6c8) = fVar6;

    // Round base spread values and set spreadActive flag (bit0)
    roundedX = (int)(longlong)roundf(*(float*)(weaponData + 0x204));
    roundedY = roundedX;
    fVar6 = *(float*)(weaponData + 0x208);
    *(byte*)(thisPtr + 0x6dc) |= 1;
    roundedY = (int)(longlong)roundf(fVar6);

LAB_SPREAD_TIMER:
    // Set spread timer for cooldown
    *(uint32_t*)(thisPtr + 0x6d8) = g_currentFrameCount;
    int randomTime = GetRandomIntOffset(roundedY);
    *(uint32_t*)(thisPtr + 0x6d8) += randomTime + roundedX;

    return;
}