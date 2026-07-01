// FUNC_NAME: IsTimestampValid
// Function address: 0x0077b2f0
// Role: Checks if a given timestamp is within a valid time window defined by global time variables.
extern float g_fMinTimestamp;   // 0xd577a0
extern float g_fCurrentTimestamp; // 0x1205228
extern float g_fTimestampWindow;  // 0xd68540

int IsTimestampValid(const float* pTimestamp)
{
    if ((g_fMinTimestamp <= *pTimestamp) && (g_fCurrentTimestamp - *pTimestamp <= g_fTimestampWindow))
    {
        return 0; // valid
    }
    return 1; // invalid
}