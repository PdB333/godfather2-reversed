// FUNC_NAME: EntitySpawner::SpawnFromData
// 0x00983b20 - Spawns an entity instance from a data template stored at this+0x100.
// Uses a global manager (DAT_0112b9b4) to obtain the spawner (offset 0x40) and its creation function table (offset 0x60).
int __thiscall EntitySpawner::SpawnFromData(uint param_2) {
    int spawnerPtr;
    int *templatePtr;
    int result;

    spawnerPtr = *(int *)(DAT_0112b9b4 + 0x40); // Get spawner from global manager
    if (spawnerPtr != 0) {
        preSpawnValidate();                     // this->PreSpawnCheck() – validation before spawn
        templatePtr = *(int *)(this + 0x100);   // Data template pointer
        if (templatePtr != 0) {
            spawnerPtr = *(int *)(spawnerPtr + 0x60); // Spawn function table or object factory
            if (spawnerPtr != 0) {
                // Arguments: spawner, param_2, parent ID (0xFFFFFFFF = none), template fields
                result = SpawnObjectFromTemplate(spawnerPtr, param_2, 0xFFFFFFFF,
                                                  *(undefined4 *)(templatePtr + 0x50),   // field_0x50
                                                  *(undefined4 *)(templatePtr + 0x64),   // field_0x64 (100 decimal)
                                                  *(undefined4 *)(templatePtr + 0x68),   // field_0x68
                                                  *(undefined4 *)(templatePtr + 0x6c));  // field_0x6c
                if (result != 0) {
                    return result;
                }
                return 1; // spawn succeeded but result handle was zero? (error/fallback)
            }
        }
    }
    return 0; // spawn failed
}