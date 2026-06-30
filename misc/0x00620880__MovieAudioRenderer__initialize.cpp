// FUNC_NAME: MovieAudioRenderer::initialize
void __thiscall MovieAudioRenderer::initialize(void) {
    char cVar1;
    int local_18[2]; // [0-7] output buffer, size 8 bytes
    float local_10;  // temporary float
    float local_8;   // temporary float

    EA_BeginInit();
    // m_handle8 at +0x8, m_pSomeStruct at +0xa0, then +0x10 from that struct
    EA_SetAudioData(*(int*)(this + 8), *(int*)(*(int*)(this + 0xa0) + 0x10), 0, local_18);
    // Convert signed int at +0x40 to float, with negative handling
    local_10 = (float)*(int*)(this + 0x40);
    if (*(int*)(this + 0x40) < 0) {
        local_10 = local_10 + g_fConversionConstant; // DAT_00e44578
    }
    // Convert signed int at +0x44 to float, with negative handling
    local_8 = (float)*(int*)(this + 0x44);
    if (*(int*)(this + 0x44) < 0) {
        local_8 = local_8 + g_fConversionConstant; // DAT_00e44578
    }
    local_18[0] = 0;
    EA_InitSomething(0, local_18);
    // Register audio renderer callback; context at +0xc, callback at 0x00620a90
    cVar1 = EA_RegisterRenderCallback(this + 0xc, FUN_00620a90, this, "RWMovie AudioRenderer_EARS", 0, 0);
    if (cVar1 == '\0') {
        *(char*)(this + 0x24) = 1; // Set flag at +0x24 to 1 on failure
    }
    EA_EndInit();
    return;
}