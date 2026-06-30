// FUNC_NAME: SetSessionGUID

void SetSessionGUID(const uint8_t (*guid)[16])
{
    if (guid == nullptr) {
        g_storedGuid1 = {};
        g_storedGuid2 = {};
    } else {
        g_storedGuid1 = (*guid);
        g_storedGuid2 = (guid[1]);
    }

    if ((g_currentContext == &g_contextStruct) && (g_contextStruct.field_0x14 == g_expectedValue)) {
        FUN_0060ab00(g_expectedValue, g_targetBuffer, &g_storedGuid1, 8);
    }
}