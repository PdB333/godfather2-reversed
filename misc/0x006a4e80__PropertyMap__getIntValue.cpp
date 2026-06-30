// FUNC_NAME: PropertyMap::getIntValue

bool __thiscall PropertyMap::getIntValue(int key, int* outValue)
{
    int value;
    bool success;

    value = 0;
    success = this->internalGetIntValue(key, &value);
    if (success) {
        *outValue = value;
        return true;
    }
    *outValue = 0;
    return false;
}