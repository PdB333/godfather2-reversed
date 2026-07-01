// FUNC_NAME: Vehicle::isPlayerControlled
bool __fastcall Vehicle::isPlayerControlled(int this)
{
    uint local_8;
    byte *local_4;
    char cVar1;

    local_8 = 0;
    local_4 = (byte *)0x0;
    cVar1 = FUN_00865830(2, 1, *(int *)(this + 0x5c) + 0x1050, &DAT_00d75f24, &local_8);
    if ((((cVar1 != '\0') && (local_4 != (byte *)0x0)) && (local_8 != 0)) &&
       ((*(char *)(local_8 + 6) == '\x02' && ((*local_4 & 2) != 0)))) {
        return false;
    }
    return true;
}