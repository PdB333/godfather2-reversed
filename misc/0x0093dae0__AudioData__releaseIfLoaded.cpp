// FUNC_NAME: AudioData::releaseIfLoaded

struct AudioData {
    // ... (other members before 0x5C)
    unsigned short flags; // +0x5C: bit 0 = loaded flag
};

void __thiscall AudioData::releaseIfLoaded(void)
{
    if ((this->flags & 1) != 0) {
        FUN_004086d0(&DAT_012069c4); // release the global audio resource
        this->flags &= ~1;           // clear the loaded flag
    }
}