// FUNC_NAME: CrimeScene::updateFeedback
// Function address: 0x0053c670
// Called on scene updates; checks if the current scene ID (from this+0x10) matches a global scene ID,
// and if corresponding data is available, triggers an audio/feedback effect via FUN_0060add0.

#include <cstdint>

// Global static data (from .data section)
static int32_t DAT_01219900;          // Global scene ID (e.g., active crime scene)
static int32_t DAT_01219924;          // Pointer/flag for associated feedback data
static int32_t DAT_01198e74;          // Another global scene ID
static uint8_t DAT_011f6680[/*?*/];   // Static buffer for sound/VO data

// Called before the main checks (unknown purpose, likely a common update or lock)
void __fastcall FUN_00612a60(void);

// Plays a voiceover, sound effect, or other feedback
// @param sceneId: numeric ID of the current scene
// @param sceneData: pointer to scene-specific data (e.g., audio struct)
// @param audioBuffer: static buffer for audio output
void __fastcall FUN_0060add0(int32_t sceneId, int32_t sceneData, void* audioBuffer);

// __thiscall: this pointer passed in ECX (first parameter in Ghidra's __fastcall)
void __fastcall CrimeScene__updateFeedback(int32_t this) {
    int32_t currentSceneId;

    FUN_00612a60();

    currentSceneId = *(int32_t*)(this + 0x10); // +0x10: currently active scene ID

    // First check: if current scene matches the first global scene AND data is ready
    if ((currentSceneId == DAT_01219900) && (DAT_01219924 != 0)) {
        FUN_0060add0(currentSceneId, DAT_01219924, &DAT_011f6680);
        return;
    }

    // Second check: if current scene matches the second global scene AND local data is ready
    if ((currentSceneId == DAT_01198e74) && (*(int32_t*)(this + 0x270) != 0)) {
        FUN_0060add0(currentSceneId, *(int32_t*)(this + 0x270), &DAT_011f6680);
    }
}