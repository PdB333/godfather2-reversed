// FUNC_NAME: FadeManager::checkFadeTransition
// Address: 0x00517970
// Role: Checks if a screen fade transition has completed by verifying that the fade overlay is off-screen and the color matches a sentinel value.

// Global definitions (addresses based on Ghidra analysis)
struct FadeState {
    float colorR;       // +0x00 (DAT_01219250)
    float colorG;       // +0x04 (DAT_01219254)
    float colorB;       // +0x08 (DAT_01219258)
    float colorA;       // +0x0C (DAT_0121925c)
    float unk10;        // +0x10
    float unk14;        // +0x14
    float unk18;        // +0x18
    float unk1C;        // +0x1C
    float unk20;        // +0x20
    float unk24;        // +0x24
    float unk28;        // +0x28
    float currentFade;  // +0x2C (DAT_0121927c, used as transition progress)
    float posX;         // +0x30 (DAT_01219280, presumably screen x coordinate)
    float posY;         // +0x34 (DAT_01219284, y coordinate)
    float timer1;       // +0x38 (DAT_01219288)
    float timer2;       // +0x3C (DAT_0121928c)
    int32 fadeType;     // +0x40 (DAT_01219290, 4 = normal fade, 0x4000000 = flash)
    float unk44;        // +0x44 (DAT_01219294)
    int32 unk48;        // +0x48 (DAT_01219298)
    int32 unk4C;        // +0x4C (DAT_0121929c)
};

static FadeState* g_currentFadeState = reinterpret_cast<FadeState*>(0x01219250);
static FadeState* g_previousFadeState = reinterpret_cast<FadeState*>(0x012192b0);

// Constants (addresses from debug build)
static float g_fadeCheckThreshold = *reinterpret_cast<float*>(0x012192a0);
static float g_frameTime = *reinterpret_cast<float*>(0x00e2af44);
static float g_screenWidth = *reinterpret_cast<float*>(0x00e448ec);
static float g_fadeCompleteValue = *reinterpret_cast<float*>(0x00e2b1a4); // sentinel value when fade is done
static uint8* g_fadeActiveFlagByte = reinterpret_cast<uint8*>(0x00f17650); // byte at offset 3 assumed

// Enum for fade types
enum { FADE_TYPE_NORMAL = 4, FADE_TYPE_FLASH = 0x4000000 };

// External functions
char isFadeTransitionActive(void); // FUN_00517040
void debugPrintFade(int severity); // FUN_00609890

// Return 1 if fade transition is complete, 0 otherwise
uint8 FadeManager::checkFadeTransition(void)
{
    // Step 1: If fade threshold is zero, or currentFade < frameTime, or both timers < frameTime, reset target
    if (g_fadeCheckThreshold == 0.0f ||
        g_currentFadeState->currentFade < g_frameTime ||
        (g_currentFadeState->timer1 < g_frameTime && g_currentFadeState->timer2 < g_frameTime))
    {
        g_previousFadeState->currentFade = 0.0f; // set target to 0
    }
    else
    {
        // Check if transition is active; if not, copy current state to previous state
        char active = isFadeTransitionActive();
        if (active == 0)
        {
            // Copy entire FadeState from current to previous
            *g_previousFadeState = *g_currentFadeState;
        }
    }

    // Step 2: Check completion conditions
    uint8 result = 0;
    if (g_frameTime <= g_previousFadeState->currentFade &&
        (g_frameTime <= g_previousFadeState->timer1 || g_frameTime <= g_previousFadeState->timer2))
    {
        // If the fade type flag is set, log the event
        if (g_fadeActiveFlagByte[3] != 0) // accessing byte at offset 3 of the flag pointer
        {
            debugPrintFade(2);
        }

        // Determine if position is within screen bounds
        bool posXInBounds = (g_previousFadeState->posX > 0.0f && g_previousFadeState->posX <= g_screenWidth);
        bool posYInBounds = (g_previousFadeState->posY > 0.0f && g_previousFadeState->posY <= g_screenWidth);

        // Check fade type and color match to sentinel
        if (g_previousFadeState->fadeType == FADE_TYPE_NORMAL ||
            g_previousFadeState->fadeType == FADE_TYPE_FLASH)
        {
            if (g_previousFadeState->colorR == g_fadeCompleteValue &&
                g_previousFadeState->colorG == g_fadeCompleteValue &&
                g_previousFadeState->colorB == g_fadeCompleteValue &&
                !posXInBounds && !posYInBounds)
            {
                result = 1; // fade complete
            }
        }
    }

    // Step 3: Mark that this function has been executed
    g_fadeActiveFlagByte[3] = 1;

    return result;
}