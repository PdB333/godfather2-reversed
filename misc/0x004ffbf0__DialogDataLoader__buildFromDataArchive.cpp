// FUNC_NAME: DialogDataLoader::buildFromDataArchive
void __thiscall DialogDataLoader::buildFromDataArchive(int *thisPtr, void *archiveReader, int *dataRecord)
{
    int *nodePtr;
    char *dest1;
    char *dest2;
    char isValid;
    int *eaxIn = dataRecord;
    int resourceId;
    int *thisNode;
    int fsOffset;
    int zeroValue;
    char tempBuffer[28];

    // base class constructor call (e.g., DataLoader base)
    FUN_00533cc0();

    // set vtable (vtable ptr at +0x00)
    *thisPtr = &PTR_FUN_00e37bf0;

    // node pointer at offset +0x3C (thisPtr[0xf])
    nodePtr = thisPtr + 0xf;
    *nodePtr = 0;
    // +0x40 (thisPtr[0x10])
    thisPtr[0x10] = 0;

    // if archiveReader already processed (offset +0x0d byte), early exit
    if (*(char *)((int)archiveReader + 0xd) != '\0') {
        return;
    }

    zeroValue = 0;
    // store dataRecord pointer at +0x44 (thisPtr[0x11])
    thisPtr[0x11] = (int)eaxIn;
    // +0xB4 and +0xB8
    thisPtr[0x2d] = 0;
    thisPtr[0x2e] = *eaxIn;

    // if node pointer already allocated, free it (call FUN_004daf90)
    if (*nodePtr != 0) {
        FUN_004daf90(nodePtr);
        *nodePtr = 0;
    }

    // compute some base pointer from thread-local storage (FS segment offset +0x2c)
    resourceId = **(int **)(fsOffset + 0x2c);
    // +0x24 (thisPtr[9]) = thisPtr[1]
    thisPtr[9] = thisPtr[1];
    // +0x28 (thisPtr[10]) = *(resourceId+8) + 0x80 + thisPtr[4]
    thisPtr[10] = *(int *)(resourceId + 8) + 0x80 + thisPtr[4];
    // +0x2C..0x38 (thisPtr[0xb..0xe]) cleared
    thisPtr[0xb] = zeroValue;
    thisPtr[0xc] = zeroValue;
    thisPtr[0xd] = zeroValue;
    thisPtr[0xe] = zeroValue;

    // string fields
    nodePtr = eaxIn + 2; // points to record's flags/data
    dest1 = (char *)(thisPtr + 0x12); // offset +0x48
    *(char *)(thisPtr + 0x12) = 0; // null terminate first string
    *dest1 = '\0';
    *(char *)(thisPtr + 0x24) = 0; // offset +0x90? Actually this is later used as dest_00
    // Note: the offset +0x24 is also used later for third string. Let's align: +0x12 is first, +0x1b is second, +0x24 is third (as per subsequent code)
    // Actually the code sets *dest1='\0' then later *(thisPtr+0x12)=0 again; so perhaps there is a misunderstanding.
    // Reading carefully: *(undefined1 *)(unaff_ESI + 0x12) = 0; sets byte at offset 0x12 to 0. Then *_Dest = '\0'; where _Dest = (char *)(unaff_ESI + 0x1b); (offset 0x6c). Then *(undefined1 *)(unaff_ESI + 0x24) = 0; (offset 0x90).
    // So strings at offsets 0x12, 0x1b, 0x24. Ok.

    // check if record has no data (all zero flags)
    if ((*nodePtr == 0 && eaxIn[3] == 0) && (eaxIn[4] == 0 && eaxIn[5] == 0)) {
LAB_004ffcab:
        *(char *)((int)archiveReader + 0xc) = 1; // mark as loaded
        return;
    }

    // read strings from data record (+6, +10, +0xe) into tempBuffer
    FUN_004eaec0(eaxIn + 6, tempBuffer);
    _strncpy((char *)(thisPtr + 0x12), tempBuffer, 0x23); // first string (0x12 bytes from start? Actually offset 0x12 * 4 = 0x48 bytes, so char array size 0x23 = 35)
    // but note: offset 0x12 is 18 * 4 = 72 bytes? That doesn't align with char. The decompiler used unaff_ESI as int*, so +0x12 means +0x48 bytes. That's fine.
    FUN_004eaec0(eaxIn + 10, tempBuffer);
    _strncpy((char *)(thisPtr + 0x1b), tempBuffer, 0x23); // second string at +0x1b*4 = 0x6c
    FUN_004eaec0(eaxIn + 0xe, tempBuffer);
    dest2 = (char *)(thisPtr + 0x24); // third string at +0x24*4 = 0x90
    _strncpy(dest2, tempBuffer, 0x23);

    // validate strings: check non-empty and valid locale (FUN_0043e480)
    if ((((*(char *)(thisPtr + 0x12) != '\0') &&
          ((char *)(thisPtr + 0x12) == (char *)0x0 || (isValid = FUN_0043e480(), isValid == '\0'))) ||
         ((*((char *)(thisPtr + 0x1b)) != '\0') &&
          (((char *)(thisPtr + 0x1b) == (char *)0x0 || (isValid = FUN_0043e480(), isValid == '\0'))))) ||
        ((*dest2 != '\0') &&
         ((dest2 == (char *)0x0 || (isValid = FUN_0043e480(), isValid == '\0'))))) {
        // if any string invalid, try to load resource from the original node pointer
        if (nodePtr == (int *)0x0) {
            *(char *)((int)archiveReader + 0xc) = 1;
            return;
        }
        resourceId = FUN_004211e0(nodePtr);
        thisNode = thisPtr + 0xf;
        if (thisPtr[0xf] != resourceId) {
            if (thisPtr[0xf] != 0) {
                FUN_004daf90(thisNode);
            }
            *thisNode = resourceId;
            if (resourceId != 0) {
                thisPtr[0x10] = *(int *)(resourceId + 4);
                *(int **)(resourceId + 4) = thisNode;
            }
        }
        if (*thisNode == 0) goto LAB_004ffcab;
        FUN_004cb0c0(0);
    }
    // call finalize init function
    FUN_0043e500(thisPtr + 9);
    return;
}