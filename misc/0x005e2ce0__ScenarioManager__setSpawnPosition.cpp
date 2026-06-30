// FUNC_NAME: ScenarioManager::setSpawnPosition
// Address: 0x005e2ce0
// Sets a spawn position (3D vector) for the current scenario if spawning is enabled.
// Returns 1 on success, 0 if scenario not available or spawning disabled.

int ScenarioManager::setSpawnPosition(int unusedArg, const float* position)
{
    // Global singleton pointer (DAT_0122350c) + 0x1744: flag indicating spawning is enabled
    if (*(char*)(DAT_0122350c + 0x1744) != '\0') {
        // Retrieve the current scenario object (FUN_005e2150)
        void* scenario = FUN_005e2150();
        if (scenario != 0) {
            // Set the position vector at offsets +0x288 (x), +0x28c (y), +0x290 (z)
            *(float*)((char*)scenario + 0x288) = position[0];
            *(float*)((char*)scenario + 0x28c) = position[1];
            *(float*)((char*)scenario + 0x290) = position[2];
            return 1;
        }
    }
    return 0;
}