// FUNC_NAME: createPromptControl
// Function address: 0x004ef520
// This function creates a UI prompt (button/dialog) with given dimensions and type.
// It sets up control states, allocates vertex data, and renders the prompt.

// Global variables (UI state)
extern float DAT_00e2af44;           // Some threshold? +0x0c comparison
extern float DAT_01205884;           // Screen offset X?
extern float DAT_01205888;           // Screen offset Y?
extern float DAT_01218e44;           // Scale factor X
extern float DAT_01218e48;           // Scale factor Y
extern float DAT_00e2b04c;           // Another scale?
extern float DAT_00e2b1a4;           // Center offset?
extern int g_screenWidth;            // DAT_012058d0
extern int g_screenHeight;           // DAT_00f15988
extern int g_uiButtonState;          // _DAT_011f3a30 (some flag?)
extern int g_uiAnotherFlag;          // _DAT_011f39f4
extern int g_uiSetting3;             // _DAT_011f3a3c
extern int g_uiSetting4;             // _DAT_011f3a38
extern int g_uiSetting5;             // _DAT_011f3a14
extern int g_uiSetting6;             // _DAT_011f3a44
extern float g_promptTextureA;       // DAT_012198f0 or DAT_012198f8
extern float g_promptTextureB;       // DAT_012198f4 or DAT_01219900
extern int g_promptMode;             // _DAT_01219a6c
extern void* g_promptBuffer;         // DAT_01219940? (pointer)

// Forward declarations of internal helper functions
void FUN_00417cf0(int a, int b, int c);  // e.g., setControlDefaults
void FUN_00417db0(int a, int b, int c, int d, int e); // setControlAdvanced
void FUN_0060a460(void* ptr);               // free memory
void FUN_00530df0();                        // begin texture setup?
void FUN_005311d0();                        // begin render?
void FUN_00530a60();                        // allocate buffer?
void* FUN_0060cd00(int size, int count, int align, int something, int unknown); // malloc
void FUN_0060cde0();                        // submit geometry
void FUN_00612e00();                        // flush render

