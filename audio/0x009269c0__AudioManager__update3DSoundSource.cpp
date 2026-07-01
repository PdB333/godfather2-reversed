// FUNC_NAME: AudioManager::update3DSoundSource
void __thiscall AudioManager::update3DSoundSource(void)
{
    // Local struct for 3D audio parameters (32 bytes)
    struct Audio3DParams {
        float posX;          // +0x00
        float posY;          // +0x04
        int   unk0;          // +0x08
        float deltaTime;     // +0x0C
        float offsetX;       // +0x10
        float offsetY;       // +0x14
        int   unk1;          // +0x18
        float deltaTime2;    // +0x1C
    };

    float srcPosX = *(float *)(this + 0x3AC);  // m_soundSourceWorldX
    float srcPosY = *(float *)(this + 0x3B0);  // m_soundSourceWorldY
    int trackIndex = *(int *)(this + 0x3D0);   // m_audioTrackId

    // --- Configure audio channels for dialog (channel index 7) ---
    if (g_audioChannelLeft < 7)
        g_audioChannelLeft = 7;
    if (7 < g_audioChannelRight)
        g_audioChannelRight = 7;
    g_audioChannelEnable7 = 0;

    // --- Channel 14 ---
    if (g_audioChannelLeft < 0xE)
        g_audioChannelLeft = 0xE;
    if (0xE < g_audioChannelRight)
        g_audioChannelRight = 0xE;
    g_audioChannelEnable14 = 0;

    // --- Channel 27 ---
    if (g_audioChannelLeft < 0x1B)
        g_audioChannelLeft = 0x1B;
    if (0x1B < g_audioChannelRight)
        g_audioChannelRight = 0x1B;
    g_audioChannelEnable27 = 1;

    // Set sub-mix group parameters (1=group1, 5=group5, 6=group6)
    setAudioSubmixGroup(1, 5, 6);

    // --- Channel 25 ---
    if (g_audioChannelLeft < 0x19)
        g_audioChannelLeft = 0x19;
    if (0x19 < g_audioChannelRight)
        g_audioChannelRight = 0x19;
    g_audioChannelEnable25 = 7;  // not boolean, could be a count

    // --- Channel 24 ---
    if (g_audioChannelLeft < 0x18)
        g_audioChannelLeft = 0x18;
    if (0x18 < g_audioChannelRight)
        g_audioChannelRight = 0x18;
    g_audioChannelEnable24 = 0;

    // --- Channel 15 ---
    if (g_audioChannelLeft < 0xF)
        g_audioChannelLeft = 0xF;
    if (0xF < g_audioChannelRight)
        g_audioChannelRight = 0xF;
    g_audioChannel15Flag = 0;

    // Copy default audio sample parameters (16 bytes)
    g_audioDefaultParams[0] = g_audioDefaultSourceParams[0];
    g_audioDefaultParams[1] = g_audioDefaultSourceParams[1];
    g_audioDefaultParams[2] = g_audioDefaultSourceParams[2];
    g_audioDefaultParams[3] = g_audioDefaultSourceParams[3];

    // Compute local 3D audio parameters based on source position and global screen ratios
    Audio3DParams params;
    params.posX = srcPosX + (g_deltaTime / (float)g_screenWidth) * g_audioPosOffsetX0;
    params.posY = srcPosY + (g_deltaTime / (float)g_screenHeight) * g_audioPosOffsetY0;
    params.offsetX = params.posX + (g_deltaTime / (float)g_screenWidth) * g_audioPosOffsetX1;
    params.offsetY = params.posY + (g_deltaTime / (float)g_screenHeight) * g_audioPosOffsetY1;
    params.unk0 = 0;
    params.deltaTime = g_deltaTime;
    params.unk1 = 0;
    params.deltaTime2 = g_deltaTime;

    // Determine custom parameters pointer based on track index
    void *pCustomParams = &g_audioCustomParamsTable;
    if (trackIndex == 0 || trackIndex == -1) {
        pCustomParams = nullptr;
        trackIndex = g_audioCurrentTrackIndex;
    }
    g_audioCurrentTrackIndex = trackIndex;

    // Apply the 3D sound parameters (pass params, flag 0, optional custom data)
    apply3DAudioParams(&params, 0, pCustomParams);

    // --- Tear down channel configuration ---
    // Channel 27 disabled
    if (g_audioChannelLeft < 0x1B)
        g_audioChannelLeft = 0x1B;
    if (0x1B < g_audioChannelRight)
        g_audioChannelRight = 0x1B;
    g_audioChannelEnable27 = 0;

    setAudioSubmixGroup(1, 5, 6);

    // Channel 25
    if (g_audioChannelLeft < 0x19)
        g_audioChannelLeft = 0x19;
    if (0x19 < g_audioChannelRight)
        g_audioChannelRight = 0x19;
    g_audioChannelEnable25 = 7;

    // Channel 24
    if (g_audioChannelLeft < 0x18)
        g_audioChannelLeft = 0x18;
    if (0x18 < g_audioChannelRight)
        g_audioChannelRight = 0x18;
    g_audioChannelEnable24 = 0;

    // Channel 15
    if (g_audioChannelLeft < 0xF)
        g_audioChannelLeft = 0xF;
    if (0xF < g_audioChannelRight)
        g_audioChannelRight = 0xF;
    g_audioChannelEnable15 = 0;

    // Channel 7 enabled
    if (g_audioChannelLeft < 7)
        g_audioChannelLeft = 7;
    if (7 < g_audioChannelRight)
        g_audioChannelRight = 7;
    g_audioChannelEnable7 = 1;

    // Channel 14 enabled
    if (g_audioChannelLeft < 0xE)
        g_audioChannelLeft = 0xE;
    g_audioChannelEnable14 = 1;
    if (0xE < g_audioChannelRight)
        g_audioChannelRight = 0xE;

}

// Global variables (declared extern in header, defined elsewhere)
extern int g_audioChannelLeft;        // DAT_012058d0
extern int g_audioChannelRight;       // DAT_00f15988
extern int g_audioChannelEnable7;     // _DAT_011f39f4
extern int g_audioChannelEnable14;    // _DAT_011f3a10
extern int g_audioChannelEnable27;    // _DAT_011f3a44
extern int g_audioChannelEnable25;    // _DAT_011f3a3c
extern int g_audioChannelEnable24;    // _DAT_011f3a38
extern int g_audioChannelEnable15;    // _DAT_011f3a14
extern int g_audioChannel15Flag;      // DAT_011f4234

extern int g_audioDefaultParams[4];   // DAT_011f4220 - DAT_011f422c
extern int g_audioDefaultSourceParams[4]; // _DAT_00e56580+ (16 bytes)

extern float g_deltaTime;             // _DAT_00d5780c
extern int g_screenWidth;             // DAT_0120587c
extern int g_screenHeight;            // DAT_01205880
extern float g_audioPosOffsetX0;      // _DAT_00e56578
extern float g_audioPosOffsetY0;      // _DAT_00e5657c
extern float g_audioPosOffsetX1;      // _DAT_00e56570
extern float g_audioPosOffsetY1;      // _DAT_00e56574
extern int g_audioCurrentTrackIndex;  // DAT_011f4230
extern char g_audioCustomParamsTable[]; // DAT_00e56550 (larger data block)

// Called subroutines (defined elsewhere)
extern void setAudioSubmixGroup(int a, int b, int c);  // FUN_00417cf0
extern void apply3DAudioParams(void *params, int flag, void *custom); // FUN_006103f0