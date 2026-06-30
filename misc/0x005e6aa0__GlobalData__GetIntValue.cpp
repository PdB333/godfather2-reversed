// FUNC_NAME: GlobalData::GetIntValue
// 0x005e6aa0: Retrieves an integer value from a global data array at index 0.
// Uses a global pointer (DAT_01223514) to the data array and a success flag (unused).

extern int* LookupGlobalData(void* pArray, byte* outSuccess); // callee at 0x005f0600
extern void* g_pGlobalDataArray; // DAT_01223514

int GetIntValue()
{
    byte successFlag = 0;
    int* pValue = (int*)LookupGlobalData(g_pGlobalDataArray, &successFlag);
    if (pValue != nullptr)
    {
        return *pValue;
    }
    return 0;
}