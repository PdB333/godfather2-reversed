// FUNC_NAME: ShaderEffect::initConstantHandles
void __fastcall ShaderEffect::initConstantHandles(int this) {
    // Retrieve handle for the "inColor" shader constant
    // +0x60: stored as member variable
    // *(this + -0xa0) likely points to the effect object or device (e.g., ID3DXEffect*)
    undefined4 constantHandleInColor = FUN_0060a580(*(undefined4 *)(this + -0xa0), "inColor");
    *(undefined4 *)(this + 0x60) = constantHandleInColor;

    // Retrieve handle for the "ModelViewProj" shader constant
    // stored at this - 0x60 (negative offset) - this is unusual; possibly an error in decompilation? 
    // We'll keep as is, but note that negative offsets often indicate a base pointer or a different member.
    undefined4 constantHandleModelViewProj = FUN_0060a580(*(undefined4 *)(this + -0xa0), "ModelViewProj");
    *(undefined4 *)(this + -0x60) = constantHandleModelViewProj;

    return;
}