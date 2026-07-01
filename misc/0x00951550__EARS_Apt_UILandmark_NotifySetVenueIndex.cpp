// Xbox PDB: EARS_Apt_UILandmark_NotifySetVenueIndex
// FUNC_NAME: PauseCityEntry::buildTooltip

// Reconstructed from 0x00951550 - updates tooltip and related strings for a city pause menu business entry
// Struct offsets:
// +0x68: maxEntries (uint)
// +0x64: pEntryArray (int*) - array of IDs/handles
// +0x7c: unknown (int)
// +0x80: currentIndex (uint)
// +0x84: pNameBuffer (char*) - max 0x80
// +0x88: pSubtitleBuffer (char*) - max 0x20
// +0x8c: pTypeBuffer (char*) - max 0x20
// +0x90: pStatusBuffer (char*) - max 0x20
// +0x94: pTooltipBuffer (char*) - max 0x80
// +0x98: tooltipType (int)
// +0x9c: businessValue (int)

#include <cstring>
#include <cmath>

class PauseCityEntry {
public:
    uint maxEntries;            // +0x68
    int* pEntryArray;           // +0x64
    int unknown7c;              // +0x7c
    uint currentIndex;          // +0x80
    char* pNameBuffer;          // +0x84
    char* pSubtitleBuffer;      // +0x88
    char* pTypeBuffer;          // +0x8c
    char* pStatusBuffer;        // +0x90
    char* pTooltipBuffer;       // +0x94
    int tooltipType;            // +0x98
    int businessValue;          // +0x9c

    // Called callees (declared externally):
    // int* getBusinessNode(int entryId);
    // void copyString(char* dest, const char* src, uint maxLen, uint srcLen);
    // const char* getBusinessNameStr();
    // int isBusinessDangerous(int* node);
    // const char* getBusinessDangerString();
    // int getBusinessStatus();
    // void startLocalization();
    // int getGameTimeSeconds();
    // void formatTimeToHoursMinutes(int seconds, char** outStr);
    // void setLocalizationParam(int paramId, const char* str);
    // bool isBusinessOpeningSoon();
    // const char* formatLocalizedString(int localeHandle, char* buffer, char** outStr, const char* formatKey);
    // void endLocalization();
    // const char* getSomethingString(int* outStrPtr, int param);
    // void formatString(int localeHandle, char** outStr, int copyCount);
    // int isBusinessTypeSpecific(int typeId);
    // const char* getBusinessTypeString();

    void buildTooltip();
};

// Forward declarations for callees
extern int* getBusinessNode(int entryId);
extern void copyString(char* dest, const char* src, uint maxLen, uint srcLen);
extern const char* getBusinessNameStr();
extern int isBusinessDangerous(int* node);
extern const char* getBusinessDangerString();
extern int getBusinessStatus();
extern void startLocalization();
extern int getGameTimeSeconds();
extern void formatTimeToHoursMinutes(int seconds, char** outStr);
extern void setLocalizationParam(int paramId, const char* str);
extern bool isBusinessOpeningSoon();
extern const char* formatLocalizedString(int localeHandle, char* buffer, char** outStr, const char* formatKey);
extern void endLocalization();
extern const char* getSomethingString(int* outStrPtr, int param);
extern void formatString(int localeHandle, char** outStr, int copyCount);
extern int isBusinessTypeSpecific(int typeId);
extern const char* getBusinessTypeString();

