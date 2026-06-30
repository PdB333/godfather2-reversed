// FUNC_NAME: StreamManager::updateStreams
// Address: 0x0060cde0
// Role: Main update loop for audio/streaming subsystem. Processes current stream state,
// activates/pauses streams, advances position.

// Forward declarations
struct StreamInfo;
class StreamManager;

// Global pointers (inferred from data references)
extern StreamInfo* g_pCurrentStream;       // DAT_0120584c
extern StreamManager* g_pStreamManager;    // DAT_01205840
extern int g_streamPosition;               // DAT_01205844
extern int g_someTarget;                   // DAT_01205848
extern int g_currentTarget;                // DAT_0120583c
extern class AudioSystem* g_pAudioSystem;  // DAT_01205750
extern int g_streamActiveFlags[];          // DAT_011da7f0
extern int g_streamPausedFlags[];          // DAT_011da7f4

// StreamInfo structure offsets (relative to g_pCurrentStream)
// +0x00: unknown (set to 0)
// +0x04: streamState (int)
// +0x08: streamData (int)
// +0x0C: streamSomething (int)
// +0x10: streamIncrement (int)
// +0x20: streamIndex (int)

// External functions
void FUN_0060c820(int streamIndex, StreamManager* manager, int something, int position);
void FUN_006102c0(void);
int FUN_0060c9d0(void);

// Virtual function offsets for AudioSystem (g_pAudioSystem)
const int kAudioSystem_Reset = 0x30;          // (code **)(*obj + 0x30)
const int kAudioSystem_ProcessState = 0x144;  // (code **)(*obj + 0x144)
const int kAudioSystem_SubmitData = 0x148;    // (code **)(*obj + 0x148)
const int kAudioSystem_ActivateStream = 0x198;// (code **)(*obj + 0x198)
const int kAudioSystem_SetTarget = 0x1A0;     // (code **)(*obj + 0x1A0)
const int kAudioSystem_PauseStream = 400;     // (code **)(*obj + 400) = 0x190

void StreamManager::updateStreams(void)
{
    int streamState;
    int streamData;
    int streamIndex;
    int uVar6;

    // Reset current stream's first field to 0
    *g_pCurrentStream = 0;

    // Call virtual reset on stream manager
    (*(void (**)(StreamManager*))(*g_pStreamManager + kAudioSystem_Reset))(g_pStreamManager);

    // Process stream with given index, manager, something, and current position
    FUN_0060c820(
        *(int*)(g_pCurrentStream + 0x20),  // streamIndex
        g_pStreamManager,
        *(int*)(g_pCurrentStream + 0x0C),  // streamSomething
        g_streamPosition
    );

    // Update audio system (mix, etc.)
    FUN_006102c0();

    streamState = *(int*)(g_pCurrentStream + 0x04);
    if (streamState == 0x0D) // 13 = some specific state (e.g., "ready to submit")
    {
        streamData = *(int*)(g_pCurrentStream + 0x08);
        if (g_currentTarget != *g_someTarget)
        {
            // Set new target via virtual call
            (*(void (**)(AudioSystem*, int))(*g_pAudioSystem + kAudioSystem_SetTarget))(g_pAudioSystem, *g_someTarget);
            g_currentTarget = *g_someTarget;
        }
        // Submit data: (4, 0, 0, streamData, 0, (streamData*2)>>2)
        (*(void (**)(AudioSystem*, int, int, int, int, int, uint))(*g_pAudioSystem + kAudioSystem_SubmitData))(
            g_pAudioSystem,
            4,
            0,
            0,
            streamData,
            0,
            (uint)(streamData * 2) >> 2
        );
    }
    else
    {
        uVar6 = FUN_0060c9d0();
        // Process state with uVar6
        (*(void (**)(AudioSystem*, int, int, int))(*g_pAudioSystem + kAudioSystem_ProcessState))(
            g_pAudioSystem,
            streamState,
            0,
            uVar6
        );
    }

    streamIndex = *(int*)(g_pCurrentStream + 0x20);
    if (g_streamActiveFlags[streamIndex] != 1)
    {
        // Activate stream
        (*(void (**)(AudioSystem*, int, int))(*g_pAudioSystem + kAudioSystem_ActivateStream))(g_pAudioSystem, streamIndex, 1);
        g_streamActiveFlags[streamIndex] = 1;
    }

    if (g_streamPausedFlags[streamIndex] != 0)
    {
        // Pause stream (set to 0)
        (*(void (**)(AudioSystem*, int, int, int, int))(*g_pAudioSystem + kAudioSystem_PauseStream))(g_pAudioSystem, streamIndex, 0, 0, 0);
        g_streamPausedFlags[streamIndex] = 0;
        g_streamPosition += *(int*)(g_pCurrentStream + 0x10); // streamIncrement
        return;
    }

    g_streamPosition += *(int*)(g_pCurrentStream + 0x10); // streamIncrement
    return;
}