// FUNC_NAME: Player::updateCutsceneFlag
void __fastcall Player::updateCutsceneFlag(Player* this) {
    int objectPtr;
    
    // Get object from entity ID at offset +0x270
    objectPtr = FUN_006b07e0(*(int*)((char*)this + 0x270));
    if (objectPtr != 0) {
        // Check if the object's class ID at (+0x180)->+0x40 matches a known constant
        if (*(int*)(*(int*)((char*)objectPtr + 0x180) + 0x40) == 0x637b907) {
            // Clear bit 19 (0x80000) of flag at offset 700 (0x2BC)
            *(unsigned int*)((char*)this + 700) &= 0xfff7ffff;
            // Check global game state (DAT_0112af98)
            objectPtr = FUN_0043b870(DAT_0112af98);
            if (objectPtr != 0) {
                FUN_007894b0(); // Handle cutscene-related action
                return;
            }
        }
    }
    return;
}