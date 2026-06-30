// FUNC_NAME: EntityManager::findByGUID
// Function at 0x006bca80: Linear search through global entity list for a matching 128-bit GUID stored at offsets +0x20..+0x2c

extern EARSObject** g_pEntityList;    // DAT_0112a6a0 - array of pointers to EARSObject instances
extern int g_entityCount;             // DAT_0112a6a4 - number of entities in the list

EARSObject* EntityManager::findByGUID(int* pGuid) // pGuid is 4 ints forming the GUID
{
    if (g_entityCount != 0) {
        for (int i = 0; i < g_entityCount; i++) {
            EARSObject* pObj = g_pEntityList[i];
            // Compare GUID fields at offsets +0x20, +0x24, +0x28, +0x2c
            if (pGuid[0] == *(int*)((char*)pObj + 0x20) &&
                pGuid[1] == *(int*)((char*)pObj + 0x24) &&
                pGuid[2] == *(int*)((char*)pObj + 0x28) &&
                pGuid[3] == *(int*)((char*)pObj + 0x2c)) {
                return pObj;
            }
        }
    }
    return 0;
}