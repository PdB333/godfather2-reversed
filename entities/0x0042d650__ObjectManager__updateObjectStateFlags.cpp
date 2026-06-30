// FUNC_NAME: ObjectManager::updateObjectStateFlags
void __thiscall ObjectManager::updateObjectStateFlags(ushort mask, int contextPtr)
{
    ushort uVar1;
    int currentPtr;   // iVar5, iterates over object array
    int endPtr;       // iVar2, end of array
    uint structFlags; // uVar3, flags from object struct
    ushort newMask;   // uVar4
    int fsBase;       // unaff_FS_OFFSET

    currentPtr = *(int *)(this + 0x50);                // +0x50: pointer to array of objects (each 0xB0 bytes)
    mask = mask | (ushort)_DAT_012053d8;               // global mask OR
    endPtr = *(int *)(this + 0x34) * 0xB0 + currentPtr; // +0x34: count of objects
    do {
        if (currentPtr == endPtr) {
            return;
        }
        if (*(short *)(currentPtr + 0x2A) > -2) {       // +0x2A: some state short (maybe Z position or health?)
            if (((*(char *)(currentPtr + 0x28) == '\0') &&       // +0x28: byte, 0 = active?
                 (*(char *)(currentPtr + 4) != '\x01')) &&       // +4: byte, 1 = dead?
                (structFlags = *(uint *)(currentPtr + 8),        // +8: uint flags
                 (structFlags & 0x803C) == 0)) {                // check no certain bits set
                newMask = (ushort)DAT_012053dc & mask;
                if (newMask == 0) {
LAB_0042d6cc:
                    if ((structFlags & 0x10000) == 0) goto LAB_0042d6e3;
                    structFlags = structFlags & 0xFFFEFFFF;
                }
                else {
                    if ((structFlags & 0x10000) != 0) {
                        if (newMask != 0) goto LAB_0042d6e3;
                        goto LAB_0042d6cc;
                    }
                    structFlags = structFlags | 0x10000;
                }
                *(uint *)(currentPtr + 8) = structFlags;
                FUN_00432e30(contextPtr);                    // unknown function, likely update some system
            }
LAB_0042d6e3:
            newMask = mask;
            if ((*(uint *)(currentPtr + 8) & 0x800) != 0) { // check flag 0x800
                // Access per-thread data via fs segment (GS in x86)
                newMask = ~*(ushort *)(**(int **)(unaff_FS_OFFSET + 0x2C) + 0x20) & mask;
            }
            uVar1 = *(ushort *)(**(int **)(unaff_FS_OFFSET + 0x2C) + 0x0C); // +0x0C: ushort mask1
            if (((uVar1 & newMask) != 0) &&
                ((*(ushort *)(**(int **)(unaff_FS_OFFSET + 0x2C) + 0x0E) & newMask) != 0)) {
                newMask = newMask & ~uVar1;
            }
            if ((*(byte *)(currentPtr + 0x29) < 6) &&         // +0x29: byte index (0-5)
                (*(short *)(currentPtr + 0x2A) >= 0)) {       // +0x2A: short sub-index
                // Write newMask into a 2D array at contextPtr + 0x123C + (index * 0x6A0) + (subIndex * 2)
                *(ushort *)(*(int *)((uint)*(byte *)(currentPtr + 0x29) * 0x6A0 + 0x123C + contextPtr) +
                           *(short *)(currentPtr + 0x2A) * 2) = newMask;
            }
        }
        currentPtr += 0xB0;
    } while (true);
}