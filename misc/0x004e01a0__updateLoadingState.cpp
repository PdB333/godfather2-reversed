// FUNC_NAME: updateLoadingState
// Address: 0x004e01a0
// Role: Advances loading state machine from state 3 to 5, performing intermediate steps.
// Global state variables (likely part of engine globals):
//   g_currentLoadState (DAT_01194540) - current major load phase
//   g_currentLoadSubState (DAT_0119453c) - substep within current phase
// Callees:
//   getLoadResourceHandle() (FUN_004e9fa0)
//   processLoadResource() (FUN_004ea080)
//   finalizeLoadStep() (FUN_0051a7d0)

extern int g_currentLoadState;   // DAT_01194540
extern int g_currentLoadSubState; // DAT_0119453c

extern int getLoadResourceHandle(void);   // FUN_004e9fa0
extern void processLoadResource(int handle); // FUN_004ea080
extern void finalizeLoadStep(void);       // FUN_0051a7d0

void updateLoadingState(void)
{
    int resourceHandle;

    if (g_currentLoadState != 3)
    {
        g_currentLoadSubState = 4;

        resourceHandle = getLoadResourceHandle();
        processLoadResource(resourceHandle);
        finalizeLoadStep();

        g_currentLoadState = 5;
    }
}