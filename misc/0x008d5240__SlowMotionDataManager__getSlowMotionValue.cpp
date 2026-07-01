// FUNC_NAME: SlowMotionDataManager::getSlowMotionValue
// Address: 0x008d5240
// Dispatcher that retrieves a slow-motion related value based on type ID (param_1) and context parameter (param_2).
// This is part of a slow-motion or time-manipulation system, common in action games like The Godfather 2.
// The constant 0x637b907 likely identifies a specific slow-motion configuration/asset.

#define SLOW_MOTION_HASH 0x637b907

typedef struct SlowMotionConfig {
    // +0x00 unknown
    // +0x18 first float?
    // +0x28 second float?
    // +0x30 third float?
    // +0x40 fourth float?
    // +0x48 fifth float?
    // +0x58 sixth float?
    // +0x60 seventh float?
    // +0x70 eighth float?
    // +0x7c ninth float?
    // +0x84 tenth float?
    float values[10]; // approximate, offsets are not contiguous
} SlowMotionConfig;

// External global pointer to the slow motion config table (located at 0x011299a8)
extern SlowMotionConfig* gSlowMotionConfig;

// Forward declarations of helper functions (likely in the same module)
int applyConversion(int value); // FUN_008d42b0
int processWithArg(int base, int arg); // FUN_008d4300
int getGlobalField(SlowMotionConfig* config, int index); // FUN_008d4350
int getBaseValue(int type); // FUN_008d6ac0
int getBaseValue2(int type); // FUN_008d6ad0
int getBaseValue3(int type); // FUN_008d6ae0
int getBaseValue4(int type); // FUN_008d6af0
int getFromHash1(int hash); // FUN_008d37a0
int getFromHash2(int hash); // FUN_008d37f0
int getFromHash3(int hash); // FUN_008d7bb0
int getFromHash4(int hash); // FUN_008d7c00
int getSubValue1(int index); // FUN_008d2d00
int getSubValue2(int index); // FUN_008d2d10
int getSubValue3(int index); // FUN_008d2d20
int getSubValue4(int index); // FUN_008d2d30

int __cdecl getSlowMotionValue(int typeId, int contextParam) {
    int result = 0;

    switch (typeId) {
    case 0:
        result = getBaseValue(contextParam);
        result = applyConversion(result);
        return result;

    case 4:
        result = getBaseValue3(contextParam);
        result = applyConversion(result);
        return result;

    case 9:
        result = getFromHash1(SLOW_MOTION_HASH);
        result = processWithArg(result, contextParam);
        return result;

    case 0x0e: // 14
        result = getSubValue1(0);
        result = processWithArg(result, contextParam);
        return result;

    case 0x0f: // 15
        result = getSubValue1(2);
        result = processWithArg(result, contextParam);
        return result;

    case 0x10: // 16
        result = getSubValue1(1);
        result = processWithArg(result, contextParam);
        return result;

    case 0x11: // 17
        result = getSubValue1(3);
        result = processWithArg(result, contextParam);
        return result;

    case 0x14: // 20
        result = getSubValue3(contextParam);
        result = processWithArg(result);
        return result;

    case 0x16: // 22
        result = getFromHash2(SLOW_MOTION_HASH);
        result = processWithArg(result, contextParam);
        return result;

    case 0x1b: // 27
        result = getSubValue2(0);
        result = processWithArg(result, contextParam);
        return result;

    case 0x1c: // 28
        result = getSubValue2(2);
        result = processWithArg(result, contextParam);
        return result;

    case 0x1d: // 29
        result = getSubValue2(1);
        result = processWithArg(result, contextParam);
        return result;

    case 0x1e: // 30
        result = getSubValue2(3);
        result = processWithArg(result, contextParam);
        return result;

    case 0x21: // 33
        result = getSubValue4(contextParam);
        result = processWithArg(result);
        return result;

    case 0x22: // 34
        result = getGlobalField(gSlowMotionConfig + 0x18, contextParam); // first float field
        return result;

    case 0x23: // 35
        result = getGlobalField(gSlowMotionConfig + 0x30, contextParam);
        return result;

    case 0x24: // 36
        result = getGlobalField(gSlowMotionConfig + 0x48, contextParam);
        return result;

    case 0x25: // 37
        result = getGlobalField(gSlowMotionConfig + 0x60, contextParam);
        return result;

    case 0x26: // 38
        result = getGlobalField(gSlowMotionConfig + 0x7c, contextParam);
        return result;

    case 0x27: // 39
        result = getGlobalField(gSlowMotionConfig + 0x28, contextParam);
        return result;

    case 0x28: // 40
        result = getGlobalField(gSlowMotionConfig + 0x40, contextParam);
        return result;

    case 0x29: // 41
        result = getGlobalField(gSlowMotionConfig + 0x58, contextParam);
        return result;

    case 0x2a: // 42
        result = getGlobalField(gSlowMotionConfig + 0x70, contextParam);
        return result;

    case 0x2b: // 43
        result = getGlobalField(gSlowMotionConfig + 0x84, contextParam);
        // No extra processing, fall through to return result (break missing? but it's at end of switch before default)
        break;

    case 0x2d: // 45
        result = getFromHash3(SLOW_MOTION_HASH);
        result = applyConversion(result, contextParam);
        return result;

    case 0x32: // 50
        result = getBaseValue2(0);
        result = applyConversion(result, contextParam);
        return result;

    case 0x33: // 51
        result = getBaseValue2(2);
        result = applyConversion(result, contextParam);
        return result;

    case 0x34: // 52
        result = getBaseValue2(1);
        result = applyConversion(result, contextParam);
        return result;

    case 0x35: // 53
        result = getBaseValue2(3);
        result = applyConversion(result, contextParam);
        return result;

    case 0x39: // 57
        result = getFromHash4(SLOW_MOTION_HASH);
        result = applyConversion(result, contextParam);
        return result;

    case 0x3e: // 62
        result = getBaseValue4(0);
        result = applyConversion(result, contextParam);
        return result;

    case 0x3f: // 63
        result = getBaseValue4(2);
        result = applyConversion(result, contextParam);
        return result;

    case 0x40: // 64
        result = getBaseValue4(1);
        result = applyConversion(result, contextParam);
        return result;

    case 0x41: // 65
        result = getBaseValue4(3);
        result = applyConversion(result, contextParam);
        return result;

    // default: return 0 (implied)
    }

    return result;
}