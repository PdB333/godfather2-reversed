// FUNC_NAME: RWMoviePlayer::init
void __thiscall RWMoviePlayer::init(int this, undefined4 playerID, uint flags, undefined4 someEnum, undefined4 anotherParam)
{
    int streamObj;
    undefined4 tempHandle;
    int iVar3;
    char *modeStr;
    undefined4 *puVar5;
    // Local structures for EARS audio setup
    undefined4 soundDesc1[2]; // local_70
    undefined4 soundDesc2[2]; // local_68
    undefined4 local_60;
    undefined4 local_58;
    undefined4 local_50;
    undefined4 local_4c;
    undefined1 local_48;
    undefined4 local_44;
    undefined4 local_40;
    undefined1 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    undefined1 local_30;
    undefined4 local_2c;
    undefined4 local_28;
    undefined1 local_24;
    undefined4 *local_20;
    undefined4 local_1c;
    undefined1 local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined1 local_c;

    // Store parameters into instance fields
    *(uint *)(this + 0x40) = flags;
    *(undefined4 *)(this + 4) = playerID;
    *(undefined4 *)(this + 0x44) = someEnum;
    *(undefined4 *)(this + 0x48) = anotherParam;

    // Initialize audio section based on flags high nibble
    FUN_00620040(flags >> 4, someEnum);

    // Select mode string based on global flag at 0x01223454+0x15
    if (*(char *)(DAT_01223454 + 0x15) == '\0') {
        modeStr = "MUSIC_UI";
    } else {
        modeStr = "MOVIE_PLAYER";
    }
    *(undefined4 *)(this + 0x3c) = FUN_004dafd0(modeStr);

    FUN_00c9eac0(); // likely enter critical section or lock

    // Check if some sub-object at (this+8) is initialized
    if (*(int *)(*(int *)(this + 8) + 0x28) == 0) {
        FUN_00ca3ee0(); // possibly a creator/initializer
    }

    tempHandle = FUN_00caa1c0(); // get current audio environment handle
    local_4c = FUN_00c9ceb0(tempHandle); // convert to something

    // Build an EARS sound descriptor structure (local_50, etc.)
    local_48 = (undefined1)someEnum;
    local_50 = 0;
    local_40 = FUN_00c9cd50(0x52636830); // "Rch0" - reverb channel hash
    local_44 = 0;
    local_3c = (undefined1)someEnum;
    local_34 = FUN_00c9cd50(0x52737030); // "Rsp0" - response channel hash
    local_38 = 0;
    local_30 = (undefined1)someEnum;
    local_28 = FUN_00c9cd50(0x47614630); // "Gaf0" - gain factor hash
    local_24 = (undefined1)someEnum;
    local_2c = 0;
    local_1c = FUN_00c9cd50(0x506e3231); // "Pn21" - pan? hash

    puVar5 = soundDesc2;
    tempHandle = FUN_00c9cd50(0x506e3231); // same hash
    FUN_00c9cba0(*(undefined4 *)(this + 8), tempHandle, puVar5); // fill soundDesc2

    local_58 = 0;
    local_20 = soundDesc2;
    soundDesc2[0] = DAT_0110ae38; // some global constant
    local_60 = DAT_00e44720; // another global constant
    local_18 = 6;
    local_10 = FUN_00c9cd50(0x53656e30); // "Sen0" - send/receive? hash
    local_14 = 0;
    local_c = 6;

    // Create a stream object (0 = type?, 6 = priority?, &local_50 = descriptor, 0 = flags)
    streamObj = FUN_00ca55a0(*(undefined4 *)(this + 8), 0, 6, &local_50, 0);
    *(int *)(this + 0x9c) = streamObj;

    // Name the stream
    *(char **)(streamObj + 0x14) = "RWMovie Voice";

    streamObj = *(int *)(this + 0x9c);
    FUN_00c9cbe0(*(undefined4 *)(this + 8), local_10, 0, soundDesc1);
    soundDesc1[0] = FUN_00c9ebd0(); // get current time
    FUN_00c9cd40(0, soundDesc1); // set time marker?

    // Store audio channel properties from the stream object
    *(undefined4 *)(this + 0xa8) = *(undefined4 *)(streamObj + 0x58);
    *(undefined4 *)(this + 0xa0) = *(undefined4 *)(streamObj + 0x50);
    *(undefined4 *)(this + 0xa4) = *(undefined4 *)(streamObj + 0x5c);
    iVar3 = *(int *)(streamObj + 0x60);
    *(int *)(this + 0xac) = iVar3;
    *(undefined4 *)(this + 0xb0) = *(undefined4 *)(streamObj + 100);

    if (iVar3 != 0) {
        FUN_00ca4e90(1, 0); // set master volume? (enable, value)
    }

    FUN_00c9eae0(); // likely leave critical section / unlock
    return;
}