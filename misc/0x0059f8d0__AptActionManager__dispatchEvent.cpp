// FUNC_NAME: AptActionManager::dispatchEvent
void AptActionManager::dispatchEvent(int param_1, char* param_2, int param_3)
{
    char cVar1;
    int* piVar2;
    code* pcVar3;
    uint uVar4;
    undefined4 uVar5;
    uint* puVar6;
    char* pcVar7;
    int iVar8;
    int unaff_FS_OFFSET;
    undefined4 uVar9;
    undefined4 uVar10;
    undefined4 uVar11;
    char* sourceFile; // local_14
    char* functionName; // local_10
    undefined4 lineNumber; // local_c
    int severity; // local_8
    undefined1* assertFlag; // local_4

    // Check if APT is initialized
    if (DAT_012055b0 != 0) goto LAB_0059f966; // bAptIsInitialized flag

    // Debug assertion for "bAptIsInitialized"
    sourceFile = "bAptIsInitialized";
    functionName = "..\\source\\Apt\\Apt.cpp";
    lineNumber = 0x2b7; // 695
    severity = 2;
    assertFlag = &DAT_01128f51; // assertion flag

    if (DAT_01128f51 == '\0') goto LAB_0059f966; // assertion not enabled

    piVar2 = *(int**)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x30); // FS segment TLS
    uVar4 = 1;
    if (piVar2 == (int*)0x0) {
LAB_0059f944:
        if ((uVar4 & 2) != 0) {
            *assertFlag = 0;
        }
    }
    else {
        uVar4 = (**(code**)(*piVar2 + 8))(&sourceFile, "bAptIsInitialized");
        if (assertFlag != (undefined1*)0x0) goto LAB_0059f944;
    }
    if (((piVar2 != (int*)0x0) || (severity != 4)) &&
       (((uVar4 & 1) != 0 || ((severity == 0 || (severity == 1)))))) {
        pcVar3 = (code*)swi(3); // debug break
        (*pcVar3)();
        return;
    }

LAB_0059f966:
    // Main processing
    uVar11 = 1;
    uVar10 = 1;
    uVar9 = 0;
    uVar5 = FUN_0059e2f0(0, param_1, 1, 1); // likely createEvent
    puVar6 = (uint*)FUN_005aea60(uVar5, uVar9, param_1, uVar10, uVar11); // likely getOrCreateAction
    if (puVar6 != DAT_0119cbbc) {
        uVar4 = *puVar6 & 0x7fff; // action type (lower 15 bits)
        if ((uVar4 != 0x19) && // 25
           (((~(byte)(*puVar6 >> 0xf) & 1) != 0 || // if high bit not set
            (((uVar4 != 0xb && (uVar4 != 0x18)) && (uVar4 != 0x17)))))) {
            FUN_0059c230(puVar6); // likely markForDelete or deref
        }
    }
    pcVar7 = (char*)FUN_005a90a0(param_2, param_3); // likely strdup or copy
    if (pcVar7 != param_2) {
        iVar8 = (int)param_2 - (int)pcVar7;
        do {
            cVar1 = *pcVar7;
            pcVar7[iVar8] = cVar1;
            pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
    }
    (**(code**)(&DAT_0103aee0 + (*puVar6 & 0x7fff) * 4))(puVar6); // dispatch via jump table
    return;
}