// FUNC_NAME: EntityUIComponent::initializeBackground
void __fastcall EntityUIComponent::initializeBackground(int this)
{
    int iVar1;
    char *pcVar2;
    uint uVar3;
    char *pcVar4;
    undefined4 uVar5;
    int *ppiVar6;

    uVar3 = 0;
    // If the global background list has elements
    if (*(uint *)(g_pBackgroundManager + 0x2c) != 0) {
        ppiVar6 = *(int **)(g_pBackgroundManager + 0x28);
        do {
            // Compare entity ID (at +0x28 of each entry) with this object's entity ID (+0x2c0)
            if (*(int *)(*ppiVar6 + 0x28) == *(int *)(this + 0x2c0)) {
                if (uVar3 != 0xffffffff) {
                    iVar1 = (*(int **)(g_pBackgroundManager + 0x28))[uVar3];
                    // Status: found – set to 3 (active/loaded)
                    *(undefined4 *)(this + 0x2c4) = 3;
                    // Copy background related fields from the found entry
                    *(undefined4 *)(this + 0x2cc) = *(undefined4 *)(iVar1 + 0x2c);
                    *(undefined4 *)(this + 0x2d0) = *(undefined4 *)(iVar1 + 0x34);
                    uVar5 = *(undefined4 *)(iVar1 + 0x38);
                    *(undefined4 *)(this + 0x2d8) = uVar5;
                    // Build background texture name by appending "_background" to the base name
                    pcVar2 = "_background";
                    do {
                        pcVar4 = pcVar2;
                        pcVar2 = pcVar4 + 1;
                    } while (*pcVar4 != '\0');
                    uVar5 = buildBackgroundTexturePath(uVar5, "_background", pcVar4 + -0xd878f4);
                    *(undefined4 *)(this + 0x2c8) = uVar5;
                    return;
                }
                break;
            }
            uVar3 = uVar3 + 1;
            ppiVar6 = ppiVar6 + 1;
        } while (uVar3 < *(uint *)(g_pBackgroundManager + 0x2c));
    }
    // Not found: default values
    *(undefined4 *)(this + 0x2c4) = 1;   // status = inactive/initial
    *(undefined4 *)(this + 0x2cc) = 0;
    *(undefined4 *)(this + 0x2d0) = 0;
    *(undefined4 *)(this + 0x2d8) = 0;
    *(undefined4 *)(this + 0x2c8) = 0;   // clear background texture
    return;
}