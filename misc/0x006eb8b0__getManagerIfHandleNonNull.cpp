// FUNC_NAME: getManagerIfHandleNonNull
// Function at 0x006eb8b0: Returns a global manager pointer (obtained via FUN_0043b870 from global DAT_0112af58) if the given handle is non-zero; otherwise returns 0.
// param_1: handle (likely a pointer or index) to validate
// return: result of manager access or null

int getManagerIfHandleNonNull(int handle)
{
    if (handle != 0) {
        // Call into manager singleton accessor; DAT_0112af58 holds a global pointer (e.g., SimManager, GodfatherGameManager)
        int managerValue = FUN_0043b870(*(int*)0x0112af58);
        return managerValue;
    }
    return 0;
}