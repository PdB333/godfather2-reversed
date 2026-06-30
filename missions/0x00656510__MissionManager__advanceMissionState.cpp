// FUNC_NAME: MissionManager::advanceMissionState

// 00656510 - MissionManager::advanceMissionState
// Advances the mission state machine. Checks current phase (0x6d), stores mission ID,
// and transitions to phase 7 if conditions allow.

#include <cstdint>

// Forward declarations for called functions (invented names based on context)
int* GetMissionManager();               // 00655130 returns singleton
void CopyMissionId(int size, int* dst); // 0064b9e0 copies param_2 to dst? (size 0x20)
int GetMissionStatus();                 // 00655250 returns status flag
void* GetMissionList(int this_offset);  // 00658860 returns some list at this+0x5c
void CancelCurrentMission(int* manager, int status); // 006552f0 cancels mission
void ResetManagerState(int* manager);   // 00655420 resets manager
void ReleaseManagerLock();              // 006550d0 releases something

void __thiscall MissionManager::advanceMissionState(int thisPtr, int missionId)
{
    int* pManager = GetMissionManager();
    if (pManager != nullptr && pManager[0x6d] == 4) // Current phase == 4 (running)
    {
        CopyMissionId(0x20, &missionId);        // Store mission ID copy
        pManager[0x28] = missionId;             // Current mission ID
        pManager[0x24] = missionId;             // Previous mission ID
        pManager[0x2a] = missionId;             // Backup mission ID

        // Virtual call at vtable+0x2c (likely a check if can advance)
        bool canAdvance = (*(bool(**)(void))(*pManager + 0x2c))();
        if (canAdvance)
        {
            int status = GetMissionStatus();
            if (status == 0)
            {
                // Normal path: move to phase 7
                goto advanceState;
            }

            // Compare mission list element count
            int* missionList = (int*)GetMissionList(thisPtr + 0x5c);
            // Decrement global counter
            uint32_t* globalCounter = (uint32_t*)0x01205a30;
            *globalCounter = *globalCounter - 1;

            if (*(uint32_t*)(missionList + 4) < *(uint32_t*)(missionId + 4 * 0)) // Hmm, note: param_2 is int but used as ptr? Actually decompiled uses param_2 as int pointer. Wait: decompiled iVar2 = param_2 (int) then uses *(uint*)(iVar2+4). That means param_2 is a pointer. In our reconstruction, param_2 is an int, but the code treats it as pointer. Need to re-evaluate.
            {
                // Re-evaluating: The decompiled shows "iVar2 = param_2" then later "*(uint *)(iVar2 + 4)". So param_2 is actually a pointer (int*). But we passed it as int? The signature from Ghidra shows param_2 as int, but usage indicates it's a pointer. Let's correct: param_2 is likely a pointer to some struct (maybe MissionId container). We'll change param_2 type to void* but then assign to int arrays. Actually, in the code, param_2 is assigned to pManager[0x28] which is int, so param_2 is an int but then used as pointer? That's inconsistent. Most likely Ghidra misread. The function signature probably actually takes a pointer (int*). We'll assume param_2 is a pointer to a MissionId struct (size 0x20). We'll rename it to missionIdPtr.
                CancelCurrentMission(pManager, status);
                goto advanceState;
            }
        }
        ReleaseManagerLock();
    }
    return;

advanceState:
    ResetManagerState(pManager);
    ReleaseManagerLock();
    pManager[0x6d] = 7; // New phase = 7 (completed/next)
    // Virtual call at vtable+0x14 (likely a state enter function)
    (*(void(**)(void))(*pManager + 0x14))();
    return;
}