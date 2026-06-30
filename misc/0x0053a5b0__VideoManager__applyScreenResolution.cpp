// FUNC_NAME: VideoManager::applyScreenResolution
// Address: 0x0053a5b0
// Sets screen resolution from a mode index and updates projection if needed

struct ParamsBlock {
    int dummy1;
    int dummy2;
    float widthScale;
    float heightScale;
};

struct DisplayModeInfo {
    unsigned short field_2; // +0x2 width? or aspect ratio denominator?
    unsigned short field_4; // +0x4 height? or aspect ratio denominator?
    // ... other fields up to 0x38 bytes
} __attribute__((packed));

extern int g_screenModeIndex;          // DAT_0121b970
extern void* g_pVideoManager;           // DAT_012058e8
extern void* g_videoManagerInstance;    // DAT_0121b740
extern int g_currentDisplayMode;        // DAT_0121b754
extern int g_requestedDisplayMode;      // DAT_0121bbcc
extern int g_someFlag1;                 // DAT_0121bb94
extern int g_someFlag2;                 // DAT_0121bb98
extern float g_screenDiagonal;          // DAT_00e2cd54
extern DisplayModeInfo g_displayModes[0x1000]; // DAT_011a0f28, each 0x38 bytes

void FUN_006063b0(void);  // unknown: maybe reset display state
void FUN_0060add0(int displayMode, int flag, const ParamsBlock* params); // unknown: update projection/viewport

void VideoManager::applyScreenResolution(int in_EAX) // __thiscall but no this used implicitly
{
    g_screenModeIndex = in_EAX;

    if ((g_pVideoManager == &g_videoManagerInstance) && (g_currentDisplayMode == g_requestedDisplayMode))
    {
        if (g_someFlag1 != 0)
        {
            FUN_006063b0();
        }

        if (g_someFlag2 != 0)
        {
            ParamsBlock params;
            params.dummy1 = 0;
            params.dummy2 = 0;

            DisplayModeInfo* pMode = (in_EAX < 0x1000) ? &g_displayModes[in_EAX] : nullptr;
            params.widthScale = g_screenDiagonal / (float)pMode->field_2;

            pMode = (in_EAX < 0x1000) ? &g_displayModes[in_EAX] : nullptr;
            params.heightScale = g_screenDiagonal / (float)pMode->field_4;

            FUN_0060add0(g_currentDisplayMode, g_someFlag2, &params);
        }
    }
}