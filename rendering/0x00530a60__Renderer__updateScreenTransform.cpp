// FUNC_NAME: Renderer::updateScreenTransform
void __fastcall Renderer::updateScreenTransform(int this)
{
    uint uVar1;
    int iVar2;
    undefined1 *puVar3;
    int iVar4;
    undefined4 uVar5;
    int iVar6;
    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    
    FUN_00612a60(); // likely some initialization or state check
    iVar6 = *(int *)(this + 0x14); // +0x14: current render mode/state
    uVar5 = DAT_01219920; // global render target width
    if (iVar6 != DAT_012198f0) { // compare with some render mode constant
        if (iVar6 != *(int *)(this + 0x108)) { // +0x108: another render mode
            if (iVar6 == DAT_012198f8) { // specific render mode (e.g., fullscreen)
                FUN_0060add0(iVar6, DAT_0121991c, this + 0xc0); // set viewport dimensions
                FUN_0060b2f0(*(undefined4 *)(this + 0x14), DAT_01219910, *(undefined4 *)(this + 0xa4)); // set projection matrix
                iVar6 = DAT_0121992c; // another global constant
            }
            else {
                if (iVar6 != DAT_012198fc) { // another render mode
                    if (iVar6 == *(int *)(this + 0x114)) { // +0x114: custom render mode
                        FUN_0060b2f0(iVar6, *(undefined4 *)(this + 0xf8), *(undefined4 *)(this + 0xa4)); // set projection with custom params
                    }
                    goto LAB_00530a94;
                }
                FUN_0060b2f0(iVar6, DAT_01219914, *(undefined4 *)(this + 0xa4)); // set projection for another mode
                iVar6 = DAT_01219930; // another global constant
            }
            if (iVar6 != 0) {
                iVar2 = *(int *)(this + 0x10); // +0x10: current display mode
                local_20 = 0.0;
                local_1c = 0.0;
                local_18 = 0.0;
                local_14 = 0.0;
                if (((iVar2 == DAT_01219908) && (iVar4 = DAT_01219928, DAT_01219928 != 0)) ||
                   ((iVar2 == DAT_01219900 && (iVar4 = DAT_01219924, DAT_01219924 != 0)))) {
                    FUN_0060add0(iVar2, iVar4, &local_20); // get display mode dimensions
                }
                uVar1 = *(uint *)(this + 0xa4); // +0xa4: render target index
                if (uVar1 < 0x1000) {
                    puVar3 = &DAT_011a0f28 + uVar1 * 0x38; // render target info array (0x38 bytes per entry)
                }
                else {
                    puVar3 = (undefined1 *)0x0;
                }
                local_20 = DAT_00e2b1a4 / (float)*(ushort *)(puVar3 + 2); // width / render target width
                if (uVar1 < 0x1000) {
                    puVar3 = &DAT_011a0f28 + uVar1 * 0x38;
                }
                else {
                    puVar3 = (undefined1 *)0x0;
                }
                local_1c = DAT_00e2b1a4 / (float)*(ushort *)(puVar3 + 4); // height / render target height
                local_18 = local_20 * DAT_00e2cd54; // scale factor for width
                local_14 = local_1c * DAT_00e2cd54; // scale factor for height
                FUN_0060add0(*(undefined4 *)(this + 0x14), iVar6, &local_20); // set final screen transform
                return;
            }
            goto LAB_00530a94;
        }
        uVar5 = *(undefined4 *)(this + 0xfc); // +0xfc: custom width
    }
    FUN_0060add0(iVar6, uVar5, this + 0xc0); // set viewport with default dimensions
LAB_00530a94:
    iVar6 = *(int *)(this + 0x10);
    if (((iVar6 == DAT_01219908) && (iVar2 = DAT_01219928, DAT_01219928 != 0)) ||
       ((iVar6 == DAT_01219900 && (iVar2 = DAT_01219924, DAT_01219924 != 0)))) {
        FUN_0060add0(iVar6, iVar2, &DAT_011f6680); // set display mode dimensions from global
    }
    return;
}