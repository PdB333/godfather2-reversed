// FUNC_NAME: getLevelAttributeValue
// Function at 0x006f1890 returns a fixed integer based on input level (1-9).
// Used by FUN_006f2890, likely for level-dependent values (e.g., health, damage, reputation).
int getLevelAttributeValue(int levelIndex)
{
    switch (levelIndex)
    {
    case 1:
        return 400;
    case 2:
        return 600;
    case 3:
        return 1000;
    case 4:
        return 1200; // 0x4b0
    case 5:
        return 2000;
    case 6:
        return 2200; // 0x898
    case 7:
        return 2600; // 0xa28
    case 8:
        return 2800; // 0xaf0
    case 9:
        return 3000;
    default:
        return 0;
    }
}