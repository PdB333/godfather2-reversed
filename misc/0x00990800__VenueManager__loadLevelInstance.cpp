// FUNC_NAME: VenueManager::loadLevelInstance
// Function at 0x00990800 - loads a venue apartment 3D instance for a given level.
// Returns a status code: 1 if level index+1 is multiple of 5, else 2.
char __thiscall VenueManager::loadLevelInstance(int this, int unusedParam, uint levelIndex) {
    char buffer[32];                        // Temp buffer for level string

    // Build level string like "_level0", "_level1", etc.
    _sprintf(buffer, "_level%u", levelIndex);

    // Load the venue apartment instance with the constructed level name.
    // FUN_0059e490 likely "getVenueApartmentInstance" or "loadAsset".
    getVenueApartmentInstance("venue_apt3d_instance", buffer);

    // Return 1 if (levelIndex+1) is a multiple of 5, else 2.
    // Possible meanings: 1 = success/loaded, 2 = needs additional setup? Or reversed?
    return ((levelIndex + 1U) % 5 != 0) + 1;
}