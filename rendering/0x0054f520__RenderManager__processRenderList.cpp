// FUNC_NAME: RenderManager::processRenderList
void __thiscall RenderManager::processRenderList(int this) {
    int* piVar3;
    int iVar2;
    int iVar4;
    int listCount = 0;
    int listBuffer[3];
    int local_2c4;
    undefined4 viewportStruct[5];
    int listItemCount;
    undefined4 local_2b4;
    undefined4 local_2b0;
    undefined4 local_2ac;
    undefined4 local_2a8;
    undefined4 local_2a4;
    undefined4 uStack_2a0;
    undefined4 uStack_29c;
    undefined4 uStack_298;
    undefined4 uStack_294;
    undefined4 uStack_290;
    undefined4 uStack_28c;
    undefined4 uStack_288;
    int iStack_280;
    undefined4 uStack_27c;
    undefined4 uStack_278;
    undefined4 uStack_274;
    int* apiStack_270[2];
    undefined4 local_268;
    short refCount;
    short unkShort;
    undefined** vtablePtr;
    undefined1 local_244;
    undefined1* listDataPtr;
    int listBufferPtr;
    int listSize;
    undefined1 local_234[260];
    undefined** destVtable;
    undefined4 cameraPosX;
    float cameraPosZ;
    undefined4 cameraPosY;
    undefined4 cameraRot;
    undefined4* objPtr[7];
    uint flags;

    iVar2 = *(int*)(this + 0x18) + 0x10;
    iVar4 = 0;
    listCount = 0;
    if ((iVar2 != 0) && (*(char*)(*(int*)(this + 0x18) + 0x20) + iVar2 != 0)) {
        listCount = 0;
        FUN_004af8c0(listBuffer, 0x2001);
        if (listBuffer[0] != 0) {
            listCount = listBuffer[0];
        }
    }
    local_2b0 = *(undefined4*)(this + 0xe0);  // +0xe0: some flag/offset
    local_2b4 = 0x3e0;                        // viewport width (992)
    local_2ac = 0x80000000;                   // viewport flags
    local_2a8 = 0;
    local_2a4 = 0;
    FUN_00a64b00(_DAT_0103b238);              // global texture/surface
    FUN_00549bf0();                           // setup rendering state
    destVtable = &PTR_FUN_00e39bd0;
    if (objPtr[0] != &local_268) {
        if (((objPtr[0] != (undefined4*)0x0) && (*(short*)(objPtr[0] + 1) != 0)) &&
            (*(short*)((int)objPtr[0] + 6) = *(short*)((int)objPtr[0] + 6) + -1,
            *(short*)((int)objPtr[0] + 6) == 0)) {
            (**(code**)*objPtr[0])(1);
        }
        objPtr[0] = &local_268;
        if (refCount != 0) {
            unkShort = unkShort + 1;
        }
    }
    vtablePtr = &PTR_LAB_00e3572c;
    listSize = -0x7ffffff0;                   // negative large number
    listBufferPtr = 0;
    flags = (uint)&local_2b4 >> 2 | 0x40000000;  // packed viewport data
    listDataPtr = local_234;                  // stack buffer for list
    iVar2 = *(int*)(*(int*)(*(int*)(this + 0x14) + 0x30) + 0x18);  // camera position struct
    cameraPosX = *(undefined4*)(iVar2 + 0x30);
    cameraPosZ = *(float*)(iVar2 + 0x34) + DAT_00e2cd54;
    cameraPosY = *(undefined4*)(iVar2 + 0x38);
    cameraRot = *(undefined4*)(iVar2 + 0x3c);
    local_244 = 0;
    FUN_009eb910(objPtr, *(undefined4*)(*(int*)(_DAT_01223480 + 0x24) + 0x6c), &vtablePtr);
    listBuffer[0] = 0;
    if (0 < listSize) {
        do {
            iVar2 = *(int*)(listDataPtr + iVar4 + 8);
            if ((iVar2 != 0) && (*(char*)(iVar2 + 0x10) + iVar2 != 0)) {
                FUN_004af8c0(apiStack_270, 0x2001);
                piVar3 = (int*)0x0;
                if (apiStack_270[0] != (int*)0x0) {
                    piVar3 = apiStack_270[0];
                }
                if (piVar3 != (int*)0x0) {
                    iVar2 = *(int*)(*(int*)(*(int*)(this + 0x14) + 0x30) + 0x18);
                    uStack_2a0 = *(undefined4*)(iVar2 + 0x30);
                    uStack_29c = *(undefined4*)(iVar2 + 0x34);
                    uStack_298 = *(undefined4*)(iVar2 + 0x38);
                    uStack_294 = *(undefined4*)(iVar2 + 0x3c);
                    iVar2 = *(int*)(this + 0x18);
                    uStack_290 = DAT_01126050;
                    uStack_28c = DAT_01126054;
                    uStack_288 = DAT_01126058;
                    iStack_280 = iVar2 + 0x10;
                    uStack_284 = 0;
                    uStack_27c = *(undefined4*)(iVar2 + 0x14);
                    uStack_278 = *(undefined4*)(listDataPtr + iVar4 + 8);
                    uStack_274 = *(undefined4*)(listDataPtr + iVar4 + 0xc);
                    (**(code**)(*piVar3 + 200))(listCount, (int)*(char*)(iVar2 + 0x28), &uStack_2a0);
                }
            }
            listBuffer[0] = listBuffer[0] + 1;
            iVar4 = iVar4 + 0x10;
        } while (listBuffer[0] < listSize);
    }
    iVar2 = listSize;
    vtablePtr = &PTR_LAB_00e3572c;
    if (-1 < listSize) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(listDataPtr, iVar2 << 4, 0x17);  // free memory
    }
    undefined4* puVar1 = objPtr[0];
    vtablePtr = &PTR_LAB_00dcf968;
    destVtable = &PTR_FUN_00e39bc8;
    if (((objPtr[0] != (undefined4*)0x0) && (*(short*)(objPtr[0] + 1) != 0)) &&
        (*(short*)((int)objPtr[0] + 6) = *(short*)((int)objPtr[0] + 6) + -1,
        *(short*)((int)puVar1 + 6) == 0)) {
        (**(code**)*puVar1)(1);
    }
    return;
}