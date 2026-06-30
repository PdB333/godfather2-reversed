// FUNC_NAME: Job::updateStep
// Address: 0x00707a70
// Role: Handles the main update logic for a job step, including state transitions and entity management.

#include <cstdint>

// Forward declarations for known functions
extern bool isPlayerInGame();                     // FUN_00481660
extern bool isMissionActive();                    // FUN_00481620
extern bool isTargetAvailable();                  // FUN_00481640
extern int getEntityState(int handle);            // FUN_004546d0
extern void releaseHandle(int *handle);           // FUN_00454610
extern int allocateHandle(int *handle);            // FUN_00454570
extern void initEntity(int handle, void *data);   // FUN_00454650
extern void profileBegin(int id);                 // FUN_005403e0
extern void profileEnd(int id);                   // FUN_00540410

// Global function pointer for cleanup callback (pcRam00000248)
extern void (*g_cleanupCallback)(Job *job);

class Job {
public:
    // Vtable layout: offset 0x188 - isStepActive()
    virtual bool isStepActive() = 0; // (**(code **)(*this + 0x188))()

    // Offsets (relative to 'this' pointer)
    int *m_nextStep;      // +0x9e (param_1[0x9e])
    int *m_currentStep;   // +0x9f (param_1[0x9f]) set to m_nextStep
    uint32_t m_flags;     // +0x74 (bit 10 checked)
    int m_handle;         // +0xb3 (entity handle)
    uint8_t m_data[0x16 - 0]; // +0x16 (some data for initEntity)

    // Method called on param_2 (likely a manager)
    virtual bool checkJobType(uint32_t hash) = 0; // (**(code **)(*param_2 + 0x10))(hash)
};

int __thiscall Job::updateStep(Job *this, Job *other) {
    bool stepActive;
    bool playerInGame;
    bool missionActive;
    bool targetAvailable;
    int state;
    int *handlePtr;
    int newHandle;

    stepActive = this->isStepActive();
    if (stepActive) {
        // Copy pending next step to current step
        this->m_currentStep = this->m_nextStep; // param_1[0x9f] = param_1[0x9e]

        // Check flag bit 10 (maybe 'skip normal processing')
        if (!(this->m_flags & (1 << 10))) {
            // Check if this specific job type is active (hash 0x383225a1)
            if (other->checkJobType(0x383225a1)) {
                profileBegin(0xc9); // profiling scope

                playerInGame = isPlayerInGame();
                if (!playerInGame) {
                    // Player not in game: check other conditions
                    missionActive = isMissionActive();
                    if (missionActive) {
                        targetAvailable = isTargetAvailable();
                        if (!targetAvailable) {
                            // No target available - cleanup required
                            g_cleanupCallback(this);
                        }
                        // If target available, do nothing extra
                    }
                    // If mission not active, do nothing
                } else {
                    // Player is in game
                    playerInGame = isPlayerInGame(); // second check? Might be a different function or state check.
                    // Based on pattern: this probably checks another condition
                    if (!playerInGame) { // Actually the code checks if FUN_00481660 returns 0 again?
                        // This branch is tricky; decompiler might have misordered.
                        // The original logic likely was:
                        //   if (firstCheck) { ... } else if (secondCheck) { ... } else { ... }
                        // We'll treat the second call as a distinct check (maybe isPlayerInRange?)
                        // For clarity, we'll call it isPlayerInRange().
                        bool inRange = isTargetAvailable(); // this was in the inner else
                        if (inRange) {
                            handlePtr = &this->m_handle;
                            if (this->m_handle != -1) {
                                state = getEntityState(this->m_handle);
                                if (state == 3) {
                                    releaseHandle(handlePtr);
                                }
                            }
                            if (*handlePtr == -1) {
                                newHandle = allocateHandle(handlePtr);
                                initEntity(newHandle, &this->m_data);
                            }
                        }
                    } else {
                        g_cleanupCallback(this);
                        if (this->m_handle != -1) {
                            releaseHandle(&this->m_handle);
                        }
                    }
                }

                profileEnd(0xc9);
                return 1;
            }
        }
    }
    return 1;
}