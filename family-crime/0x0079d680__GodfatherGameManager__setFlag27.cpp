// FUNC_NAME: GodfatherGameManager::setFlag27
void __thiscall GodfatherGameManager::setFlag27(int this, char enable)
{
    if (enable != '\0') {
        // Set bit 0x8000000 (flag) at offset +0x249c
        *(uint *)(this + 0x249c) |= 0x8000000u;
        return;
    }
    // Clear the flag and call internal deactivation routine
    *(uint *)(this + 0x249c) &= 0xF7FFFFFFu;
    FUN_00787a90(); // likely "reset" or "disable" function
    return;
}