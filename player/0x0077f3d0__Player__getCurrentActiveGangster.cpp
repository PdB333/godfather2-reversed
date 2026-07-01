// FUNC_NAME: Player::getCurrentActiveGangster
int __fastcall Player::getCurrentActiveGangster(int thisPtr)
{
    uint gangsterCount = *(uint *)(thisPtr + 0x744); // +0x744: number of gangsters in player's crew
    uint index = 0;
    
    if (gangsterCount != 0) {
        do {
            int gangster = FUN_00704110(index); // likely getGangsterByIndex(index)
            if ((gangster != 0) &&
                (*(char *)(gangster + 0x1aa) == '\x02') && // +0x1AA: some state flag (e.g., alive/active)
                (*(char *)(gangster + 0x1a8) == '\x02')) { // +0x1A8: another state flag (e.g., following/controlled)
                return gangster;
            }
            index = index + 1;
        } while (index < gangsterCount);
    }
    return 0;
}