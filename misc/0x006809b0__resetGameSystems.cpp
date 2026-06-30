// FUNC_NAME: resetGameSystems
// Function address: 0x006809b0
// Role: Full game system reset/restart. Initializes subsystems, pushes a vtable entry,
// runs per-player reset loops, and invokes shutdown callbacks.

extern void func_006938a0();                    // sub-init A
extern void setStartupFlag(int flag);           // set global startup flag
extern void* g_SomeObject;                      // object with vtable at +4
extern void* g_ManagerBase;                     // base address for manager structures
extern void* g_Callback1;                       // shutdown callback 1
extern void* g_Callback2;                       // shutdown callback 2
extern void* g_Callback3;                       // shutdown callback 3

extern void resetSubsystem_0(int type);         // per-player reset A
extern void resetSubsystem_1(int type);         // per-player reset B

extern void resetRendering();                   // FUN_0043bee0
extern void resetInput();                       // FUN_00439f30
extern void resetAudio();                       // FUN_00426000
extern void resetCamera();                      // FUN_00424950
extern void resetPhysics();                     // FUN_004403f0
extern void resetParticles();                   // FUN_0043c050

void resetGameSystems(void)
{
    int* ppVTableSlot;   // pointer into vtable list
    int i;

    // Initial phase: generic init and flag set
    func_006938a0();
    setStartupFlag(1);

    // Call a virtual method on some object (vtable offset 4)
    (*(void (**)(void))(*(int*)g_SomeObject + 4))();

    // Push a new vtable entry onto a list (stack-like structure)
    // Address at g_ManagerBase+0x14 holds a pointer to the current insertion point.
    ppVTableSlot = (int*)(g_ManagerBase + 0x14);
    **(int**)(g_ManagerBase + 0x14) = (int)&s_ResetVTable; // set new vtable pointer at current slot
    *ppVTableSlot = *ppVTableSlot + 4;                     // advance insertion point by 4 bytes

    // Reset per-player (or per-entity) state 4 times (e.g., 4 players)
    i = 4;
    do {
        resetSubsystem_0(0);
        resetSubsystem_1(0);
        i--;
    } while (i != 0);

    // Core subsystem resets
    resetRendering();
    if (g_Callback1 != (void*)0) {
        (*(void (*)(int))g_Callback1)(1);   // call shutdown callback with arg 1
    }
    if (g_Callback2 != (void*)0) {
        (*(void (*)(int))g_Callback2)(1);
    }
    if (g_Callback3 != (void*)0) {
        (*(void (*)(int))g_Callback3)(1);
    }

    // Second wave of subsystem resets
    resetInput();
    resetAudio();
    resetCamera();

    // Repeat per-player reset (maybe for new state)
    resetSubsystem_0(0);
    resetSubsystem_1(0);

    resetPhysics();
    resetParticles();
}