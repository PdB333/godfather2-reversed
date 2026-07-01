// FUNC_NAME: SoundEffect::updateSound
void __thiscall SoundEffect::updateSound(int* thisPtr)
{
    // Offsets: +0x397 (char* soundName1), +0x39b (char* soundName2),
    //          +0x39f (int soundHandle), +0x4c (int soundParam)
    if (thisPtr[0x39f] == 0) {
        char* name1 = (char*)thisPtr[0x397];
        if (name1 == nullptr) {
            name1 = (char*)&DAT_0120546e;  // empty string or zero
        }
        char* name2 = (char*)thisPtr[0x39b];
        if (name2 == nullptr) {
            name2 = (char*)&DAT_0120546e;
        }
        // Load sound resource (returns handle)
        int handle = FUN_0099c060(name2, name1, 0, 0);
        thisPtr[0x39f] = handle;
    }

    if (thisPtr[0x39f] != 0) {
        // Obtain sound player/stream using handle and parameter at +0x4c
        int player = FUN_0099b090(thisPtr[0x39f], thisPtr[0x4c]);
        // Play the sound
        FUN_004608c0(player);
    }

    // Virtual call to base update (vtable+0x134) with argument 1
    (**(code**)(*thisPtr + 0x134))(1);
}