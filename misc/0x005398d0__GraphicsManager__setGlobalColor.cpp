// FUNC_NAME: GraphicsManager::setGlobalColor
// Address: 0x005398d0
// Role: Copies a 4-component color (RGBA) into global state and optionally applies it to a render target based on current mode.

static uint32_t sGlobalColorR; // +0x0121b7f0
static uint32_t sGlobalColorG; // +0x0121b7f4
static uint32_t sGlobalColorB; // +0x0121b7f8
static uint32_t sGlobalColorA; // +0x0121b7fc
static void* gCurrentRenderState; // DAT_012058e8
static void* kDefaultRenderState = (void*)0x0121b740; // &DAT_0121b740
static uint32_t gRenderMode; // DAT_0121b754
static uint32_t gModeParam1; // DAT_0121bbb0
static uint32_t gModeParam2; // DAT_0121bbb8
static uint32_t gModeParamTarget1; // DAT_0121b994
static uint32_t gModeParamTarget2; // DAT_0121b9dc

void __fastcall setGlobalColor(uint32_t* color)
{
    sGlobalColorR = color[0];
    sGlobalColorG = color[1];
    sGlobalColorB = color[2];
    sGlobalColorA = color[3];

    if (gCurrentRenderState == kDefaultRenderState) {
        if (gRenderMode == gModeParam1) {
            FUN_0060add0(gModeParam1, gModeParamTarget1, &sGlobalColorR);
            return;
        }
        if (gRenderMode == gModeParam2) {
            FUN_0060add0(gModeParam1, gModeParamTarget2, &sGlobalColorR);
        }
    }
}