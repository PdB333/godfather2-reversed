// FUNC_NAME: DisplayMode::selectBestMatch
// Address: 0x006073e0
// This function selects the largest display mode (width, height, refresh rate) that fits within the user-specified maximum bounds.
// It queries the graphics device for a list of supported modes, then picks the highest resolution/refresh.
// The resulting mode is stored in the DisplayMode structure at 'this'.
// Also updates global aspect ratio (DAT_01205878) and uses global DAT_012058b4 (maybe default refresh).

#include <cstdint>
#include <cstring>

// Forward declarations of called subroutines (EA EARS engine internal)
bool videoDeviceEnumerateModes(void* buffer, void* config, uint32_t deviceHandle, DisplayMode* thisPtr, bool fullscreen); // FUN_0060ea60
void processModeList(uint32_t* listPtr); // FUN_006099f0 - processes the mode list (maybe sorts)
void freeModeList(uint32_t* modeList); // FUN_009c8f10 - frees mode list memory
void finalizeModeSelection(); // FUN_00609aa0 - finalizes selection (release lock etc.)

// External globals (likely in .data section)
extern uint32_t DAT_01205878; // aspect ratio computed as bestWidth/bestHeight
extern uint32_t DAT_012058b4; // some global display parameter

class DisplayMode {
public:
    // Member fields (offset from 'this')
    uint32_t width;      // +0x00
    uint32_t height;     // +0x04
    uint32_t depth;      // +0x08 (bit depth or some other mode attribute)
    uint32_t field_0C;   // +0x0C (always 1)
    uint32_t field_10;   // +0x10 (always 0)
    uint32_t field_14;   // +0x14 (always 0)
    uint32_t field_18;   // +0x18 (always 1)
    uint32_t field_1C;   // +0x1C (copied from DAT_012058b4)
    uint32_t field_20;   // +0x20 (bFullscreen flag)
    uint32_t field_24;   // +0x24 (0)
    uint32_t field_28;   // +0x28 (0)
    uint32_t field_2C;   // +0x2C (0)
    uint32_t field_30;   // +0x30 (refresh rate, or 0 if windowed)
    uint32_t field_34;   // +0x34 (flags: 0x80000000 for windowed, else vsync/other)

    // __thiscall: this pointer in ecx
    bool __fastcall selectBestMatch(uint32_t deviceHandle, uint16_t* pMaxWidth, uint16_t* pMaxHeight, uint16_t* pMaxRefresh,
                                    bool bFullscreen, bool bVsync);
};

