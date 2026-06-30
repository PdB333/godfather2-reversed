// FUNC_NAME: AudioManager::updateChannels
void __thiscall AudioManager::updateChannels(void) {
    int iVar1;
    int iVar2;
    float10 fVar3;

    iVar2 = 0;
    if (0 < this->channelCount) {  // this+0x3e0
        do {
            iVar1 = isChannelActive();  // thunk_FUN_004ab300
            if (iVar1 != 0) {
                fVar3 = (float10)getChannelFloat();  // FUN_004aabd0
                setChannelFloat((float)fVar3);       // FUN_004aa8c0
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 < this->channelCount);
    }
    return;
}