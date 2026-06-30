// FUNC_NAME: SpatialGrid::findEntityInViewCone
int __thiscall SpatialGrid::findEntityInViewCone(int this, int enableFlag, float* queryPos, float minDist, bool (*filterCallback)(int), float maxDist)
{
    int bestEntity = 0;
    float bestDistSqFromQuery = DAT_00d5f6f0; // +0x0: large initial value
    int iVar3;
    int local_3c = 0;
    float queryToCamDir[3]; // local_20, local_1c, local_18

    if (enableFlag == 0) {
        return 0;
    }

    int camera = FUN_00471610(); // returns Camera*? -> position at +0x30,x, +0x34,y, +0x38,z
    queryToCamDir[0] = *queryPos - *(float*)(camera + 0x30);
    queryToCamDir[1] = queryPos[1] - *(float*)(camera + 0x34);
    queryToCamDir[2] = queryPos[2] - *(float*)(camera + 0x38);
    undefined4 local_14 = 0;
    FUN_0056afa0(queryToCamDir, queryToCamDir); // normalize direction from quest to cam? Actually it's toCam, so reverse

    int hashIdx = ((int)*(float*)(camera + 0x38) >> 3 & 0x1f) * 0x20 + ((int)*(float*)(camera + 0x30) >> 3 & 0x1f);
    byte* gridOffsets = (byte*)&DAT_0112a960; // 2D grid offset table (2-byte entries)
    do {
        iVar3 = local_3c;
        // Access hash bucket: cell index = (gridOffsets[1]*0x20 + hashIdx) & 0x3e0 | (gridOffsets[0] + hashIdx) & 0x1f
        int cellIdx = ((char)gridOffsets[1] * 0x20 + hashIdx & 0x3e0) | ((uint)gridOffsets[0] + hashIdx & 0x1f);
        for (int entity = *(int*)(this + 0x20 + cellIdx * 8); entity != 0; entity = *(int*)(entity + 8)) {
            // +0x8a: flags (bit 0 = alive? 1 = hidden?)
            if (((*(byte*)(entity + 0x8a) & 1) == 0) &&
                (filterCallback == nullptr || filterCallback(entity))) {
                float dx = *queryPos - *(float*)(entity + 0x44); // +0x44: x
                float dy = queryPos[1] - *(float*)(entity + 0x48); // +0x48: y
                float dz = queryPos[2] - *(float*)(entity + 0x4c); // +0x4c: z
                float distSqFromQuery = dx*dx + dy*dy + dz*dz;
                if (distSqFromQuery <= maxDist && distSqFromQuery >= minDist) {
                    float camToEntity[3];
                    camToEntity[0] = *(float*)(entity + 0x44) - *(float*)(camera + 0x30);
                    camToEntity[1] = *(float*)(entity + 0x48) - *(float*)(camera + 0x34);
                    camToEntity[2] = *(float*)(entity + 0x4c) - *(float*)(camera + 0x38);
                    float distSqFromCam = camToEntity[0]*camToEntity[0] + camToEntity[1]*camToEntity[1] + camToEntity[2]*camToEntity[2];
                    if (distSqFromCam <= bestDistSqFromQuery) {
                        FUN_0043a210(camToEntity, camToEntity); // normalize
                        // Dot product with queryToCamDir (which is actually direction from query to cam? This is reversed, so check if entity behind query? Actually condition: < DAT_00d5fb04 (cosine threshold) means it's in front of camera? need to check sign)
                        if (dx * queryToCamDir[0] + dy * queryToCamDir[1] + dz * queryToCamDir[2] < DAT_00d5fb04) {
                            bestDistSqFromQuery = distSqFromQuery;
                            local_3c = entity;
                            if (distSqFromCam < DAT_00d5ddec) { // immediate accept if very close to camera
                                return entity;
                            }
                        }
                    }
                }
            }
            iVar3 = local_3c;
        }
        gridOffsets += 2;
    } while ((int)gridOffsets < 0x112a99a);
    return local_3c;
}