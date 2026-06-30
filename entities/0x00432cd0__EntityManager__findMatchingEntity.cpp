// FUNC_NAME: EntityManager::findMatchingEntity
// Function at 0x00432cd0 - searches a list of entities for one matching a source entity's type/flags
// this +0x3a74: array of entity pointers (listStart)
// this +0x3af4: count of entities in list (listCount)
// Global g_entitySpecialList[] at DAT_012233b0+0x30: 3 special entity pointers
// Global g_bFlag at DAT_0120535b: some global flag

int* __thiscall EntityManager::findMatchingEntity(int this, int* sourceEntity) {
    uint bitFlags;
    int i, j;
    char flagChar;
    byte byteFlag;
    int* piVar6;
    int** ppEntity;
    int* currentEntity;
    int specialList[3]; // actually at global offset
    extern int* g_specialEntityList[3]; // DAT_012233b0+0x30
    extern char g_someGlobalFlag; // DAT_0120535b

    // Check if sourceEntity is in the special list (player, etc.)
    piVar6 = g_specialEntityList;
    for (i = 0; i < 3; i++) {
        if (piVar6[i] == sourceEntity) {
            // Mark first byte of sourceEntity (likely bIsSpecial) as 1
            *(char*)sourceEntity = 1;
            if (g_someGlobalFlag != 0)
                break;
            goto checkList;
        }
    }
    *(char*)sourceEntity = 0;

checkList:
    ppEntity = (int**)(this + 0x3a74);
    currentEntity = 0;
    if (ppEntity == ppEntity + *(int*)(this + 0x3af4)) {
        return 0;
    }
    do {
        // Virtual call at offset 0x3c: returns entity type / category
        char typeChar = (*(char (__thiscall**)(int*))(**ppEntity + 0x3c))();
        if (typeChar == *(char*)sourceEntity) {
            // Complex global read: likely some bitfield related to player/team
            bitFlags = *(uint*)(*(int*)(*(int*)(__readfsdword(0x2c) + 8) + 0x7c) + *(int*)(sourceEntity + 0x18));
            byteFlag = (**(byte (__thiscall**)(int*))(**ppEntity + 0x40))(); // Get some flag
            if (((byte)(bitFlags >> 0xb) & 1) == byteFlag) {
                // Virtual call at offset 0x14: check if entity matches sourceEntity
                char matchResult = (**(char (__thiscall**)(int*, int*))(**ppEntity + 0x14))();
                if (matchResult != 0) {
                    currentEntity = *ppEntity;
                }
            }
        }
        ppEntity++;
    } while (ppEntity != (int**)(this + 0x3a74) + *(int*)(this + 0x3af4));
    return (int)currentEntity;
}