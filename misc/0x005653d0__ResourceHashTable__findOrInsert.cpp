// FUNC_NAME: ResourceHashTable::findOrInsert
int __thiscall ResourceHashTable::findOrInsert(uint this, KeyPair *pKey)
{
    byte bVar1;
    int iVar2;
    byte *pbVar3;
    byte *pbVar4;
    uint uVar5;
    int iVar6;
    int *piVar7;
    bool bVar8;

    uVar5 = 0;
    if (*(int *)(this + 0x124) != 0) { // m_entryCount
        piVar7 = (int *)(this + 0x24); // m_entryArray
        do {
            iVar6 = *piVar7; // current entry
            if (*(int *)(iVar6 + 0x28) == pKey[1]) { // entry->keyId == pKey->keyId
                if (*(int *)(iVar6 + 0x28) == 0) { // if keyId is 0, return entry immediately?
                    return iVar6;
                }
                pbVar4 = (byte *)*pKey; // pKey->keyString
                pbVar3 = *(byte **)(iVar6 + 0x24); // entry->keyString
                do {
                    bVar1 = *pbVar3;
                    bVar8 = bVar1 < *pbVar4;
                    if (bVar1 != *pbVar4) {
LAB_00565430:
                        iVar2 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                        goto LAB_00565435;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar3[1];
                    bVar8 = bVar1 < pbVar4[1];
                    if (bVar1 != pbVar4[1]) goto LAB_00565430;
                    pbVar3 = pbVar3 + 2;
                    pbVar4 = pbVar4 + 2;
                } while (bVar1 != 0);
                iVar2 = 0;
LAB_00565435:
                if (iVar2 == 0) {
                    return iVar6; // found matching entry
                }
            }
            uVar5 = uVar5 + 1;
            piVar7 = piVar7 + 1;
        } while (uVar5 < *(uint *)(this + 0x124));
    }
    // Not found; allocate new entry
    iVar2 = FUN_009c8e50(0x40); // raw allocation (64 bytes)
    iVar6 = 0;
    if (iVar2 != 0) {
        // Zero fields from +0x10 to +0x38 (11 dwords)
        *(undefined4 *)(iVar2 + 0x10) = 0;
        *(undefined4 *)(iVar2 + 0x14) = 0;
        *(undefined4 *)(iVar2 + 0x18) = 0;
        *(undefined4 *)(iVar2 + 0x1c) = 0;
        *(undefined4 *)(iVar2 + 0x20) = 0;
        *(undefined4 *)(iVar2 + 0x24) = 0;
        *(undefined4 *)(iVar2 + 0x28) = 0;
        *(undefined4 *)(iVar2 + 0x2c) = 0;
        *(undefined4 *)(iVar2 + 0x30) = 0;
        *(undefined4 *)(iVar2 + 0x34) = 0;
        *(undefined4 *)(iVar2 + 0x38) = 0;
        iVar6 = iVar2;
    }
    if (*(uint *)(this + 0x124) < 0x40) { // capacity check (max 64 entries)
        *(int *)(this + 0x24 + *(uint *)(this + 0x124) * 4) = iVar6; // store entry pointer
        *(int *)(this + 0x124) = *(int *)(this + 0x124) + 1; // increment count
    }
    *(undefined4 *)(iVar6 + 0x38) = *(undefined4 *)(this + 0x128); // copy m_ownerData to entry+0x38
    FUN_004d3e20(pKey); // presumably copies/processes the key string
    pbVar4 = (byte *)*pKey; // string pointer
    if (pbVar4 == (byte *)0x0) {
        pbVar4 = &DAT_0120546e; // fallback empty string constant
    }
    iVar2 = 0;
    if (pbVar4 != (byte *)0x0) {
        bVar1 = *pbVar4;
        while (bVar1 != 0) {
            uVar5 = (uint)bVar1;
            pbVar4 = pbVar4 + 1;
            if (uVar5 - 0x41 < 0x1a) { // if uppercase letter A-Z
                uVar5 = uVar5 + 0x20; // convert to lowercase
            }
            iVar2 = iVar2 * 0x1003f + uVar5; // hash: h = h * 65599 + c
            bVar1 = *pbVar4;
        }
    }
    *(int *)(iVar6 + 0x3c) = iVar2; // store hash value in entry
    return iVar6; // return new entry
}