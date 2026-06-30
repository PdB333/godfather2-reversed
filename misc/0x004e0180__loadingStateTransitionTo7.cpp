// FUNC_NAME: loadingStateTransitionTo7
// Called by FUN_0067d090 at 0x0067d090
// Address: 0x004e0180
// Role: Updates global loading state from 4 to 7, performing two intermediate steps.

// Declarations for called subroutines
void processLoadingStep1(void); // 0x004e3f60
void processLoadingStep2(void); // 0x0051d820

// Global loading state indicator (DAT_01194540)
extern int g_loadingState; 

void loadingStateTransitionTo7(void)
{
    g_loadingState = 4;   // Mark loading phase 1 start
    processLoadingStep1(); // e.g., resource loading
    processLoadingStep2(); // e.g., asset finalization
    g_loadingState = 7;   // Mark loading phase complete (ready)
}