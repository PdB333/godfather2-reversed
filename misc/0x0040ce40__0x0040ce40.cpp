extern "C" undefined* FUN_0040ce40()
{
    undefined2 uVar1;
    DWORD DVar2;

    _DAT_01223a88 = 0;
    _DAT_01223a8c = 0x18000000;
    DAT_011625d0 = 0;
    _DAT_01223a80 = 0x18000000;
    _DAT_01223a84 = 0x18000000;

    DVar2 = GetEnvironmentVariableA("EARS_GAMEROOT", &DAT_01223b10, 0x80);
    uVar1 = s_runtime_data_win_ntsc_en__00e2f334._24_2_;

    if (DVar2 == 0) {
        _DAT_01223b10 = &LAB_005c3a43;
        DVar2 = 3;
    }

    *reinterpret_cast<undefined8*>(&DAT_01223b10 + DVar2) =
        s_runtime_data_win_ntsc_en__00e2f334._0_8_;
    *reinterpret_cast<undefined8*>((int)&DAT_01223b13 + DVar2 + 5) =
        s_runtime_data_win_ntsc_en__00e2f334._8_8_;
    *reinterpret_cast<undefined8*>((int)&DAT_01223b1b + DVar2 + 5) =
        s_runtime_data_win_ntsc_en__00e2f334._16_8_;
    *reinterpret_cast<undefined2*>((int)&DAT_01223b23 + DVar2 + 5) =
        uVar1;

    return &DAT_01223a80;
}