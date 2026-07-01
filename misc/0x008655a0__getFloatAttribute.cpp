// FUNC_NAME: getFloatAttribute
float __cdecl getFloatAttribute(void* object, float key)
{
    float result;
    void* dummy;
    if (FUN_00865000(object, key, &result, &dummy) != 0) {
        return result;
    }
    return *(float*)0x00d5ccf8; // default float value
}