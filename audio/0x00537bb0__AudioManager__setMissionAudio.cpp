// FUNC_NAME: AudioManager::setMissionAudio
// Function address: 0x00537bb0
// Role: Sets three audio IDs for a mission scenario using global sound bank structures (offsets +0x08, +0x0c, +0x10)
//       and conditionally updates a second audio manager using a fallback bank.

// Forward declarations of callees
void __cdecl setAudioById(void* mgr, int audioId);                // FUN_0060add0  (2 args)
void __cdecl setAudioByIdWithData(void* mgr, int audioId, int extra); // FUN_0060add0 (3 args)
void __cdecl setAudioByPriority(void* mgr, int audioId, int priority); // FUN_0060aa90

// Global pointers (from data segments)
extern void* g_pAudioManager1;        // 0x0121a394
extern void* g_pAudioManager2;        // 0x0121a390
extern int* g_pSoundBank1;            // 0x0121b0a8  (contains offsets +0x08, +0x0c, +0x10)
extern void* g_pFallbackBank1;        // 0x0121b638  (non-zero => use offset +0x1c)
extern void* g_pFallbackBank2;        // 0x0121b63c  (otherwise use offset +0x14)

void __cdecl setMissionAudio(int param_1, int param_2) {
    // Set audio ID from soundBank1+0x0c (2-arg call)
    setAudioById(g_pAudioManager1, *(g_pSoundBank1 + 0x0c / 4)); // offset 0x0c

    // Set audio ID from soundBank1+0x10 (3-arg call with param_2)
    setAudioByIdWithData(g_pAudioManager1, *(g_pSoundBank1 + 0x10 / 4), param_2);

    // Set audio ID from soundBank1+0x08 (3-arg call with param_1)
    setAudioByPriority(g_pAudioManager1, *(g_pSoundBank1 + 0x08 / 4), param_1);

    // Choose fallback bank and set audio ID on second manager
    if (g_pFallbackBank1 != 0) {
        setAudioById(g_pAudioManager2, *(int*)((char*)g_pFallbackBank1 + 0x1c));
    } else {
        setAudioById(g_pAudioManager2, *(int*)((char*)g_pFallbackBank2 + 0x14));
    }
}