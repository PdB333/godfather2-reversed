extern "C" unsigned char* FUN_0040cf00()
{
    if ((_DAT_01223d30 & 1) == 0) {
        _DAT_01223d30 = _DAT_01223d30 | 1;
        FUN_0040ce40();
    }

    return &DAT_01223a80;
}