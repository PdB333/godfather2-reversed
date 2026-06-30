// FUNC_NAME: IsPointInsideAnyInteractiveVolume
bool IsPointInsideAnyInteractiveVolume()
{
    float* boxPtr;
    bool* resultCache;
    uint* volumeListPtr;
    uint cacheContext;
    float pointX;
    float pointY;
    float pointZ;
    float margin;

    // Attempt to retrieve cached result for this query context
    cacheContext = FUN_00429c60(&stack0x00000004);  // some static context
    if (cacheContext != 0) {
        // Return cached boolean at offset 4
        return *(bool*)(cacheContext + 4);
    }

    // Get current time (or delta)
    float currentTime = FUN_0049feb0();  // likely GetTickCount or similar
    margin = margin - DAT_00e3ac54;      // subtract a base time, probably not margin but something else

    // Initialize point coordinates (likely from some global or previous context)
    // These are not explicitly initialized in the decompiled code, possibly from caller stack
    pointY = ???;
    pointZ = ???;
    // They are used in bounding box checks

    volumeListPtr = &DAT_0120a3e8;  // array of pointers to volume structs
    while (true) {
        if (&DAT_0120a3e8 + DAT_0120a5e8 == volumeListPtr) {
            // No volume contains the point
            FUN_00429cc0(&cacheContext, &stack0x00000004);
            *(bool*)(cacheContext + 4) = false;
            return false;
        }
        boxPtr = (float*)*volumeListPtr;
        // Check if point is within expanded bounding box (margin added)
        if ((boxPtr[0] + margin < pointX) && (pointX < boxPtr[4] - margin) &&
            (boxPtr[2] + margin < pointZ) && (pointZ < boxPtr[6] - margin) &&
            (boxPtr[1] + margin < pointY) && (pointY < boxPtr[5] - margin)) break;
        volumeListPtr = volumeListPtr + 1;
    }

    // Point is inside a volume; allocate result and cache true
    bool* result = (bool*)FUN_004299d0();
    *result = true;
    return true;
}