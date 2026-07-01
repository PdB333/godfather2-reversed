// FUNC_NAME: ParameterManager::getUIntParam
bool ParameterManager::getUIntParam(uint param1, uint param2, uint *outParam3)
{
    uint value = 0;
    bool success = FUN_004480d0(param1, param2, &value);
    if (success) {
        *outParam3 = value;
        return true;
    }
    *outParam3 = 0;
    return false;
}