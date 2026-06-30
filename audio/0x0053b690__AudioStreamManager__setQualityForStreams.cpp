// FUNC_NAME: AudioStreamManager::setQualityForStreams

void __fastcall setStreamQuality(int unkArg, int channelIndex, char useHighQuality)
{
    // Selects between high and low quality audio buffers for active streams.
    // Two stream groups: first group uses g_streamIndex1 (stride 0x38), second group uses g_streamIndex2 (stride 0x3c).
    // For each active stream, calls assignPrimaryBuffer() or assignSecondaryBuffer() with the appropriate buffer pointer.

    int streamIndex1 = g_streamIndex1();     // DAT_01125388
    int streamIndex2 = g_streamIndex2();     // DAT_01125389
    int *base1 = g_streamBase1;             // DAT_011252e8
    int *base2 = g_streamBase2;             // DAT_011252ec

    // First group, first stream
    int *primaryStreamPtr = (int *)(g_primaryStreamArray + streamIndex1 * 0x38); // DAT_01125408
    if (primaryStreamPtr != 0) {
        char *buffer = useHighQuality ? (char *)g_highQualityBuf1 : (char *)g_lowQualityBuf1;
        assignPrimaryBuffer(base1, (int)primaryStreamPtr, channelIndex);
    }

    // First group, second stream
    int *secondaryStreamPtr = (int *)(g_secondaryStreamArray + streamIndex1 * 0x38); // DAT_01125424
    if (secondaryStreamPtr != 0) {
        char *buffer = useHighQuality ? (char *)g_highQualityBuf1 : (char *)g_lowQualityBuf1;
        assignSecondaryBuffer(base1, (int)secondaryStreamPtr, buffer);
    }

    // Second group, first stream
    int *thirdStreamPtr = (int *)(g_thirdStreamArray + streamIndex2 * 0x3c); // DAT_011254cc
    if (thirdStreamPtr != 0) {
        char *buffer = (g_globalQualityFlag != 0) ? (char *)g_highQualityBuf2 : (char *)g_lowQualityBuf2; // DAT_01163840
        assignSecondaryBuffer(base2, (int)thirdStreamPtr, buffer);
    }

    // Second group, second stream
    int *fourthStreamPtr = (int *)(g_fourthStreamArray + streamIndex2 * 0x3c); // DAT_011254d0
    if (fourthStreamPtr != 0) {
        char *buffer = (g_globalQualityFlag != 0) ? (char *)g_highQualityBuf3 : (char *)g_lowQualityBuf3;
        assignPrimaryBuffer(base2, (int)fourthStreamPtr, buffer);
    }
}

// Extern global variables and helper functions (addresses from Ghidra)
// These would be defined elsewhere in the binary
extern int g_streamIndex1;          // DAT_01125388
extern int g_streamIndex2;          // DAT_01125389
extern int *g_streamBase1;          // DAT_011252e8
extern int *g_streamBase2;          // DAT_011252ec
extern int g_primaryStreamArray[];   // DAT_01125408, stride 0x38
extern int g_secondaryStreamArray[]; // DAT_01125424, stride 0x38
extern int g_thirdStreamArray[];     // DAT_011254cc, stride 0x3c
extern int g_fourthStreamArray[];    // DAT_011254d0, stride 0x3c
extern char g_highQualityBuf1[];     // DAT_011280d0
extern char g_lowQualityBuf1[];      // DAT_00e2e770
extern char g_highQualityBuf2[];     // DAT_01163810
extern char g_lowQualityBuf2[];      // DAT_00e2e760
extern char g_highQualityBuf3[];     // DAT_011637d0
extern char g_lowQualityBuf3[];      // DAT_00e2e720
extern char g_globalQualityFlag;     // DAT_01163840

// Helper functions (addresses from callees)
// Likely: void assignPrimaryBuffer(int *base, int streamPtr, int channelIndex);
//         void assignSecondaryBuffer(int *base, int streamPtr, char *buffer);
extern void assignPrimaryBuffer(int *base, int streamPtr, int channelIndex);  // FUN_0060b020
extern void assignSecondaryBuffer(int *base, int streamPtr, char *buffer);    // FUN_0060add0