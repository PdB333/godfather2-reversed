// FUNC_NAME: InputManager::updateControllerConfig

#include <cstdint>

// Global state variables (likely part of a larger input manager state)
static int32_t g_controllerId = 0;           // DAT_011f38f0
static int32_t g_lastControllerId = 0;        // DAT_011f38f4
static uint8_t g_controllerCount = 0;          // DAT_012058a4 (probably)
static int32_t g_minVibration = 0;             // DAT_012058d0
static int32_t g_maxVibration = 0;             // DAT_00f15988
static int32_t g_rumbleLeftMotor = 0;          // _DAT_011f3a30 (bitfield?)
static int32_t g_rumbleRightMotor = 0;         // _DAT_011f3a10
static int32_t g_rumbleWeapon = 0;             // _DAT_011f39f4
static int32_t g_rumbleExplosion = 0;          // _DAT_011f3a3c
static int32_t g_rumbleDamage = 0;             // _DAT_011f3a38
static int32_t g_rumbleFootstep = 0;           // _DAT_011f3a14
static int32_t g_rumbleMenu = 0;               // _DAT_011f3a44
static int32_t g_controllerCount2 = 0;         // _DAT_01205500 (increment/decrement)
static uint32_t g_controllerArray[20][2];      // DAT_01218e50 (array of 20 pairs)
// Offsets: base + 0x00 = first int, base + 0x04 = second int
static uint32_t g_controllerResult[2];         // DAT_01218eb8 (two elements)
static void* g_deviceList[0x1000];             // Base DAT_011a0f28, each entry 0x38 bytes
// Offsets in devEntry: +0x00 byte, +0x0C uint32 flags, +0x1C pointer

// Forward declarations of called functions
extern void releaseDevice(uint32_t* ptr, uint32_t flags);  // FUN_00606e60
extern void syncDeviceState();                           // FUN_006189c0
extern void runSpecialUpdate(int a, int b, int c);       // FUN_00417cf0
extern void processControllerData(int32_t unk, int param2); // FUN_0052be20
extern void finalizeControllerUpdate();                  // FUN_00606470
extern void notifyControllerChange(uint32_t oldId, uint32_t oldLastId); // FUN_00609340
extern void applyDefaultRumbleSettings(int, int, int, float, float); // FUN_0060db60

