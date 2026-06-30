// Xbox PDB: EARS::Modules::NPC::ActivateHudIndicator
// FUNC_NAME: HUDActionManager::setTargetingMode

#include <cstring>
#include <cstdio>

// Constants for field offsets (guessed from decompiled access)
// this->fields:
// +0x841 (0x2104) : currentMode (int)
// +0x842 (0x2108) : displayCallback (void*)
// +0x843 (0x210C) : unknownFlag
// +0x844 (0x2110) : unknownCounter
// +0x845 (0x2114) : freeCallback (void*)
// +0x846 (0x2118) : pointer to some struct (maybe `HUDDisplay**`)
// +0x847 (0x211C) : isDirty (byte)
// +0x848 (0x2120) : targetList (void*)
// +0x7d5 (0x1F54) : playerFlags1 (uint)
// +0x7e6 (0x1F98) : playerFlags2 (uint)
// +0x7b4 (0x1ED0) : someID (int)
// +0x238 (0x8E0) : generalFlags (uint)

// Forward declarations of helper functions (unmangled)
void clearHudDisplay();
void getCurrentHudString(char* out, int maxLen);
bool isPlayerInF2F();
int getPlayerState(); // returns pointer to some object
bool isFamilyMember(int statePtr);
const char* getFriendContext(); // returns something
bool checkPlayerFlag(/*this*/ int thisPtr, int flag);
int getSomeContext(); // returns some pointer
void convertString(const char* src, char* dst);
void showTargetingDisplay(const char* text, int, void*, int, int* displayPtr, int unknown, int*);

