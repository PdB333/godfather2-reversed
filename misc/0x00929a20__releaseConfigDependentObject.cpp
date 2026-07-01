// FUNC_NAME: releaseConfigDependentObject
void releaseConfigDependentObject(uint configKey, uint defaultString, uint* trueObjectPtr, uint* falseObjectPtr)
{
    // Static buffer for reading a single-character config value
    static char configChar = '\0';

    configChar = '\0';
    // Retrieve config string; likely writes first character into configChar
    getConfigString(configKey, &configChar, defaultString, 0);

    // If config value is not "1", use the false object pointer instead
    if (configChar != '1') {
        trueObjectPtr = falseObjectPtr;
    }

    // Dereference to get the object pointer to release
    uint objectToRelease = *trueObjectPtr;
    // Release the object (safe delete, sets pointer to null)
    releaseObject(&objectToRelease, 0);
}