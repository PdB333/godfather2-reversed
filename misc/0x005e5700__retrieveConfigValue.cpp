// FUNC_NAME: retrieveConfigValue
int retrieveConfigValue(void)
{
    uint *lookupResult;        // pointer to result data
    byte successFlag;          // output parameter for lookup function
    uint unusedLocal;          // not used

    successFlag = 0;
    unusedLocal = 0;
    lookupResult = (uint *)lookupByKey(DAT_01223514, &successFlag);
    if (lookupResult != (uint *)0x0) {
        return *lookupResult;
    }
    return 0;
}