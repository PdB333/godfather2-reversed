// FUNC_NAME: ModelInstance::applyTextureOverride
void __thiscall ModelInstance::applyTextureOverride(int this) {
    int iVar1;  // pointer to global game state
    int iVar2;  // pointer to mesh/render component
    undefined4 uVar3; // texture handle

    iVar1 = DAT_0112aa1c; // Global game state singleton
    iVar2 = FUN_00786720(this + 0x48); // get mesh from +0x48 offset (e.g., RenderComponent)
    if (iVar2 != 0) {
        // Decide which texture to use based on bit 1 of flags at +0x74
        if ((*(uint *)(this + 0x74) >> 1 & 1) == 0) {
            // Use texture from global state +0x2c88 -> +0x88 (e.g., default texture)
            uVar3 = *(undefined4 *)(*(int *)(iVar1 + 0x2c88) + 0x88);
        } else {
            // Use texture from this->+0x28 -> +0x1ed4 (e.g., custom texture override)
            uVar3 = *(undefined4 *)(*(int *)(this + 0x28) + 0x1ed4);
        }
        // Apply texture to the mesh's material slot at +0x20
        FUN_008fb600(uVar3, *(undefined4 *)(iVar2 + 0x20));
    }
    return;
}