void __thiscall createPromptControl(void* this, // seems unused
                                     float left,       // param_2
                                     float top,        // param_3
                                     float right,      // param_4
                                     float bottom,     // param_5
                                     int* pControlData, // param_6 (pointer with +0x0c)
                                     int buttonType,   // param_7 (enum: 0-7)
                                     bool isAction,    // param_8 (0 or non-zero)
                                     float extra1,     // param_9
                                     float extra2,     // param_10
                                     float extra3,     // param_11
                                     float extra4)     // param_12
{
    // Early exit if the control's activation condition fails
    if (*(float*)(pControlData + 0x0c) <= DAT_00e2af44 && DAT_00e2af44 != *(float*)(pControlData + 0x0c))
    {
        return;
    }

    // Calculate screen coordinates from normalized input
    float xLeft   = (((float)DAT_01205884 + left)   * DAT_01218e44 * DAT_00e2b04c) - DAT_00e2b1a4;
    float xRight  = (((float)DAT_01205884 + right)  * DAT_01218e44 * DAT_00e2b04c) - DAT_00e2b1a4;
    float yTop    = DAT_00e2b1a4 - (((float)DAT_01205888 + top)    * DAT_01218e48 * DAT_00e2b04c);
    float yBottom = DAT_00e2b1a4 - (((float)DAT_01205888 + bottom) * DAT_01218e48 * DAT_00e2b04c);

    // Clamp screen dimensions (min/max)
    if (g_screenWidth < 0x16) g_screenWidth = 0x16;
    if (0x16 < g_screenHeight) g_screenHeight = 0x16;
    g_uiButtonState = 1;

    if (g_screenWidth < 7) g_screenWidth = 7;
    if (7 < g_screenHeight) g_screenHeight = 7;
    g_uiAnotherFlag = 0;

    if (g_screenWidth < 0x19) g_screenWidth = 0x19;
    if (0x19 < g_screenHeight) g_screenHeight = 0x19;
    g_uiSetting3 = 5;

    if (g_screenWidth < 0x18) g_screenWidth = 0x18;
    if (0x18 < g_screenHeight) g_screenHeight = 0x18;
    g_uiSetting4 = 1;

    if (g_screenWidth < 0xf) g_screenWidth = 0xf;
    if (0xf < g_screenHeight) g_screenHeight = 0xf;
    g_uiSetting5 = 1;

    if (g_screenWidth < 0x1b) g_screenWidth = 0x1b;
    if (0x1a < g_screenHeight) g_screenHeight = 0x1b;
    g_uiSetting6 = 1;

    // Set up button type (switch on param_7)
    int controlArg1, controlArg2, controlArg3;
    switch (buttonType)
    {
    case 0:
        controlArg1 = 2;
        controlArg2 = 5;
        // controlArg3 not set?
        break;
    case 1:
        controlArg1 = 6;
        controlArg2 = 5;
        break;
    case 2:
        controlArg1 = 2;
        controlArg2 = 5;
        controlArg3 = 3;
        goto applyControl;
    default:
        controlArg1 = 1;
        controlArg2 = 2;
        break;
    case 4:
        controlArg1 = 1;
        controlArg2 = 9;
        break;
    case 5:
        controlArg1 = 2;
        controlArg2 = 9;
        break;
    case 6:
        FUN_00417db0(9, 1, 1, 1, 2);
        goto skipStandard;
    case 7:
        FUN_00417db0(9, 1, 1, 2, 1);
        goto skipStandard;
    }
    controlArg3 = 1; // default if not set

applyControl:
    FUN_00417cf0(controlArg3, controlArg2, controlArg1);

skipStandard:
    // Branch based on isAction (param_8)
    if (isAction == 0)
    {
        g_promptTextureA = DAT_012198f0; // some global texture
        g_promptTextureB = DAT_012198f4;
        g_promptMode = 0;

        // Free old textures if they match
        if (g_promptBuffer == &DAT_01219940)
        {
            FUN_0060a460(DAT_012198f0);
            FUN_0060a460(g_promptTextureB);
        }

        FUN_005311d0();
        FUN_00530a60();

        // Allocate vertex buffer (5*4 floats = 20 floats = 80 bytes? But they write 8 floats)
        float* vertices = (float*)FUN_0060cd00(5, 4, 0, 1, 0);
        if (vertices == nullptr) goto cleanup;

        // Set up a 4-vertex quad (standard button shape)
        vertices[0] = xLeft;   // x1
        vertices[4] = xLeft;   // x1 (duplicate? Actually array of 5*4=20 floats, indexing is weird)
        vertices[1] = yTop;    // y1
        vertices[2] = xRight;  // x2
        vertices[3] = yTop;    // y2
        vertices[5] = yBottom; // y3
        vertices[6] = xRight;  // x4
        vertices[7] = yBottom; // y4
        // Note: indices are offset by 0,4,1 etc., likely because of vertex format (position, texcoord?)
        // This may be a 4-vertex strip with 8 coordinates (2D positions)
    }
    else
    {
        g_promptTextureA = DAT_012198f8;
        g_promptTextureB = DAT_01219900;
        g_promptMode = 3;

        if (g_promptBuffer == &DAT_01219940)
        {
            FUN_0060a460(DAT_012198f8);
            FUN_0060a460(g_promptTextureB);
        }

        FUN_00530df0();
        FUN_005311d0();
        FUN_00530a60();

        float* vertices = (float*)FUN_0060cd00(5, 4, 0, 1, 0);
        if (vertices == nullptr) goto cleanup;

        // For action prompt, use more complex vertex data (likely rounded corners or additional points)
        vertices[1]  = yTop;
        vertices[2]  = extra1;
        vertices[3]  = extra2;
        vertices[5]  = yTop;
        vertices[7]  = extra2;
        vertices[10] = extra1;
        vertices[0]  = xLeft;
        vertices[4]  = xRight;
        vertices[6]  = extra3;
        vertices[8]  = xLeft;
        vertices[9]  = yBottom;
        vertices[0xB]= extra4;
        vertices[0xC]= xRight;
        vertices[0xD]= yBottom;
        vertices[0xE]= extra3;
        vertices[0xF]= extra4;
        // This appears to be a 6-point shape (16 floats? Actually 0x10 = 16 floats)
    }

    FUN_0060cde0(); // submit geometry

cleanup:
    FUN_00612e00();

    // Reset some UI state variables
    g_uiAnotherFlag = 0;
    g_uiButtonState = 0;
    g_promptTextureA = 0;
    g_promptTextureB = 0;

    // Clamp again (probably for next render)
    if (g_screenWidth < 0x16) g_screenWidth = 0x16;
    if (0x16 < g_screenHeight) g_screenHeight = 0x16;
    g_uiButtonState = 1;

    if (g_screenWidth < 7) g_screenWidth = 7;
    if (7 < g_screenHeight) g_screenHeight = 7;
    g_uiAnotherFlag = 1;

    if (g_screenWidth < 0x19) g_screenWidth = 0x19;
    if (0x19 < g_screenHeight) g_screenHeight = 0x19;
    g_uiSetting3 = 7;

    if (g_screenWidth < 0x18) g_screenWidth = 0x18;
    if (0x18 < g_screenHeight) g_screenHeight = 0x18;
    g_uiSetting4 = 0;

    if (g_screenWidth < 0xf) g_screenWidth = 0xf;
    if (0xf < g_screenHeight) g_screenHeight = 0xf;
    g_uiSetting5 = 0;

    if (g_screenWidth < 0x1b) g_screenWidth = 0x1b;
    if (0x1a < g_screenHeight) g_screenHeight = 0x1b;
    g_uiSetting6 = 0;

    FUN_00417cf0(1, 5, 6);
}