bool __fastcall DisplayMode::selectBestMatch(uint32_t deviceHandle, uint16_t* pMaxWidth, uint16_t* pMaxHeight, uint16_t* pMaxRefresh,
                                             bool bFullscreen, bool bVsync)
{
    // Local variables
    uint32_t bestWidth = 0;
    uint32_t bestHeight = 0;
    uint32_t bestRefresh = 0;
    uint32_t* modeList = nullptr;      // pointer to array of mode entries (each 4 uints)
    int32_t modeCount = 0;              // number of modes in the list
    uint32_t maxWidth, maxHeight, maxRefresh; // copies of user-specified limits

    // Temporary buffer for mode enumeration (size 36 bytes)
    char buffer[36] = {0};

    // Call enumeration routine: fills buffer with mode data and returns success bool
    if (!videoDeviceEnumerateModes(buffer, (void*)0x0120575c, deviceHandle, this, bFullscreen))
    {
        finalizeModeSelection();
        return false;
    }

    // Clear the DisplayMode structure (0x38 = 56 bytes -> 14 uints)
    memset(this, 0, sizeof(uint32_t) * 14);

    // Extract some value from the enumeration result (offset +4 in the returned struct)
    uint32_t someAttribute = *(uint32_t*)(buffer + 4); // possibly a mode ID or depth

    // Process the mode list (sort or filter)
    // buffer + 8 is likely the start of the mode list array
    processModeList((uint32_t*)(buffer + 8)); // FUN_006099f0

    if (!bFullscreen)
    {
        // Mode filtering for windowed mode: clamp user bounds to the actual maximums available
        // Retrieve mode list bounds (assumed stored in variables set by enumeration)
        // Note: The decompiler could not show assignments to modeList and modeCount from the buffer,
        // but they are used below. We infer they are set by the enumeration function (via the buffer).
        // For the code to work, modeList must point to the first mode entry and modeCount is the number of entries.
        // Each mode entry is 4 uints: width, height, refresh, flags.

        // The following uses local_15c and local_158 which are likely modeList and modeCount.
        // Since we cannot see the exact assignments, we assume they are extracted from the buffer.

        // For clarity, we'll write the logic assuming modeList and modeCount are already known.
        // The decompiled code shows:
        //   uVar5 = *param_3; // maxWidth
        //   if ( (uint)uVar5 < *modeList ) uVar5 = (ushort)*modeList;
        //   *param_3 = uVar5; // pMaxWidth = max(original, min available width)
        //   similarly for height and refresh.
        // This ensures the user-specified bounds are at least as large as the smallest mode.

        uint16_t tempWidth = *pMaxWidth;
        if ((uint32_t)tempWidth < modeList[0]) {
            tempWidth = (uint16_t)modeList[0];
        }
        *pMaxWidth = tempWidth;

        uint16_t tempHeight = *pMaxHeight;
        if ((uint32_t)tempHeight < modeList[1]) {
            tempHeight = (uint16_t)modeList[1];
        }
        *pMaxHeight = tempHeight;

        uint16_t tempRefresh = *pMaxRefresh;
        uint32_t refreshLimit = (uint32_t)*pMaxRefresh;
        if (refreshLimit < modeList[2]) {
            tempRefresh = (uint16_t)modeList[2];
        }
        *pMaxRefresh = tempRefresh;

        maxWidth = (uint32_t)*pMaxWidth;
        maxHeight = (uint32_t)*pMaxHeight;
        maxRefresh = (uint32_t)*pMaxRefresh;

        // Now iterate through all modes to find the largest that fits within (maxWidth, maxHeight, maxRefresh)
        if (modeCount != 0)
        {
            uint32_t* currentMode = modeList;  // pointer to first mode entry
            for (int32_t i = 0; i < modeCount; i++)
            {
                uint32_t modeW = currentMode[0];
                uint32_t modeH = currentMode[1];
                uint32_t modeR = currentMode[2];

                // Candidate must satisfy: current width within range, height within range, refresh <= maxRefresh
                if ((bestWidth <= modeW) && (modeW <= maxWidth) &&
                    (bestHeight <= modeH) && (modeH <= maxHeight) &&
                    (modeR <= (maxRefresh & 0xFFFF)))
                {
                    bestWidth = modeW;
                    bestHeight = modeH;
                    bestRefresh = modeR;
                }
                currentMode += 4; // each mode entry is 4 uints
            }
        }

        // Write back the best mode's dimensions into the user pointers
        *pMaxWidth = (uint16_t)bestWidth;
        *pMaxHeight = (uint16_t)bestHeight;
        *pMaxRefresh = (uint16_t)bestRefresh;

        // Update global aspect ratio
        DAT_01205878 = (float)bestWidth / (float)bestHeight;
    }

    // Fill the DisplayMode structure with the selected values
    this->width = (uint32_t)*pMaxWidth;
    this->height = (uint32_t)*pMaxHeight;
    this->depth = someAttribute;  // offset +0x08 (from earlier)
    this->field_0C = 1;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 1;
    this->field_1C = DAT_012058b4;
    this->field_20 = (uint32_t)bFullscreen;
    this->field_24 = 0;
    this->field_28 = 0;
    this->field_2C = 0;

    if (!bFullscreen)
    {
        // Windowed mode
        this->field_34 = 0x80000000;   // flag indicating windowed
        this->field_30 = 0;
    }
    else
    {
        this->field_30 = (uint32_t)*pMaxRefresh;  // selected refresh rate
        if (bVsync == false)
        {
            // Copy flag from the mode entry (bit 31 of field_34 from mode list)
            this->field_34 = (uint32_t)(modeList != nullptr ? (modeList[3] & 0x80000000) : 0);
        }
        else
        {
            // If vsync enabled, check the mode's flag bit 1
            uint32_t flags = (modeList != nullptr ? modeList[3] : 0);
            if ((flags & 2) == 0)
            {
                this->field_34 = flags & 1;
            }
            else
            {
                this->field_34 = 2;
            }
        }
    }

    // Free the mode list if it was allocated
    if (modeList != nullptr)
    {
        freeModeList(modeList);
    }

    finalizeModeSelection();
    return true;
}