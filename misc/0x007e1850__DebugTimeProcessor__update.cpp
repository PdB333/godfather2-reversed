// FUNC_NAME: DebugTimeProcessor::update
extern void* GetTimeData(); // FUN_00471610 - returns pointer to time structure
extern int MathOperation(void* a, void* b, int mode, void* param4, int param5, int param6); // FUN_00542650
extern int FormatAndPrint(char* buffer, void** formatTable); // FUN_009e5ed0

extern float g_TimeAdjustment; // DAT_00d5f52c (global float)
extern int g_SomeConstant; // DAT_01030000 (unknown, might be float or int)
extern int g_DefaultValue; // DAT_00d5780c (int)
extern void* g_FunctionTable; // PTR_FUN_00e32a8c (pointer to function table)

int __cdecl DebugTimeProcessor::update(void* pObj) {
    if (pObj == 0) {
        return 0;
    }

    // Get time data from global source
    void* timeData1 = GetTimeData(); // returns struct with double at +0x30 and float at +0x38
    void* timeData2 = GetTimeData(); // second call, possibly same data

    // Read double and float values
    unsigned long long timeValue1 = *(unsigned long long*)((char*)timeData1 + 0x30); // double at +0x30
    float timeFloat1 = *(float*)((char*)timeData1 + 0x38); // float at +0x38

    unsigned long long timeValue2 = *(unsigned long long*)((char*)timeData2 + 0x30); // second double
    float timeFloat2 = *(float*)((char*)timeData2 + 0x38); // second float

    // Manipulate high 32 bits of first value by adding global adjustment
    // low bits remain unchanged, high bits replaced with low+adjust (this looks like an attempt to modify a double's exponent or high word)
    unsigned int lowPart1 = (unsigned int)timeValue1; // low 32 bits
    unsigned int highPart1 = (unsigned int)(timeValue1 >> 32); // high 32 bits
    highPart1 = highPart1 + *((unsigned int*)&g_TimeAdjustment); // adding float as integer? Actually interpret g_TimeAdjustment as uint
    unsigned long long modifiedValue1 = ((unsigned long long)highPart1 << 32) | lowPart1;

    // For second value, extract high 32 bits as float, add global adjustment, then recombine
    float highPart2AsFloat = (float)(timeValue2 >> 32); // high bits interpreted as float? This cast is dangerous
    highPart2AsFloat += g_TimeAdjustment;
    unsigned int newHighPart2 = *(unsigned int*)&highPart2AsFloat; // convert float back to int bits
    unsigned int lowPart2 = (unsigned int)timeValue2;
    unsigned long long modifiedValue2 = ((unsigned long long)newHighPart2 << 32) | lowPart2;

    // Perform mathematical operation on these two 64-bit values
    MathOperation(&modifiedValue1, &modifiedValue2, 2, &g_SomeConstant, 0, 0);

    // Prepare arguments for debug print
    unsigned int local_ac = 0xFFFFFFFF;
    unsigned int local_a0 = 0xFFFFFFFF;
    void* formatTablePtr = &g_FunctionTable; // pointer to function pointer table
    int printResult = 0;
    int initialValue = g_DefaultValue;
    int initialValue2 = 0;
    int cc = g_DefaultValue;

    // Call formatting function with buffer and table
    char buffer[92]; // local_60
    int result = FormatAndPrint(buffer, &formatTablePtr); // expects pointer to pointer?
    if (result != 0) {
        return 1;
    }
    return 0;
}