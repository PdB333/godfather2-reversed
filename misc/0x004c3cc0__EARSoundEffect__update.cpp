// FUNC_NAME: EARSoundEffect::update

void __thiscall EARSoundEffect::update(void)
{
    uint8_t soundHandle = *(uint8_t*)(this + 0x24);  // +0x24: sound resource identifier (byte-sized index)
    bool isPlaying = FUN_00497040(soundHandle);  // check if sound is still active
    if (!isPlaying) {
        int state = *(int*)(this + 0x48);  // +0x48: current state (0=idle, 1=playing, 2=stopping?)
        if (state == 2) {
            FUN_00496640(0xFF, *(undefined4*)(this + 0x4c));  // +0x4c: fade duration in ms; 0xFF = stop all channels
        }
        FUN_004970b0(soundHandle);  // release sound handle
    }
    return;
}