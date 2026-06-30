// FUNC_NAME: BuildingManager::findBuildingByPath
int BuildingManager::findBuildingByPath(int thisPtr, char* path, char* outPath)
{
    char cVar1;
    int iVar2;
    int iVar3;
    char* pcVar4;
    int iVar5;
    uint uVar6;
    int* piVar7;
    int result; // local_84
    char localPath [128]; // local_80

    FUN_00ab4db0(&DAT_00e2cbe8); // lock mutex
    uVar6 = 0;
    result = 3; // default: not found
    if (*(int*)(thisPtr + 0x328) != 0) {
        piVar7 = (int*)(thisPtr + 0x228); // building list pointer
        do {
            iVar2 = *piVar7; // current building
            if (*(int*)(iVar2 + 0x104) != 0) { // building has path data
                iVar3 = *(int*)(iVar2 + 4); // path data pointer
                _strncpy(localPath, (char*)(iVar3 + 8), 0x80); // copy path string
                if (localPath[0] != '\0') {
                    pcVar4 = localPath;
                    do {
                        if (*pcVar4 == '/') {
                            *pcVar4 = '\\';
                        }
                        pcVar4 = pcVar4 + 1;
                    } while (*pcVar4 != '\0');
                }
                pcVar4 = localPath;
                do {
                    cVar1 = *pcVar4;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
                iVar5 = _strncmp(localPath, path, (int)pcVar4 - (int)(localPath + 1)); // compare paths
                if (iVar5 == 0) {
                    if (outPath != (char*)0x0) {
                        _strncpy(outPath, (char*)(iVar3 + 8), 0x80); // copy original path
                    }
                    iVar2 = *(int*)(iVar2 + 0x108); // building state
                    if (iVar2 == 1) {
                        result = 0; // found and active
                    }
                    else if ((((iVar2 == 2) || (iVar2 == 3)) || (iVar2 == 6)) || (result = 2, iVar2 == 5)) {
                        result = 1; // found but inactive/destroyed
                    }
                    break;
                }
            }
            uVar6 = uVar6 + 1;
            piVar7 = piVar7 + 1;
        } while (uVar6 < *(uint*)(thisPtr + 0x328)); // iterate through buildings
    }
    FUN_00ab4e70(); // unlock mutex
    return result;
}