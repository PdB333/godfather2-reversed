// FUNC_NAME: getGameVersionString
void getGameVersionString(void)
{
    ushort uVar1;
    ushort uVar2;
    ushort uVar3;
    int iVar4;
    undefined1 *puVar5;
    BOOL BVar6;
    CHAR *pCVar7;
    CHAR *pCVar8;
    size_t asStack_138 [4];
    uint uStack_128;
    CHAR local_110 [260];
    undefined1 local_c [4];
    int local_8;
    
    // Clear the global version string buffer
    DAT_01129fc0 = 0;
    uStack_128 = 0x69d7e6;
    
    // Get the executable module filename
    GetModuleFileNameA((HMODULE)0x0, local_110, 0x104);
    
    // Get the size of the version info
    puVar5 = (undefined1 *)GetFileVersionInfoSizeA(local_110, (LPDWORD)0x0);
    GetLastError();
    
    if (puVar5 != (undefined1 *)0x0) {
        iVar4 = -(int)puVar5;
        if (&stack0xfffffee8 != puVar5) {
            // Allocate space on stack for version info
            *(CHAR **)(local_110 + iVar4 + -0xc) = local_110 + iVar4 + -8;
            *(undefined1 **)(local_110 + iVar4 + -0x10) = puVar5;
            pCVar7 = local_110 + iVar4 + -0x14;
            pCVar7[0] = '\0';
            pCVar7[1] = '\0';
            pCVar7[2] = '\0';
            pCVar7[3] = '\0';
            *(CHAR **)((int)&uStack_128 + iVar4) = local_110;
            *(undefined4 *)((int)asStack_138 + iVar4 + 0xc) = 0x69d81d;
            
            // Get the version info
            BVar6 = GetFileVersionInfoA(*(LPCSTR *)((int)&uStack_128 + iVar4),
                                        *(DWORD *)(local_110 + iVar4 + -0x14),
                                        *(DWORD *)(local_110 + iVar4 + -0x10),
                                        *(LPVOID *)(local_110 + iVar4 + -0xc));
            if (BVar6 != 0) {
                // Query for the version value
                *(undefined1 **)(local_110 + iVar4 + -0xc) = local_c;
                *(int **)(local_110 + iVar4 + -0x10) = &local_8;
                *(undefined1 **)(local_110 + iVar4 + -0x14) = &DAT_00e2f048;
                *(CHAR **)((int)&uStack_128 + iVar4) = local_110 + iVar4 + -8;
                *(undefined4 *)((int)asStack_138 + iVar4 + 0xc) = 0x69d834;
                BVar6 = VerQueryValueA(*(LPCVOID *)((int)&uStack_128 + iVar4),
                                       *(LPCSTR *)(local_110 + iVar4 + -0x14),
                                       *(LPVOID **)(local_110 + iVar4 + -0x10),
                                       *(PUINT *)(local_110 + iVar4 + -0xc));
                if (BVar6 != 0) {
                    // Extract version components from the VS_FIXEDFILEINFO structure
                    // +0x0c: dwFileVersionMS (major.minor)
                    // +0x0e: dwFileVersionLS (build.revision)
                    // +0x08: dwSignature
                    // +0x0a: dwStrucVersion
                    uVar1 = *(ushort *)(local_8 + 0xe);
                    *(uint *)(local_110 + iVar4 + -0xc) = (uint)*(ushort *)(local_8 + 0xc);
                    uVar2 = *(ushort *)(local_8 + 8);
                    uVar3 = *(ushort *)(local_8 + 10);
                    *(uint *)(local_110 + iVar4 + -0x10) = (uint)uVar1;
                    *(uint *)(local_110 + iVar4 + -0x14) = (uint)uVar2;
                    *(uint *)((int)&uStack_128 + iVar4) = (uint)uVar3;
                    
                    // Format the version string as "major.minor.build.revision"
                    *(char **)((int)asStack_138 + iVar4 + 0xc) = "%d.%d.%d.%d";
                    *(undefined4 *)((int)asStack_138 + iVar4 + 8) = 100;
                    *(undefined1 **)((int)asStack_138 + iVar4 + 4) = &DAT_01129fc0;
                    *(undefined4 *)((int)asStack_138 + iVar4) = 0x69d860;
                    _sprintf_s(*(char **)((int)asStack_138 + iVar4 + 4),
                               *(size_t *)((int)asStack_138 + iVar4 + 8),
                               *(char **)((int)asStack_138 + iVar4 + 0xc));
                }
                // Check for a debug marker (0xdddd) and free if present
                if (*(int *)(local_110 + iVar4 + -0x10) == 0xdddd) {
                    *(CHAR **)(local_110 + iVar4 + -0xc) = local_110 + iVar4 + -0x10;
                    pCVar8 = local_110 + iVar4 + -0x10;
                    pCVar8[0] = 'u';
                    pCVar8[1] = -0x28;
                    pCVar8[2] = 'i';
                    pCVar8[3] = '\0';
                    _free(*(void **)(local_110 + iVar4 + -0xc));
                }
            }
        }
    }
    return;
}