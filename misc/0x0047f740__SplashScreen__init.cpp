// FUNC_NAME: SplashScreen::init
void __thiscall SplashScreen::init(void* thisPtr, int paramIndex)
{
    char cCheckResult;
    int localCopyParam;
    undefined4 timerValue;
    byte localFlag;

    // Check if already initialized (flag at +0x90)
    if (*(byte*)((int)thisPtr + 0x90) == 0) {
        // Mark as initialized
        *(byte*)((int)thisPtr + 0x90) = 1;

        // Attempt to load first resource string (global DAT_0120e970)
        cCheckResult = isResourceReady((void*)&DAT_0120e970);
        if ((cCheckResult == 0) && (DAT_0120e970 != 0)) {
            copyString((void*)((int)thisPtr + 0x3c), (void*)&DAT_0120e970);
        }

        // If second flag (+0x91) is not set, call sub-function to load background
        if (*(byte*)((int)thisPtr + 0x91) == 0) {
            loadBackground((void*)thisPtr);
        }

        // Load image data using offset +0x394
        loadImage((void*)thisPtr, *(undefined4*)((int)thisPtr + 0x394));

        // Attempt to load second resource string (global DAT_0120e960)
        cCheckResult = isResourceReady((void*)&DAT_0120e960);
        if ((cCheckResult == 0) && (DAT_0120e960 != 0)) {
            copyString((void*)((int)thisPtr + 0x3c), (void*)&DAT_0120e960);
        }

        // Compute parameter for timer/callback based on paramIndex
        if (paramIndex == 0) {
            localCopyParam = 0;
        } else {
            localCopyParam = paramIndex + 0x20; // +0x20 offset as some index
        }

        // Set up global timer/callback value
        timerValue = DAT_0120eaf8;
        localFlag = 0;
        scheduleCallback(&timerValue, 0);
    }
    return;
}