uint32_t InputManager::updateControllerConfig(uint32_t deviceIndex, int32_t param1, int32_t param2)
{
    int32_t bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    int32_t iVar4;

    bVar1 = g_controllerId;
    iVar4 = g_controllerCount;
    if (g_controllerCount2 != 0) {
        iVar4 = *(int32_t*)((int32_t)g_controllerCount2 + 0x16c);  // maybe pointer to active controller struct
    }
    if (g_controllerId == iVar4) {
        g_controllerCount2 = g_controllerCount2 + 1;
    }

    // Clamp g_minVibration to 0x16 (22) if below
    if (g_minVibration < 0x16) {
        g_minVibration = 0x16;
    }
    if (0x16 < g_maxVibration) {
        g_maxVibration = 0x16;
    }
    g_rumbleLeftMotor = 1;

    if (g_minVibration < 0xe) {
        g_minVibration = 0xe;
    }
    if (0xe < g_maxVibration) {
        g_maxVibration = 0xe;
    }
    g_rumbleRightMotor = 0;

    if (g_minVibration < 7) {
        g_minVibration = 7;
    }
    if (7 < g_maxVibration) {
        g_maxVibration = 7;
    }
    g_rumbleWeapon = 0;

    if (g_minVibration < 0x19) {
        g_minVibration = 0x19;
    }
    if (0x19 < g_maxVibration) {
        g_maxVibration = 0x19;
    }
    g_rumbleExplosion = 5;

    if (g_minVibration < 0x18) {
        g_minVibration = 0x18;
    }
    if (0x18 < g_maxVibration) {
        g_maxVibration = 0x18;
    }
    g_rumbleDamage = 0;

    if (g_minVibration < 0xf) {
        g_minVibration = 0xf;
    }
    if (0xf < g_maxVibration) {
        g_maxVibration = 0xf;
    }
    g_rumbleFootstep = 0;

    // Device index check: if valid and corresponds to a connected device
    if ((deviceIndex != 0xFFFFFFFF) && (deviceIndex < 0x1000)) {
        int32_t devOffset = deviceIndex * 0x38;
        uint8_t* devEntry = (uint8_t*)(&g_deviceList) + devOffset;  // Actually g_deviceList is base, but reinterpret
        // Actually g_deviceList is an array of structures, each 0x38 bytes.
        // At offset 0x00: byte state ( <4 means active?)
        if ((devEntry[0] < 4) && (*(uint32_t*)(devEntry + 0x1C) != 0)) {
            // Release device with flag 0x100000
            releaseDevice(*(uint32_t**)(devEntry + 0x1C), 0x100000);
        }
        // Modify flags at offset 0x0C
        *(uint32_t*)(devEntry + 0x0C) = (*(uint32_t*)(devEntry + 0x0C) & 0xFC9C8FFF) | 0x100000;
        syncDeviceState();
    }

    runSpecialUpdate(1, 2, 1);

    if (g_minVibration < 0x1b) {
        g_minVibration = 0x1b;
    }
    if (0x1a < g_maxVibration) {
        g_maxVibration = 0x1b;
    }
    g_rumbleMenu = 0;

    processControllerData(param1, 0, param2);
    finalizeControllerUpdate();

    // Second set of rumble clamping (different pattern)
    if (g_minVibration < 0x16) {
        g_minVibration = 0x16;
    }
    if (0x16 < g_maxVibration) {
        g_maxVibration = 0x16;
    }
    g_rumbleLeftMotor = 1;

    if (g_minVibration < 7) {
        g_minVibration = 7;
    }
    if (7 < g_maxVibration) {
        g_maxVibration = 7;
    }
    g_rumbleWeapon = 1;

    if (g_minVibration < 0x19) {
        g_minVibration = 0x19;
    }
    if (0x19 < g_maxVibration) {
        g_maxVibration = 0x19;
    }
    g_rumbleExplosion = 7;

    if (g_minVibration < 0x18) {
        g_minVibration = 0x18;
    }
    if (0x18 < g_maxVibration) {
        g_maxVibration = 0x18;
    }
    g_rumbleDamage = 0;

    if (g_minVibration < 0xf) {
        g_minVibration = 0xf;
    }
    if (0xf < g_maxVibration) {
        g_maxVibration = 0xf;
    }
    g_rumbleFootstep = 0;

    runSpecialUpdate(1, 5, 6);

    if (g_minVibration < 0x1b) {
        g_minVibration = 0x1b;
    }
    if (0x1a < g_maxVibration) {
        g_maxVibration = 0x1b;
    }
    g_rumbleMenu = 0;

    if (g_minVibration < 0xe) {
        g_minVibration = 0xe;
    }
    if (0xe < g_maxVibration) {
        g_maxVibration = 0xe;
    }
    g_rumbleRightMotor = 1;

    // Search controller array for matching ID and clear low 2 bits of second element
    uVar3 = 0;
    do {
        if (g_controllerArray[uVar3][0] == bVar1) {
            if (uVar3 < 0x14) {
                g_controllerArray[uVar3][1] = g_controllerArray[uVar3][1] & 0xFFFFFFFC;
            }
            break;
        }
        uVar3 = uVar3 + 1;
    } while (uVar3 < 0x14);

    uVar2 = g_lastControllerId;
    iVar4 = g_controllerId;
    g_lastControllerId = 0;
    g_controllerId = bVar1;

    notifyControllerChange(0, iVar4, uVar2);
    applyDefaultRumbleSettings(0, 0, 0, 1.0f, 1.0f);  // 0x3f800000 = 1.0f

    iVar4 = g_controllerCount;
    if (g_controllerCount2 != 0) {
        iVar4 = *(uint32_t*)((int32_t)g_controllerCount2 + 0x16c);
    }
    if (bVar1 == iVar4) {
        g_controllerCount2 = g_controllerCount2 - 1;
    }

    // Return value selected based on param2 (non-zero vs zero)
    // The expression: (&g_controllerResult)[(-(uint)((char)param2 != '\0') & 0xfffffffd) * 2]
    // In C this is: if (param2 != 0) return g_controllerResult[1]; else return g_controllerResult[0];
    if (param2 != 0) {
        return g_controllerResult[1];
    } else {
        return g_controllerResult[0];
    }
}