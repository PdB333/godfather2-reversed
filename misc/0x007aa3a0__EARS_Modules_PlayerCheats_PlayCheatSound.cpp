// Xbox PDB: EARS_Modules_PlayerCheats_PlayCheatSound
// FUNC_NAME: UISoundPlayer::playSound
void UISoundPlayer::playSound(bool playDoorUnlock)
{
    // Virtual function at vtable offset 0xAC: plays an audio file with an unknown flag (0)
    void (UISoundPlayer::*playAudio)(const char*, int) = *(void (UISoundPlayer::**)(const char*, int))(*reinterpret_cast<int*>(this) + 0xAC);
    if (playDoorUnlock)
    {
        (this->*playAudio)("sx_glb_door_unlocked_01.emx", 0);
    }
    else
    {
        (this->*playAudio)("sx_fehudui_skillpoint_no_01_l.emx", 0);
        (this->*playAudio)("sx_fehudui_skillpoint_no_01_r.emx", 0);
    }
}