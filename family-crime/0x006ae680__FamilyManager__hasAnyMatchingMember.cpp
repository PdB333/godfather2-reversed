// FUNC_NAME: FamilyManager::hasAnyMatchingMember
char __thiscall FamilyManager::hasAnyMatchingMember(void* this, int condition, int extra1, int extra2)
{
    int memberCount = *(int*)((char*)this + 0x19c); // +0x19c: number of family members
    int i = 0;
    char result = 0;
    if (memberCount != 0) {
        while (checkCondition(condition, extra1, extra2) == 0) { // FUN_006b7ea0: predicate on supplied parameters
            i++;
            if (memberCount <= i) {
                return 0;
            }
        }
        result = 1;
    }
    return result;
}