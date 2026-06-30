// FUNC_NAME: applyGameSpeedScale
// Address: 0x00529fd0
// Role: Multiplies global speed multipliers by a given scale factor

extern float g_speedScale0; // +0x0
extern float g_speedScale1; // +0x4
extern float g_speedScale2; // +0x8
extern float g_speedScale3; // +0xc

void applyGameSpeedScale(float scale)
{
    g_speedScale0 = scale * g_speedScale0;
    g_speedScale1 = scale * g_speedScale1;
    g_speedScale2 = scale * g_speedScale2;
    g_speedScale3 = scale * g_speedScale3;
}