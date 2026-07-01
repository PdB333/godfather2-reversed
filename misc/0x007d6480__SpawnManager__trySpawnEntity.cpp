// FUNC_NAME: SpawnManager::trySpawnEntity
unsigned int __fastcall SpawnManager::trySpawnEntity(void* thisPtr)
{
    unsigned int status;
    void* newObject;

    status = isSpawnAllowed(); // FUN_007ab6f0
    if ((status != 0) && (g_currentTime < *(float*)((int)thisPtr + 0x30))) {
        newObject = operatorNew(0x40); // FUN_00798f50(0x40)
        status = initializeObject(newObject); // FUN_0079e920
        if ((char)status != '\0') {
            status = registerObject(2); // FUN_007ab420(2)
            return status;
        }
    }
    return status & 0xffffff00;
}