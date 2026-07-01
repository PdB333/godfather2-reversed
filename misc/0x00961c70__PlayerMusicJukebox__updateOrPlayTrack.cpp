// FUNC_NAME: PlayerMusicJukebox::updateOrPlayTrack
void __fastcall PlayerMusicJukebox::updateOrPlayTrack(int this)
{
    int local_c;
    int local_8;
    byte local_4;

    // Calculate song index based on some field at +0x60
    FUN_00961a50((*(int *)(this + 0x60) + 4U) % 5);
    
    local_c = DAT_011302b0;
    local_8 = 0;
    local_4 = 0;
    
    // Call some initialization/reset function
    FUN_00408a00(&local_c, 0);
    
    return;
}