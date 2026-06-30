// FUNC_NAME: GameStateManager::shutdown

class GameStateManager {
public:
    // Vtable pointer at +0x00
    // Offset 0x3E: byte flag (bSubsystemLoaded)
    // Offset 0x4E (0x138): pointer to object A (someObjectA)
    // Offset 0x51 (0x144): function pointer for object A (release callback)
    // Offset 0x52 (0x148): pointer to object B (someObjectB)
    // Offset 0x55 (0x154): function pointer for object B (release callback)
    // Offset 0x5A (0x168): handle from engine (engineStateHandle)
    // Offset 0x5B (0x16C): engine state ID (set to 2)
    // Offset 0x73 (0x1CC): resource pointer (resourceToRelease)
    // Offset 0x74 (0x1D0): cleared after release
    // Offset 0x75 (0x1D4): cleared after release

    void __thiscall shutdown();
};

// Global variables (from context)
extern int DAT_01143360; // Engine running flag
extern char* DAT_01206940; // Debug string
extern void** DAT_01223518; // Global manager vtable pointer
extern int DAT_00e2e4c4; // Shutdown request flag

// Forward declarations of engine functions (named descriptively)
void debugPrint(const char* msg);
void stopEngineComponent(int componentId);
void engineUpdate();
void engineStep();
unsigned int getEngineStateHandle();
void setEngineStateId(int id);
int getGameLoopState();
void processEngineMessages(void*& messageOut);
void updateEngineState();
int isShutdownRequested();
void setShutdownRequested();
void shutdownAudio();
void shutdownInput();
void shutdownGraphics();

void __thiscall GameStateManager::shutdown() {
    // Set vtable to base cleanup vtable
    *(void**)this = (void*)&PTR_FUN_00e31a94;

    // If subsystem loaded flag is set, print debug
    if (*(char*)((int)this + 0x3E) != 0) {
        debugPrint(&DAT_01206940);
    }

    // If engine is running
    if (DAT_01143360 != 0) {
        stopEngineComponent(0);

        // Perform engine update steps in phases
        engineUpdate();
        engineStep();
        for (int i = 0; i < 8; ++i) {
            engineStep();
        }
        for (int i = 0; i < 2; ++i) {
            engineStep();
        }
        engineStep();

        // Store engine state handle and set state ID
        *(unsigned int*)((int)this + 0x168) = getEngineStateHandle();
        *(int*)((int)this + 0x16C) = 2;

        // Loop until game loop state is idle or menu
        int loopState;
        while (true) {
            loopState = getGameLoopState();
            if (loopState == 0 || loopState == 3) break;

            // Process engine messages (pass dummy pointer)
            void* messagePtr = (void*)0x1;
            processEngineMessages(messagePtr);
            updateEngineState();
        }

        // Release resource if allocated
        if (*(void**)((int)this + 0x1CC) != 0) {
            if (*(int*)(DAT_01223518 + 4) != 0) {
                // Call global object's resource release method (vtable slot +4)
                (*(void (__thiscall**)(void*, int))(* (*(int**)(DAT_01223518 + 4) + 4)))(
                    *(void**)((int)this + 0x1CC), 0);
            }
            *(void**)((int)this + 0x1CC) = 0;
            *(int*)((int)this + 0x1D0) = 0;
            *(int*)((int)this + 0x1D4) = 0;
        }
    }

    // Check global shutdown flag
    if (isShutdownRequested() == 0) {
        setShutdownRequested();
    }

    shutdownAudio();

    // Release object B via callback function
    if (*(void**)((int)this + 0x148) != 0) {
        void* objB = *(void**)((int)this + 0x148);
        void (*releaseB)(void*) = *(void (__thiscall**)(void*))((int)this + 0x154);
        releaseB(objB);
    }

    // Release object A via callback function
    if (*(void**)((int)this + 0x138) != 0) {
        void* objA = *(void**)((int)this + 0x138);
        void (*releaseA)(void*) = *(void (__thiscall**)(void*))((int)this + 0x144);
        releaseA(objA);
    }

    shutdownInput();
    shutdownGraphics();
}