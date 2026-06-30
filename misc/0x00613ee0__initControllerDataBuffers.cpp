// FUNC_NAME: initControllerDataBuffers
void initControllerDataBuffers(void)
{
    // Zero out two 64-byte blocks of controller data at fixed global addresses.
    // First block at 0x011f69f0 (likely an array of 4 controller slot structures, each 16 bytes? or 8 * 8 bytes?).
    // The constant DAT_00e2b1a4 is known to be 0 (null pointer sentinel).
    *(undefined4*)0x011f69f0 = 0;
    *(undefined4*)0x011f69f4 = 0;
    *(undefined4*)0x011f69f8 = 0;
    *(undefined4*)0x011f69fc = 0;
    *(undefined4*)0x011f6a00 = 0;
    *(undefined4*)0x011f6a04 = 0;
    *(undefined4*)0x011f6a08 = 0;
    *(undefined4*)0x011f6a0c = 0;
    *(undefined4*)0x011f6a10 = 0;
    *(undefined4*)0x011f6a14 = 0;
    *(undefined4*)0x011f6a18 = 0;
    *(undefined4*)0x011f6a1c = 0;
    *(undefined4*)0x011f6a20 = 0;
    *(undefined4*)0x011f6a24 = 0;
    *(undefined4*)0x011f6a28 = 0;
    *(undefined4*)0x011f6a2c = 0;

    // Second block at 0x011f6b30 (same structure layout).
    *(undefined4*)0x011f6b30 = 0;
    *(undefined4*)0x011f6b34 = 0;
    *(undefined4*)0x011f6b38 = 0;
    *(undefined4*)0x011f6b3c = 0;
    *(undefined4*)0x011f6b40 = 0;
    *(undefined4*)0x011f6b44 = 0;
    *(undefined4*)0x011f6b48 = 0;
    *(undefined4*)0x011f6b4c = 0;
    *(undefined4*)0x011f6b50 = 0;
    *(undefined4*)0x011f6b54 = 0;
    *(undefined4*)0x011f6b58 = 0;
    *(undefined4*)0x011f6b5c = 0;
    *(undefined4*)0x011f6b60 = 0;
    *(undefined4*)0x011f6b64 = 0;
    *(undefined4*)0x011f6b68 = 0;
    *(undefined4*)0x011f6b6c = 0;

    // If a global initialization flag (bit 0 of 0x011f7430) is already set,
    // perform additional setup (deeper controller initialization).
    if ((*(byte*)0x011f7430 & 1) != 0) {
        FUN_00614ab0(); // likely secondary init, e.g., allocate or hook input devices
    }
}