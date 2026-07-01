// FUNC_NAME: PlayerAudioSystem::updateRadioVolume
void __fastcall PlayerAudioSystem::updateRadioVolume(int *this)
{
    code *vtableFunc;
    uint bitField;
    float deltaTime;
    int previousRadioState;
    int currentRadioState;
    byte someBool;
    char gamePaused;
    int temp;
    float accumTime;

    accumTime = DAT_00d58cbc;  // global time step (maybe frame delta)
    deltaTime = DAT_012067e8 + (float)this[0xc4a];  // +0x3128: accumulated radio timer
    this[0xc4a] = (int)deltaTime;
    if (accumTime < deltaTime) {
        vtableFunc = *(code **)(*this + 0x28c);  // vtable offset 0x28c: some update/check function
        currentRadioState = this[0x7ba];  // +0x1ee8: current radio state (e.g., on/off/mode)
        this[0xc4a] = 0;  // reset timer
        someBool = (*vtableFunc)();
        bitField = this[0x929];  // +0x24a4: bitfield flags (bit 6 = radio enabled?)
        if ((((byte)(bitField >> 6) & 1) == someBool) && (this[0xc4b] == currentRadioState)) {
            if (someBool != 0) {
                FUN_007a5fe0(0);  // maybe stop/disable radio audio
                return;
            }
        }
        else {
            FUN_007a5fe0(1);  // maybe start/enable radio audio
            previousRadioState = this[0xc4b];  // +0x312c: previous radio state
            if (someBool == 0) {
                this[0x929] = this[0x929] & 0xffffffbf;  // clear bit 6
            }
            else {
                this[0x929] = this[0x929] | 0x40;  // set bit 6
            }
            this[0xc4b] = currentRadioState;  // update previous state
            temp = DAT_01129948;  // global game state pointer
            gamePaused = FUN_00842870();  // check if game is paused
            if ((gamePaused == '\0') && ((*(uint *)(temp + 0x4c) >> 5 & 1) == 0)) {
                if (((bitField >> 6 & 1) != 0) && (previousRadioState != 0)) {
                    FUN_00402050(&DAT_0112a5cc,0);  // play sound event "radio_off" maybe
                    temp = FUN_006b07e0(previousRadioState);  // get radio sound handle
                    if (temp != 0) {
                        FUN_006ae470();  // stop sound
                    }
                }
                if ((someBool != 0) && (currentRadioState != 0)) {
                    FUN_00402050(&DAT_0112a618,0);  // play sound event "radio_on" maybe
                    currentRadioState = FUN_006b07e0(currentRadioState);  // get radio sound handle
                    if (currentRadioState != 0) {
                        FUN_006ae3f0();  // start sound
                        return;
                    }
                }
            }
        }
    }
    return;
}