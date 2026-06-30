// FUNC_NAME: PostProcessManager::initResources

// Global state for post-processing resources
static int g_someFlag1;          // DAT_01206a78
static int g_someFlag2;          // DAT_01206a7c
static int g_someFlag3;          // DAT_01206aec
static int g_currentIndex;       // DAT_01206b04
static void* g_currentResource;  // DAT_01205958
static void* g_bigTexture[4];    // DAT_01206af0..fc
static void* g_mediumTexture;    // DAT_01206b00
static void* g_smallTexture[3];  // DAT_01206b08, b0c, b10
static void* g_tinyTexture;      // DAT_01206b14
static bool g_resourcesCreated;  // DAT_01206a80
static float g_globalWhiteBuffer[128]; // DAT_011627d0

// External helper functions (from elsewhere in the engine)
extern void postProcessSubInit();                    // FUN_0041cb80
extern void* createTexture(int type, int format, int width, int height, int depth, int usage); // FUN_00606c80
extern void resetRenderState();                      // FUN_0041cd80
extern void lockSurface(void* texture, int a, int b, void* buffer);   // FUN_00606fd0
extern void unlockSurface(void* buffer);             // FUN_006071a0
extern void setTextureColor(void* texture, int color); // FUN_006154e0

void PostProcessManager::initResources(int createResources)
{
    // Reset global flags
    g_someFlag1 = 0;
    g_someFlag2 = 0;
    g_someFlag3 = 0;
    g_currentIndex = 0;

    if (createResources == 0)
    {
        // If not creating, just null out pointers
        g_bigTexture[0] = 0;
        g_bigTexture[1] = 0;
        g_bigTexture[2] = 0;
        g_bigTexture[3] = 0;
        g_smallTexture[0] = 0;
        g_smallTexture[1] = 0;
        g_smallTexture[2] = 0;
    }
    else
    {
        // Initialize sub‑system
        postProcessSubInit();

        // Create 64x64 textures (format 0x210098, type 3)
        g_bigTexture[0] = createTexture(3, 0x210098, 0x40, 0x40, 1, 0xFFFFFFFF);
        g_bigTexture[1] = createTexture(3, 0x210098, 0x40, 0x40, 1, 0xFFFFFFFF);
        g_bigTexture[2] = createTexture(3, 0x210098, 0x40, 0x40, 1, 0xFFFFFFFF);
        g_bigTexture[3] = createTexture(3, 0x210098, 0x40, 0x40, 1, 0xFFFFFFFF);

        // Create 64x64 texture (format 0x210280, type 3)
        g_mediumTexture = createTexture(3, 0x210280, 0x40, 0x40, 1, 0xFFFFFFFF);

        // Create 128x1 textures (format 0x210080, type 0x15 – 21)
        g_smallTexture[0] = createTexture(0x15, 0x210080, 0x80, 1, 1, 0xFFFFFFFF);
        g_smallTexture[1] = createTexture(0x15, 0x210080, 0x80, 1, 1, 0xFFFFFFFF);
        g_smallTexture[2] = createTexture(0x15, 0x210080, 0x80, 1, 1, 0xFFFFFFFF);

        // Create 1x1 texture (type 8, format 0x210080)
        g_tinyTexture = createTexture(8, 0x210080, 1, 1, 1, 0xFFFFFFFF);

        // Initialize render states
        for (int i = 0; i < 4; i++)
            resetRenderState();

        // Fill the three 128x1 textures with 1.0f (white in float format)
        for (int i = 0; i < 3; i++)
        {
            // Use a stack buffer large enough for 128 floats (512 bytes)
            float buffer[128];

            // Lock the texture and obtain buffer pointer
            lockSurface(g_smallTexture[i], 2, 0, buffer);

            // Fill with 1.0f (0x3f800000)
            for (int j = 0; j < 128; j++)
                buffer[j] = 1.0f;

            // Unlock
            unlockSurface(buffer);
        }

        // Set the 1x1 texture to color 0xFF (opaque white or similar)
        setTextureColor(g_tinyTexture, 0xFF);

        // Cycle to next small texture for double‑buffering
        g_currentResource = g_smallTexture[g_currentIndex];
        g_currentIndex = (g_currentIndex + 1) % 3;
    }

    // Initialize a global white buffer (128 floats) to 1.0f
    for (int i = 0; i < 128; i++)
        g_globalWhiteBuffer[i] = 1.0f;

    // Mark whether resources were created
    g_resourcesCreated = (createResources != 0);
}