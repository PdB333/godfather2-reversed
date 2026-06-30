void FUN_00659a40(undefined4 *param_1)
{
    int iVar1;
    char *_Format;

    if (param_1 == (undefined4 *)0x0) {
        _Format = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar1 = FUN_00b995f7(
            "_ARGCHK '%s' failure on line %d of file %s\n",
            "md != NULL",
            0x11,
            "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\sha224.c"
        );
        _fprintf((FILE *)(iVar1 + 0x40), _Format);
    }

    param_1[10] = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0xc1059ed8;
    param_1[3] = 0x367cd507;
    param_1[4] = 0x3070dd17;
    param_1[5] = 0xf70e5939;
    param_1[6] = 0xffc00b31;
    param_1[7] = 0x68581511;
    param_1[8] = 0x64f98fa7;
    param_1[9] = 0xbefa4fa4;

    return;
}