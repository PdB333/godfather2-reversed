// FUNC_NAME: CharacterModel::setImportantBoneOffsets
void __thiscall CharacterModel::setImportantBoneOffsets(uint32_t param_2) {
    // Array of bone offsets: head (0x18), chest (0x28), pelvis (0x38)
    uint32_t boneOffsets[3] = {0x18, 0x28, 0x38};
    
    // Register these offsets with the animation system
    // FUN_004eba90 likely stores these offsets in a lookup table for bone transform retrieval
    FUN_004eba90(this, param_2, boneOffsets, 3);
}