// FUNC_NAME: GameState::initialize
#include <cstdint>

// Global data pointers (not defined here, only used)
extern uint8_t* g_pGameContext;              // DAT_012054dc
extern uint32_t s_defaultLevelIndex;         // DAT_012058a4
extern uint8_t s_bInitialized;              // DAT_012054d8
extern void* s_cameraFieldOfView;           // DAT_01206750
extern void* s_cameraNearPlane;             // DAT_01206754
extern void* s_cameraFarPlane;               // DAT_0120675c

struct LevelData {
    uint16_t unknown0;       // +0x00
    uint16_t screenWidth;    // +0x02
    uint16_t screenHeight;   // +0x04
    // remaining 50 bytes omitted
};
extern LevelData s_levelDataTable[];         // DAT_011a0f28, each 0x38 bytes

struct CallbackEntry {
    uint32_t dataLow;    // +0x00 low 4 bytes (includes type as LSB)
    uint32_t dataHigh;   // +0x04 high 4 bytes
    uint32_t flags;      // +0x08
};
extern CallbackEntry s_callbackTable[];      // DAT_01222328 (base for array)
extern uint32_t s_callbackCount;             // DAT_012224a8

// Subsystem initializers
void setScreenResolution(uint16_t width, uint16_t height);
void initGraphics();
void initAudio();
void initInput();
void initPhysics();
void initScripting();
void initNetwork();
void initEntityManager();
void initUI();
void initAnimation();
void initEffects();
void initSound();
void initMission();
void onFatalError();

void GameState::initialize()
{
    s_bInitialized = 0;

    uint32_t levelIndex = s_defaultLevelIndex;
    if (g_pGameContext != nullptr)
    {
        levelIndex = *(uint32_t*)(g_pGameContext + 0x16C); // +0x16C: currentLevelId
    }

    LevelData* pLevelData = nullptr;
    if (levelIndex < 0x1000)
    {
        pLevelData = &s_levelDataTable[levelIndex];
    }

    setScreenResolution(pLevelData->screenWidth, pLevelData->screenHeight);

    initGraphics();
    initAudio();
    initInput();

    // Set default camera values
    s_cameraFieldOfView = (void*)0x00e446c0;
    // ... additional camera setup omitted

    // Initialize all remaining subsystems
    initPhysics();
    initScripting();
    initNetwork();
    initEntityManager();
    initUI();
    initAnimation();
    initEffects();
    initSound();
    initMission();

    // Validate callback table entries (each 0xC bytes)
    for (uint32_t i = 0; i < s_callbackCount; i++)
    {
        // First byte of each entry is the type field
        uint8_t entryType = s_callbackTable[i].dataLow & 0xFF;
        if (entryType > 0x80)
        {
            onFatalError();
            return;
        }
    }

    // Add a new default callback if space remains
    if (s_callbackCount < 32)
    {
        uint32_t index = s_callbackCount;
        // Set two DWORDs at offset 0 and 4, and then flags at offset 8
        *(uint64_t*)&s_callbackTable[index] = 0x4e3bc0004e3ba0ULL; // default callback functions
        s_callbackTable[index].flags = 0x80; // type/flag byte
        s_callbackCount++;
    }
}