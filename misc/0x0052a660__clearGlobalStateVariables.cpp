// FUNC_NAME: clearGlobalStateVariables

extern float g_globalFloat0;   // +0x00 (0x01125230)
extern float g_globalFloat1;   // +0x04 (0x01125234)
extern float g_globalFloat2;   // +0x08 (0x01125238)
extern float g_globalFloat3;   // +0x0c (0x0112523c)
extern int   g_globalInt;      // +0x10 (0x01125240)

void clearGlobalStateVariables(void)
{
    g_globalFloat0 = 0.0f;
    g_globalFloat1 = 0.0f;
    g_globalFloat2 = 0.0f;
    g_globalFloat3 = 0.0f;
    g_globalInt = 0;
}