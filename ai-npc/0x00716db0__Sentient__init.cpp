// FUNC_NAME: Sentient::init
void __thiscall Sentient::init(Sentient* this, int owner)
{
    int randomInt;
    float randomFloat;
    float baseFloat;

    this->owner = owner; // +0x18
    clearObjectMem(this); // FUN_007ee2e0 - zeros object memory
    if (this->owner != 0) {
        globalRegisterEntity(DAT_01131018); // FUN_0043b870 - register with global manager
    }
    setTimer(this + 0xc, 0x8000); // FUN_009aefd0 - initialise timer/interval
    this->secondaryOwner = owner; // +0x318
    initSubsystemA(owner); // FUN_0071a990
    initSubsystemB(owner); // FUN_0071df90
    initSubsystemC(owner); // FUN_00714410
    // Call virtual function from dispatch table at this+0x144
    (*(void (**)(int))(*(int*)(this + 0x144) + 0x10))(owner);
    this->bufferPtr = this + 0x1bc; // +0x150 - internal buffer pointer
    clearSubObjectMem(this + 0x30c); // FUN_007ee2e0 - clear sub-object
    baseFloat = g_initialRandomBase; // DAT_00d61aac
    if ((*(uint*)(owner + 0x1f58) >> 6 & 1) == 0) {
        this->randomBase = g_randomBase; // _DAT_00d5780c
        randomInt = rand();
        baseFloat = ((float)randomInt * g_randScale * g_randRange - g_randOffset) + this->randomBase;
    }
    this->randomFloat = baseFloat; // +0x368
    this->extraRandom = getRandomValue(); // FUN_0072f960 -> +0x370
}