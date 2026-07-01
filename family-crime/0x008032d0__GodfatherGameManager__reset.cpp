// FUNC_NAME: GodfatherGameManager::reset
void __fastcall GodfatherGameManager::reset(void)
{
    // Set flag at +0x1b94 bit 0 to indicate reset in progress
    *(uint *)(this + 0x1b94) |= 1;

    // Reset various subsystems
    sub_7f4810();  // reset audio manager
    sub_7fb040();  // reset input system

    // Free and null out sub-object at +0xff0
    if (*(int *)(this + 0xff0) != 0) {
        sub_4daf90((undefined4 *)(this + 0xff0));  // delete sub-object
        *(undefined4 *)(this + 0xff0) = 0;
    }

    // Set state bytes
    *(byte *)(this + 0xff8) = 0;      // reset state byte
    *(byte *)(this + 0xff9) = 0xff;   // set max value

    // Continue resetting other subsystems
    sub_7fc9f0();  // reset network layer
    sub_7fb790();  // reset physics
    sub_7f5450();  // reset UI
    sub_7f5690();  // reset camera
}