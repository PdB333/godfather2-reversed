// FUNC_NAME: getResourceSetId
int getResourceSetId(void)
{
    int result = 0;
    int platformOrLanguage = getGlobalEnum(); // FUN_00800b60 - returns 0-4
    switch (platformOrLanguage) {
        case 0:
        case 1:
            return 0x52e7d170;
        case 2:
        case 3:
        case 4:
            result = 0x84343fc4;
            break;
    }
    return result;
}