void PauseCityEntry::buildTooltip() {
    uint index;
    float fVar2;
    char cVar3;
    int* node;
    int4* puVar5;
    const char* strSrc;
    int iVar7;
    uint uVar8;
    const char** ppStr;
    const char* tooltipKey;
    char* timeStr;

    // Initialize all string buffers and status integers
    unknown7c = 0;
    *pNameBuffer = 0;
    *pSubtitleBuffer = 0;
    *pTypeBuffer = 0;
    *pStatusBuffer = 0;
    *pTooltipBuffer = 0;
    tooltipType = 0;
    businessValue = 0;

    index = currentIndex;
    if (index == 0xFFFFFFFF) {
        return;
    }
    if (maxEntries <= index) {
        return;
    }

    // Get business node from entry array
    node = getBusinessNode(pEntryArray[index]);
    if (node == 0) {
        return;
    }

    // Get business name and copy to name buffer
    puVar5 = (int4*)getBusinessNameStr();
    strSrc = (const char*)*puVar5;
    if (strSrc == 0) {
        strSrc = "(null)";
    }
    copyString(pNameBuffer, strSrc, 0x80, puVar5[1]);

    // Check if business is dangerous and copy subtitle
    iVar7 = isBusinessDangerous((int*)(node[0x48]));
    if (iVar7 != 0) {
        puVar5 = (int4*)getBusinessDangerString();
        strSrc = (const char*)*puVar5;
        if (strSrc == 0) {
            strSrc = "(null)";
        }
        copyString(pSubtitleBuffer, strSrc, 0x20, puVar5[1]);
    }

    int businessStatus = getBusinessStatus(); // Returns 0=closed,1=open,2=bombed,3,4
    if (businessStatus == 0) {
        if (node[0xc4] != 0) { // node+0xc4 is some flag
            return;
        }
        // Check if business is not closed for good (bit 12)
        uint flags = (uint)node[0x34];
        if ((~(flags >> 0xc) & 1) != 0) {
            // Check if business type is bombed indicator
            if (node[0x40] == 0x637b907) {
                tooltipType = (node[0xfc] != 0) + 2;
            }
            else if ((node[0xfc] == 0) && (node[0x174] == 0) && ((flags >> 0x1c & 1) == 0)) {
                tooltipType = 1;
            }
        }
        goto handleStatusTooltip;
    }

    if (node[0xc4] != 0) {
        return;
    }

    // Build tooltip with opening time
    int localeHandle = 0x12234a4; // Some locale handle
    startLocalization();

    char* outStr = 0;
    int outLen = 0;
    void (*freeFunc)(void*) = 0;

    // Get current game time in seconds and format as hours:minutes
    iVar7 = getGameTimeSeconds();
    if (iVar7 < 0) {
        fVar2 = (float)iVar7 + 0.5f; // Adjust for rounding
    } else {
        fVar2 = (float)iVar7;
    }
    // Multiply by some factor from global (likely time scale)
    extern float gTimeScale;
    fVar2 *= gTimeScale;
    int totalSeconds = (int)(fVar2 + 0.5f); // rounding
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    formatTimeToHoursMinutes(hours * 3600 + minutes * 60, &timeStr); // Pass seconds to format
    if (timeStr == 0) {
        timeStr = "(null)";
    }
    setLocalizationParam(0x6e, timeStr); // Set time string param

    cVar3 = isBusinessOpeningSoon();

    if (cVar3 == 0) {
        if (businessStatus == 2 || businessStatus == 3 || businessStatus == 4) {
            tooltipKey = "$pause_city_tooltip_bombed";
        } else if (businessStatus == 1) {
            tooltipKey = "$pause_city_tooltip_closed";
        } else {
            tooltipKey = 0;
        }
    } else {
        tooltipKey = "$pause_city_tooltip_openingsoon";
    }

    if (tooltipKey != 0) {
        formatLocalizedString(localeHandle, (char*)alloca(4112), &outStr, tooltipKey);
    }

    strSrc = outStr;
    if (outStr == 0) {
        strSrc = "(null)";
    }
    copyString(pTooltipBuffer, strSrc, 0x80, outLen);

    if (timeStr != 0) {
        (*freeFunc)(timeStr);
    }
    if (outStr != 0) {
        (*freeFunc)(outStr);
    }
    endLocalization();

handleStatusTooltip:
    // Build status string
    const char* statusStr = 0;
    int statusLen = 0;
    formatString(localeHandle, &statusStr, 1);
    strSrc = statusStr;
    if (statusStr == 0) {
        strSrc = "(null)";
    }
    copyString(pStatusBuffer, strSrc, 0x20, statusLen);

    // Store business value from node
    businessValue = node[0x68];

    // Check business type and copy type string if needed
    int typeCheck = isBusinessTypeSpecific(node[0x40]);
    if (typeCheck != 0) {
        puVar5 = (int4*)getBusinessTypeString();
        strSrc = (const char*)*puVar5;
        if (strSrc == 0) {
            strSrc = "(null)";
        }
        copyString(pTypeBuffer, strSrc, 0x20, puVar5[1]);
    }

    if (statusStr != 0) {
        (*freeFunc)(statusStr);
    }
}