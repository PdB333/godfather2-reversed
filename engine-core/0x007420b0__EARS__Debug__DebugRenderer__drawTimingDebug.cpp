// FUNC_NAME: EARS::Debug::DebugRenderer::drawTimingDebug
bool __fastcall EARS::Debug::DebugRenderer::drawTimingDebug(int thisPtr)
{
    GameTimeManager* timeMgr;
    uint64_t rawTime;
    float fractionalSec;
    DebugTimingPoint startPoint;
    DebugTimingPoint endPoint;
    DebugOverlayContext overlayCtx;
    undefined overlayBuffer[92];
    undefined* vtablePtr;

    // Get the global game time manager singleton
    timeMgr = (GameTimeManager*)FUN_00471610(); // Likely EARS::Time::getManager() or similar

    // Fetch time values: at offset 0x30 is a 64-bit raw time (e.g., high-precision ticks)
    // At offset 0x38 is a fractional float (e.g., seconds since last frame or frame delta)
    rawTime = *(uint64_t*)((int)timeMgr + 0x30);
    fractionalSec = *(float*)((int)timeMgr + 0x38);

    // Reinterpret rawTime as two floats for debug draw point
    startPoint.asUint64 = rawTime;
    startPoint.floatPart = (float)(rawTime >> 32); // Upper 32 bits as float (coarse time)

    // Compute the second point: subtract a stored time from the current time
    // thisPtr + 0x50 points to some component (e.g., camera or player state)
    // At offset 0x1d64 from that component is a float (maybe previous frame time)
    endPoint.asInt64 = (int)(startPoint.floatPart - *(float*)(*(int*)(thisPtr + 0x50) + 0x1d64));
    endPoint.asUint64 = (endPoint.asUint64 & 0xFFFFFFFF00000000ULL) | (uint32_t)rawTime;

    // Draw a debug line from startPoint to endPoint with color 0x01000001 (dark blue?) and thickness 2
    // Parameters: &startPoint (as two floats), &endPoint (as two floats), thickness, color, flags (0,0)
    FUN_00542650(&startPoint, &endPoint, 2, &DAT_01000001, 0, 0); // Likely EARS::Debug::drawLine

    // Initialize local debug overlay context with its vtable
    vtablePtr = (undefined*)&PTR_FUN_00e32a8c; // Vtable for EARS::Debug::OverlayContext
    FUN_009e5ed0(overlayBuffer, &vtablePtr); // Constructor-like init

    // Return true if successful (local_70 (overlayCtx.success) == 0)
    return overlayCtx.success == 0;
}