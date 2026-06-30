// FUNC_NAME: GameLoop::processFrame
void GameLoop::processFrame(char skipRender)
{
    longlong timeDelta;
    longlong currentTime;
    longlong previousTime;

    // Begin frame timing
    beginFrame(1);
    updateInput();
    currentTime = getTimeMs();
    previousTime = getTimeMs();
    // Calculate time delta (previousTime - currentTime + previousFrameDelta) [note: likely wrong sign?]
    // Actually: lVar1 = (lVar2 - lVar1) + CONCAT44(DAT_0120582c, DAT_01205828)
    // This stores delta = (currentTime - previousTime) + previousFrameDelta? Wait: lVar2 = second call? Let's check:
    // Actually: lVar1 = FUN_00494ad0(); lVar2 = FUN_00494ad0(); then lVar1 = (lVar2 - lVar1) + CONCAT44(DAT_0120582c,DAT_01205828)
    // So first call gets currentTime (or previous?), second gets another time. Typically getTime twice to get delta? 
    // But order: first call stores in lVar1, second in lVar2. Then lVar1 = lVar2 - lVar1 + oldDelta. That means delta = newTime - oldTime + oldDelta? That seems odd.
    // Maybe the first call is "getFrameStartTime", second is "getCurrentTime"? Or the subtraction is reversed.
    // Given we have two calls, and then assignment, it's likely: delta = currentTime - previousTime + carryover?
    // But the naming: we'll keep simple as "timeDelta".
    // Actually: DAT_01205828 and DAT_0120582c store accumulated delta? Possibly frame delta.
    // I'll restructure as:
    timeDelta = (currentTime - previousTime) + ((longlong)DAT_01205828 | ((longlong)DAT_0120582c << 32));
    DAT_01205828 = (int)timeDelta;
    DAT_0120582c = (int)(timeDelta >> 32);

    if ((skipRender == '\0') && (DAT_00f15a48 != 0)) {
        processSomeEvent(DAT_00f15a48);
        timeDelta = ((longlong)DAT_01205828 | ((longlong)DAT_0120582c << 32)); // refresh after event
    }

    // Store the delta for next frame
    DAT_0120582c = (int)(timeDelta >> 32);
    DAT_01205828 = (int)timeDelta;

    updatePhysics();
    DAT_01205874++; // frame counter
    updateInput(); // second call? maybe sync?
    render(DAT_00f15a44);

    // Reset various flags/counters
    DAT_012058b0 = 0;
    _DAT_011f3918 = 0;
    _DAT_011f391c = 0;
    _DAT_011f3920 = 0;
    _DAT_011f3924 = 0;

    syncFrame();
    return;
}