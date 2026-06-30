// FUNC_NAME: AudioManager::popSoundFromQueue
void AudioManager::popSoundFromQueue(uint soundTypeMask)
{
    int index;

    // Pop from queue 1 (bit 0) - likely SFX or music
    if (((soundTypeMask & 1) != 0) && (0 < DAT_011f6bf0)) {
        DAT_011f6bf0 = DAT_011f6bf0 + -1;
        index = DAT_011f6bf0 * 0x40;
        // Copy 16 dwords (64 bytes) from queue to active sound slot
        _DAT_011f69b0 = *(undefined4 *)(&DAT_011f6c00 + index);
        _DAT_011f69b4 = *(undefined4 *)(index + 0x11f6c04);
        _DAT_011f69b8 = *(undefined4 *)(index + 0x11f6c08);
        uRam011f69bc = *(undefined4 *)(index + 0x11f6c0c);
        _DAT_011f69c0 = *(undefined4 *)(&DAT_011f6c10 + index);
        _DAT_011f69c4 = *(undefined4 *)(index + 0x11f6c14);
        _DAT_011f69c8 = *(undefined4 *)(index + 0x11f6c18);
        uRam011f69cc = *(undefined4 *)(index + 0x11f6c1c);
        _DAT_011f69d0 = *(undefined4 *)(&DAT_011f6c20 + index);
        _DAT_011f69d4 = *(undefined4 *)(index + 0x11f6c24);
        _DAT_011f69d8 = *(undefined4 *)(index + 0x11f6c28);
        uRam011f69dc = *(undefined4 *)(index + 0x11f6c2c);
        _DAT_011f69e0 = *(undefined4 *)(&DAT_011f6c30 + index);
        uRam011f69e4 = *(undefined4 *)(index + 0x11f6c34);
        uRam011f69e8 = *(undefined4 *)(index + 0x11f6c38);
        uRam011f69ec = *(undefined4 *)(index + 0x11f6c3c);
    }
    // Pop from queue 2 (bit 1) - likely voice/dialog
    if ((soundTypeMask & 2) != 0) {
        if (0 < DAT_011f7010) {
            DAT_011f7010 = DAT_011f7010 + -1;
            index = DAT_011f7010 * 0x40;
            _DAT_011f69f0 = *(undefined4 *)(&DAT_011f7020 + index);
            uRam011f69f4 = *(undefined4 *)(index + 0x11f7024);
            _DAT_011f69f8 = *(undefined4 *)(index + 0x11f7028);
            uRam011f69fc = *(undefined4 *)(index + 0x11f702c);
            _DAT_011f6a00 = *(undefined4 *)(&DAT_011f7030 + index);
            uRam011f6a04 = *(undefined4 *)(index + 0x11f7034);
            _DAT_011f6a08 = *(undefined4 *)(index + 0x11f7038);
            uRam011f6a0c = *(undefined4 *)(index + 0x11f703c);
            _DAT_011f6a10 = *(undefined4 *)(&DAT_011f7040 + index);
            uRam011f6a14 = *(undefined4 *)(index + 0x11f7044);
            _DAT_011f6a18 = *(undefined4 *)(index + 0x11f7048);
            uRam011f6a1c = *(undefined4 *)(index + 0x11f704c);
            _DAT_011f6a20 = *(undefined4 *)(&DAT_011f7050 + index);
            uRam011f6a24 = *(undefined4 *)(index + 0x11f7054);
            _DAT_011f6a28 = *(undefined4 *)(index + 0x11f7058);
            uRam011f6a2c = *(undefined4 *)(index + 0x11f705c);
        }
        // Pop from queue 3 (bit 2) - likely ambient/environment
        if (0 < DAT_011f6e00) {
            DAT_011f6e00 = DAT_011f6e00 + -1;
            index = DAT_011f6e00 * 0x40;
            _DAT_011f6b30 = *(undefined4 *)(&DAT_011f6e10 + index);
            uRam011f6b34 = *(undefined4 *)(index + 0x11f6e14);
            uRam011f6b38 = *(undefined4 *)(index + 0x11f6e18);
            uRam011f6b3c = *(undefined4 *)(index + 0x11f6e1c);
            _DAT_011f6b40 = *(undefined4 *)(&DAT_011f6e20 + index);
            uRam011f6b44 = *(undefined4 *)(index + 0x11f6e24);
            uRam011f6b48 = *(undefined4 *)(index + 0x11f6e28);
            uRam011f6b4c = *(undefined4 *)(index + 0x11f6e2c);
            _DAT_011f6b50 = *(undefined4 *)(&DAT_011f6e30 + index);
            uRam011f6b54 = *(undefined4 *)(index + 0x11f6e34);
            uRam011f6b58 = *(undefined4 *)(index + 0x11f6e38);
            uRam011f6b5c = *(undefined4 *)(index + 0x11f6e3c);
            _DAT_011f6b60 = *(undefined4 *)(&DAT_011f6e40 + index);
            uRam011f6b64 = *(undefined4 *)(index + 0x11f6e44);
            uRam011f6b68 = *(undefined4 *)(index + 0x11f6e48);
            uRam011f6b6c = *(undefined4 *)(index + 0x11f6e4c);
        }
    }
    // Pop from queue 4 (bit 2) - likely UI sounds
    if (((soundTypeMask & 4) != 0) && (0 < DAT_011f7220)) {
        DAT_011f7220 = DAT_011f7220 + -1;
        index = DAT_011f7220 * 0x40;
        _DAT_011f6a30 = *(undefined4 *)(&DAT_011f7230 + index);
        uRam011f6a34 = *(undefined4 *)(index + 0x11f7234);
        uRam011f6a38 = *(undefined4 *)(index + 0x11f7238);
        uRam011f6a3c = *(undefined4 *)(index + 0x11f723c);
        _DAT_011f6a40 = *(undefined4 *)(&DAT_011f7240 + index);
        DAT_011f6a44 = *(undefined4 *)(index + 0x11f7244);
        uRam011f6a48 = *(undefined4 *)(index + 0x11f7248);
        uRam011f6a4c = *(undefined4 *)(index + 0x11f724c);
        _DAT_011f6a50 = *(undefined4 *)(&DAT_011f7250 + index);
        uRam011f6a54 = *(undefined4 *)(index + 0x11f7254);
        DAT_011f6a58 = *(undefined4 *)(index + 0x11f7258);
        DAT_011f6a5c = *(undefined4 *)(index + 0x11f725c);
        _DAT_011f6a60 = *(undefined4 *)(&DAT_011f7260 + index);
        uRam011f6a64 = *(undefined4 *)(index + 0x11f7264);
        DAT_011f6a68 = *(undefined4 *)(index + 0x11f7268);
        DAT_011f6a6c = *(undefined4 *)(index + 0x11f726c);
    }
    // Handle streaming state - if streaming is active, call appropriate handler
    if ((DAT_011f7430 & 1) != 0) {
        if ((soundTypeMask & 1) == 1) {
            FUN_00614a50(); // handleStreamingMusic
            return;
        }
        FUN_00614910(); // handleStreamingVoice
    }
    return;
}