void HUDActionManager::setTargetingMode(int mode, const char* customText)
{
    // Local stack buffer for targeting text
    char textBuffer[64] = {0}; // local_120 is 64 bytes
    char currentText[64] = {0}; // local_90
    int* thisPtr = this; // param_1

    // Handle invalid modes (greater than 17) – cleanup
    if (mode > 17) // 0x11 = 17, so mode>17 triggers cleanup
    {
        thisPtr[0x841] = mode; // store mode
        if (thisPtr[0x842] != 0) // if callback exists
        {
            ((void (*)(int))thisPtr[0x845])(thisPtr[0x842]); // call free callback
        }
        thisPtr[0x842] = 0;
        thisPtr[0x844] = 0;
        thisPtr[0x843] = 0;

        if ((char)thisPtr[0x847] != '\0') // if dirty flag
        {
            clearHudDisplay();
            thisPtr[0x847] = 0;
        }

        int* targetList = thisPtr[0x848];
        if (targetList == 0)
            return;

        // Free target list
        clearHudDisplay();
        freeTargetList(targetList);
        thisPtr[0x848] = 0;
        return;
    }

    // Determine source string based on mode
    const char* sourceString = nullptr;
    uint flags = (uint)thisPtr[0x238] >> 4;
    bool isOverride = (flags & 1) != 0; // some override flag

    switch (mode)
    {
    case 1: // Face‑to‑face targeting
        if (!isOverride)
        {
            // Check player flags: not already in f2f, and either crew or other state
            if (((uint)thisPtr[0x7e6] >> 8 & 1) == 0 &&
                (((uint)thisPtr[0x7d5] >> 8 & 1) != 0 || ((uint)thisPtr[0x7e6] >> 0xb & 1) != 0))
            {
                if (isPlayerInF2F() != '\0')
                {
                    sourceString = "hud_targeting_f2f"; // global string pointer
                    break;
                }
            }
            // If conditions not met, fall through to default
            if (!isOverride)
                sourceString = customText; // use custom text
        }
        else
        {
            sourceString = "hud_targeting_f2f";
        }
        break;

    default:
        if (isOverride)
        {
            sourceString = "hud_targeting_f2f"; // same override for all defaults?
        }
        else
        {
            sourceString = customText;
            if (mode != 0x11) // 17 = custom text via parameter
            {
                // Table lookup for string pointers (global array)
                sourceString = *(const char**)(0x00e51588 + mode * 4);
            }
        }
        break;

    case 3: // Recruit targeting
        if (!isOverride)
        {
            // Check player state
            int playerState = getPlayerState();
            bool isRecruit = (**(code**)(*playerState + 0x1bc))(); // virtual call
            if (isRecruit == '\0')
            {
                // Not already recruiting – check if can recruit
                int familyState = getPlayerState();
                bool canRecruit = isFamilyMember(familyState);
                if (canRecruit == '\0')
                {
                    strncpy(textBuffer, "hud_targeting_recruit", 64);
                }
                else
                {
                    // Use family member string (8 bytes + padding?)
                    textBuffer[0..7] = "mm_fam_mem"; // from global data
                    textBuffer[8..11] = padding? Actually only 10 chars then stop
                    // Simplified: we'll fill from global bytes
                }
            }
            else
            {
                textBuffer[0..7] = "mm_crew"; // from global data
            }

            // Manage target list allocation
            if (thisPtr[0x848] == 0)
            {
                int* newList = allocateTargetList(0x1c); // size 28
                if (newList != 0)
                {
                    int result = initializeTargetList(thisPtr, unknownValue, &globalData);
                    thisPtr[0x848] = result;
                }
                else
                {
                    thisPtr[0x848] = 0;
                }
            }
            else
            {
                updateTargetList(thisPtr, unknownValue, &globalData);
            }
        }
        else
        {
            // Override – free target list
            int* targetList = thisPtr[0x848];
            if (targetList != 0)
            {
                clearHudDisplay();
                freeTargetList(targetList);
                thisPtr[0x848] = 0;
            }
        }
        goto LAB_00737c00; // proceed to display

    case 4: // Money taker targeting
        if (isOverride)
            goto LAB_00737c00;
        sourceString = "hud_targeting_moneytaker";
        // Check if player has crew active and is not in f2f
        if (((uint)thisPtr[0x7e6] >> 8 & 1) != 0 &&
            isPlayerInF2F() == '\0' &&
            checkPlayerFlag(thisPtr, 2) == '\0')
        {
            // Override to face‑to‑face
            sourceString = "hud_targeting_f2f";
        }
        break;

    case 5: // Hit targeting
        if (!isOverride)
        {
            int playerState = getPlayerState();
            if (playerState != 0)
            {
                // Check if player is in "hit" state
                int again = getPlayerState();
                if ((*(uint*)(again + 0x5c) >> 0x1d & 1) == 0)
                {
                    // Normal state – build formatted string
                    int id = thisPtr[0x7b4];
                    int friendContext = (int)getFriendContext();
                    if (friendContext != 0)
                    {
                        const char* prefix = *(const char**)(friendContext + 0x8c);
                        if (prefix == nullptr) prefix = "unknown";
                        snprintf(textBuffer, 64, "mm_%s%d", prefix, id);
                    }
                }
                else
                {
                    // Hit state – use "hud_targeting_hit" string
                    textBuffer[0..15] = "hud_targeting_hit"; // copy from global
                }
            }
        }
        goto LAB_00737c00;
    }

    // Copy source string to textBuffer if we didn't already set it
    if (sourceString != nullptr)
    {
        strncpy(textBuffer, sourceString, 64);
    }

LAB_00737c00:
    // Compare with current display string
    currentText[0] = 0;
    memset(currentText + 1, 0, 63); // zero rest
    int* displayHandle = &thisPtr[0x846];
    getCurrentHudString(currentText);

    if (((char)thisPtr[0x847] != '\0') && (currentText[0] != 0))
    {
        // If there is a current display and it matches the new text, skip update
        if (textBuffer[0] == 0)
        {
            return;
        }
        if (strcmp(textBuffer, currentText) == 0)
        {
            return;
        }
    }

    // Update display
    clearHudDisplay();
    thisPtr[0x847] = 1;
    thisPtr[0x841] = mode;

    if (mode == 0x11) // 17 – custom text
    {
        copyCustomText(customText); // FUN_004d3d90
    }
    else
    {
        copyDefaultText(); // FUN_00401060
    }

    int context = getSomeContext(); // FUN_00471610
    // Build some data structure for the display call (quaternion/matrix?)
    float someValue = 0.0f; // from DAT_00d5780c
    struct {
        float a,b,c,d;
        float e,f,g,h;
        float i,j,k,l;
    } transformData;
    transformData.a = someValue;
    transformData.b = someValue;
    transformData.c = someValue;
    transformData.d = 0.0f;
    transformData.e = 0.0f;
    transformData.f = 0.0f;
    transformData.g = 0.0f;
    transformData.h = 0.0f;
    transformData.i = 0.0f;
    transformData.j = *(float*)(context + 0x30);
    transformData.k = *(float*)(context + 0x34);
    transformData.l = *(float*)(context + 0x38);

    // Convert transformData to some format
    char transformBuffer[76];
    convertTransform(transformBuffer, &transformData); // FUN_0044b4e0

    int someVal = (**(code**)(*thisPtr + 0x58))(); // virtual call
    convertString(textBuffer, textBuffer); // FUN_004eacb0 – maybe normalize?
    int newDisplayHandle = createHudDisplay(&transformBuffer, someVal, 0, thisPtr, -1);
    // if old display existed, free it
    if (*displayHandle != 0)
    {
        *(int*)(*displayHandle + 8) = 0;
        *displayHandle = 0;
    }
    *displayHandle = newDisplayHandle;
    if (newDisplayHandle != 0)
    {
        *(int**)(newDisplayHandle + 8) = displayHandle; // set self‑ownership pointer
    }
    return;
}