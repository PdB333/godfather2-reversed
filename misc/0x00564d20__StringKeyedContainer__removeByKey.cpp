// FUNC_NAME: StringKeyedContainer::removeByKey
int __thiscall StringKeyedContainer::removeByKey(StringKeyedContainer *this, int *keyObject) {
    byte bVar1;
    uint uVar2;
    byte *pbVar3;
    int iVar4;
    byte *pbVar5;
    int iVar6;
    undefined4 *puVar7;
    byte *pbVar8;
    uint uVar9;
    bool bVar10;

    // Get the string from the key object (virtual function at vtable+0x14)
    pbVar3 = (byte *)(**(code **)(*keyObject + 0x14))();

    // Attempt to find the key using an internal helper (e.g., hash lookup or index)
    iVar4 = FUN_00564de0(this, pbVar3);

    // If no match found or the container is empty, return the result (likely 0)
    if ((iVar4 == 0) || (*(int *)(this + 0x1c) == 0)) {
        return iVar4;
    }

    // Linear search through the array of stored objects (starting at this+8)
    puVar7 = (undefined4 *)(this + 8);
    uVar9 = 0;
    do {
        // Get the string from the current stored object (virtual function at vtable+0x14)
        pbVar5 = (byte *)(**(code **)(*(int *)(*(int *)puVar7) + 0x14))();

        // Compare strings byte by byte (lexicographic, like strcmp)
        pbVar8 = pbVar3;
        do {
            bVar1 = *pbVar5;
            bVar10 = bVar1 < *pbVar8;
            if (bVar1 != *pbVar8) {
LAB_00564d90:
                iVar6 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
                goto LAB_00564d95;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar5[1];
            bVar10 = bVar1 < pbVar8[1];
            if (bVar1 != pbVar8[1]) goto LAB_00564d90;
            pbVar5 = pbVar5 + 2;
            pbVar8 = pbVar8 + 2;
        } while (bVar1 != 0);
        iVar6 = 0;

LAB_00564d95:
        // If strings match, remove this object from the array and return it
        if (iVar6 == 0) {
            uVar2 = *(uint *)(this + 0x1c);   // count
            iVar4 = *(int *)(this + 8 + uVar9 * 4); // object to remove
            if (uVar2 <= uVar9) {
                return iVar4;
            }
            if (uVar9 < uVar2 - 1) {
                // Shift the last element into the removed slot
                *(int *)(this + 8 + uVar9 * 4) = *(int *)(this + 4 + uVar2 * 4);
            }
            *(int *)(this + 0x1c) = *(int *)(this + 0x1c) - 1; // decrement count
            return iVar4;
        }

        uVar9 = uVar9 + 1;
        puVar7 = puVar7 + 1;
    } while (uVar9 < *(uint *)(this + 0x1c)); // continue until all elements checked

    return iVar4; // not found, return previous result (0)
}