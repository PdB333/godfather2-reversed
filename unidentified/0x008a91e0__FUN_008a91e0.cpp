// FUNC_NAME: SomeManager::spawnOrCreateObject
void __fastcall SomeManager::spawnOrCreateObject(void* thisPtr)
{
    char canSpawn;
    int newObject;
    void* spawnedObject;

    canSpawn = FUN_00481660(); // likely checks if spawning is allowed (e.g., game state, memory)
    if (canSpawn != '\0') {
        newObject = FUN_009c8e50(0x38); // allocate memory for object of size 0x38 (56 bytes)
        if (newObject != 0) {
            spawnedObject = FUN_008a9090(thisPtr); // construct/initialize the object with this as parent/owner
            FUN_00481690(spawnedObject); // register/activate the spawned object
            return;
        }
        FUN_00481690(0); // failed allocation, register null (error handling)
    }
    return;
}