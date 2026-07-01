// FUNC_NAME: Player::getHeadshotTransform
void Player::getHeadshotTransform(float4x4* transform) {
    // Get bone transforms for head, neck, and spine (likely)
    int headBoneIndex = FUN_00471610();  // getBoneIndex("head")
    int neckBoneIndex = FUN_00471610();  // getBoneIndex("neck")  
    int spineBoneIndex = FUN_00471610(); // getBoneIndex("spine")
    
    // Read world matrices from bone transforms
    // +0x30, +0x34, +0x38 are standard offsets for bone world matrix rows (row 0, 1, 2)
    transform->row3 = *(float4*)(spineBoneIndex + 0x30); // z-axis (forward) from spine
    transform->row2 = *(float4*)(neckBoneIndex + 0x34);  // y-axis (up) from neck
    transform->row1 = *(float4*)(headBoneIndex + 0x38);  // x-axis (right) from head
    
    // Position is from global data (likely latest camera position or player position)
    transform->row0 = _DAT_00d5780c; // position vector
}