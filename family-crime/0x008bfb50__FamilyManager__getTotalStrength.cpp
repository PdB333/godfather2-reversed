// FUNC_NAME: FamilyManager::getTotalStrength
int __thiscall FamilyManager::getTotalStrength() {
    int total = 0;
    int memberCount = *(int*)(this + 0x1a8); // +0x1a8: number of family members
    if (memberCount != 0) {
        for (int i = 0; i < memberCount; i++) {
            total += getMemberStrength(i); // FUN_008c8390: returns strength of member at index i
        }
    }
    return total;
}