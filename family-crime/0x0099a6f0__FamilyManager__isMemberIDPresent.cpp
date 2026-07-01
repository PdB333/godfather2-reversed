// FUNC_NAME: FamilyManager::isMemberIDPresent
void __thiscall FamilyManager::isMemberIDPresent(int thisPtr, uint memberID)
{
    int iVar1;
    int iVar2;
    bool found;
    int iVar4;
    int *piVar5;
    int iVar6;
    uint uVar7;
    uint familyIndex;
    
    iVar4 = memberID;
    found = false;
    familyIndex = 0;
    
    // Number of families (typically 5)
    if (*(uint *)(thisPtr + 8) != 0) {
        do {
            if (found) {
                return;
            }
            
            // Get pointer to the family data structure
            // Structure at thisPtr+4: manager internal array? Then +4: something, +0x10: base of family array
            // Each family entry is 0x3c bytes; we read a ushort index from a table at thisPtr+0xc
            piVar5 = (int *)(*(int *)(*(int *)(thisPtr + 4) + 4) + 0x10 +
                             (uint)*(ushort *)(*(int *)(thisPtr + 0xc) + familyIndex * 2) * 0x3c + 0x1c);
            
            // Check each of the 5 positions (Don, Underboss, Consigliere, etc.)
            for (uint position = 0; position <= 4; position++) {
                if (5 < position) break;  // safety, should never happen
                
                iVar1 = *piVar5;
                if ((iVar1 != 0) && !found) {
                    uVar7 = 0;
                    // Loop over all members in this position's crew
                    // iVar1+0x34: number of members
                    // iVar1+0x50: pointer to array of member structures, each 0xb0 bytes
                    while (uVar7 < *(uint *)(iVar1 + 0x34)) {
                        iVar2 = *(int *)(*(int *)(iVar1 + 0x50) + iVar6 + 0x54);
                        if ((iVar2 != 0) &&
                            ((*(int *)(iVar2 + 0x18) == iVar4 || (*(int *)(iVar2 + 0x10) == iVar4)))) {
                            found = true;
                        }
                        uVar7++;
                        iVar6 += 0xb0;  // size of each member structure
                    }
                }
                position++;
                piVar5++;  // move to next slot (5 consecutive ints at offset 0x1c)
            }
            
            familyIndex++;
        } while (familyIndex < *(uint *)(thisPtr + 8));
    }
    return;
}