// FUNC_NAME: placementHelper_tryPlace
int __cdecl placementHelper_tryPlace(PlacementResult* placementResult, PlacementConstraints* constraints, int placementType, int someLimit)
{
    // Dereference position from placementResult
    int x = placementResult->x;       // +0x10
    int y = placementResult->y;       // +0x14
    char canPlace = canPlaceAtLocation(placementType, x, y);  // FUN_005ce7e0

    if (canPlace != 0) {
        int handle = allocatePlacementHandle(0, 0, x, y);    // FUN_005ce8e0
        
        // Special case: placementType == 4 (e.g., building foundation?) and within bounds
        if ((placementType == 4) && 
            (constraints->limitAt4 <= someLimit) &&          // +0x04
            (x <= constraints->maxX) &&                      // +0x10
            (y <= constraints->maxY))                        // +0x14
        {
            placementResult->field_c = 0;                    // +0x0C
            placementResult->handle = handle;                // +0x18
            placementResult->state = 3;                      // +0x04
            placementResult->field_8 = 0;                    // +0x08
            return 2;
        }

        // Otherwise, try finalize placement
        char finalized = finalizePlacement(0, someLimit, x, y, handle); // FUN_005ce870
        if (finalized != 0) {
            placementResult->field_c = 0;                    // +0x0C
            placementResult->field_8 = 0;                    // +0x08
            placementResult->handle = handle;                // +0x18
            placementResult->state = 3;                      // +0x04
            return 1;
        }
    }
    return 0;
}