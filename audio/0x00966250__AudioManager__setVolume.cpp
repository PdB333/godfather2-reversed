// FUNC_NAME: AudioManager::setVolume
void AudioManager::setVolume(int deltaVolume)
{
    int globalVolume = DAT_01129930;
    if (deltaVolume < 0) {
        switch(*(undefined4 *)(DAT_01129930 + 0xdc)) { // +0xdc: currentVolumeType
        case 1: // Master volume
        case 6: // Voice volume
            uVar3 = 9;
            break;
        default:
            uVar3 = 10;
        }
        FUN_00966130(-deltaVolume, DAT_01129930 + 0xd4, DAT_01129930 + 0xc4, uVar3);
        return;
    }
    if (0 < deltaVolume) {
        uVar3 = *(undefined4 *)(DAT_01129930 + 0xe0); // +0xe0: maxVolume
        uVar2 = FUN_00962e40(uVar3);
        FUN_009661c0(deltaVolume, globalVolume + 0xd4, globalVolume + 0xc4, uVar2, uVar3);
    }
    return;
}