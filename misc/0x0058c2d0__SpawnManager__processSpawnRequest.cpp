// FUNC_NAME: SpawnManager::processSpawnRequest
int SpawnManager::processSpawnRequest(void* entityManager, SpawnData* spawnData, void* arg3, void* arg4, void* arg5, uint flags, void* arg7)
{
    float scaleX, scaleY, scaleZ;
    uint8_t typeByte;
    float* scaleVec;
    int result;

    // If the spawn count (at +0x01) is less than 1, nothing to spawn
    if (spawnData->count < 1) {
        return 0;
    }

    // Read the type byte from the data block pointed to by spawnData->dataPtr (+0x0c)
    typeByte = *(uint8_t*)(spawnData->dataPtr);

    // Mask to get low 6 bits (0-63) and check if it's within the handled range (0x23 = 35 entries)
    if ((typeByte & 0x3F) < 0x23) {
        // Call the appropriate handler from the global function table (DAT_0103afc0)
        result = ((HandlerFunc)(&DAT_0103afc0)[typeByte & 0x3F])(entityManager, spawnData->dataPtr, arg3, arg4, arg5, flags, arg7);
        if (result != 0) {
            // If the scaling flag (bit 3) is NOT set, apply scale from spawnData->scale (+0x04)
            if ((flags & 8) == 0) {
                scaleVec = (float*)spawnData->scale; // +0x04
                scaleX = scaleVec[0];
                scaleY = scaleVec[1];
                scaleZ = scaleVec[2];
                // Scale the object's transformation at offsets 0x20, 0x24, 0x28
                *(float*)(result + 0x20) *= scaleX;
                *(float*)(result + 0x24) *= scaleY;
                *(float*)(result + 0x28) *= scaleZ;
            }
            return result;
        }
    }
    return 0;
}