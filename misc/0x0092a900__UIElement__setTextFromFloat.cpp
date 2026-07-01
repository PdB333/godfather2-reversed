// FUNC_NAME: UIElement::setTextFromFloat
void __thiscall UIElement::setTextFromFloat(int thisPtr, float value, uint32_t flags)
{
    int* pGlobal = *(int**)(DAT_012233a0 + 4);
    if (pGlobal != nullptr && pGlobal != (int*)0x1f30)
    {
        int objId = *(int*)((int)pGlobal - 0x5c);
        int obj = FUN_008c74d0(objId);
        if (obj != 0)
        {
            float fVar1;
            if (value == 0.0f)
            {
                fVar1 = *(float*)(obj + 0x100); // +0x100: default value
            }
            else
            {
                float10 fVar4 = (float10)FUN_008c09a0(value * DAT_00d5ccf8, flags);
                fVar1 = (float)fVar4;
            }
            *(int*)(thisPtr + 0x60) = (int)fVar1; // +0x60: string hash/ID
        }
    }

    // Retrieve string from hash
    char* strBuffer = nullptr;
    int strLen = 0;
    int unused = 0;
    void (*freeFunc)(void*) = nullptr;
    FUN_00604000(*(int*)(thisPtr + 0x60), &strBuffer, 1); // 1 = allocate flag?

    char* finalStr = strBuffer;
    if (strBuffer == nullptr)
    {
        finalStr = &DAT_0120546e; // default empty string
    }

    // Copy string to member buffer (max 16 chars)
    FUN_005c4660(*(int*)(thisPtr + 0x114), finalStr, 0x10, strLen); // +0x114: string buffer

    if (strBuffer != nullptr)
    {
        freeFunc(strBuffer); // free allocated string
    }
}