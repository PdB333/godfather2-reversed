// Xbox PDB: EARS_Vehicles_CarAudioLuaGlue_Open
// FUNC_NAME: ChaseVehicleSoundManager::setChaseVehicleSound
// Address: 0x0087fdc0
// This function handles a Lua binding that sets a chase vehicle sound.
// It reads a vehicle index (0-3) and an optional sound parameter from Lua,
// stops the existing sound for that slot, creates a new sound source and sound,
// and plays it.

#include <cmath> // for roundf

// Forward declarations of internal engine functions (actual addresses in comments)
namespace LuaUtils {
    bool hasLuaFunction(void* luaState, int argIdx, const char* funcName);         // FUN_004aed30
    void* getLuaUserData(void* luaState, int argIdx);                              // FUN_00625a70
    bool argIsNumber(void* luaState, int argIdx);                                  // FUN_006257d0
    float getNumber(void* luaState, int argIdx);                                   // FUN_006259b0
}

namespace SoundManager {
    void resetChaseSounds();                                                       // FUN_005e3070
    void clearChaseSoundQueue();                                                   // FUN_005e30a0
    void stopSound(int soundHandle);                                               // FUN_005e6660
    int createSoundSource(void* userData);                                         // FUN_004dafd0
    int createSound(int source, int* params);                                      // FUN_005e6550
    void playSound(int soundHandle, int volume);                                   // FUN_005e6750 (volume=0 might be default)
}

// Global array of chase vehicle sound slots (4 entries, each 12 bytes)
// Address: 0x0112e168
struct ChaseVehicleSoundSlot {
    int soundHandle;       // +0x00
    int source;            // +0x04
    int soundParameter;    // +0x08
};
static ChaseVehicleSoundSlot g_chaseVehicleSounds[4];

int __thiscall ChaseVehicleSoundManager::setChaseVehicleSound(void* thisPtr)
{
    // Check if the Lua function "SetChaseVehicleSound" is callable
    if (!LuaUtils::hasLuaFunction(thisPtr, 1, "SetChaseVehicleSound"))
        return 0;

    // Get the Lua userdata (presumably the game object with the chase sound)
    void* luaObject = LuaUtils::getLuaUserData(thisPtr, 1);

    // Reset chase sound system state (stop all, clear queues)
    SoundManager::resetChaseSounds();
    SoundManager::clearChaseSoundQueue();

    // Retrieve vehicle index from Lua argument 2 (optional, defaults to 0)
    int vehicleIndex = 0;
    if (LuaUtils::argIsNumber(thisPtr, 2)) {
        float rawIndex = LuaUtils::getNumber(thisPtr, 2);
        int roundedIndex = static_cast<int>(roundf(rawIndex));
        if (roundedIndex >= 0 && roundedIndex < 4)
            vehicleIndex = roundedIndex;
    }

    // Retrieve optional sound parameter from Lua argument 3
    int soundParamBuffer[8] = {0}; // only the first element is used
    if (LuaUtils::argIsNumber(thisPtr, 3)) {
        float rawParam = LuaUtils::getNumber(thisPtr, 3);
        soundParamBuffer[0] = static_cast<int>(roundf(rawParam));
    }

    // Stop any existing sound for this vehicle slot
    if (g_chaseVehicleSounds[vehicleIndex].soundHandle != 0) {
        SoundManager::stopSound(g_chaseVehicleSounds[vehicleIndex].soundHandle);
    }

    // Create a new sound source from the Lua object
    int newSource = SoundManager::createSoundSource(luaObject);
    g_chaseVehicleSounds[vehicleIndex].source = newSource;

    // Create a new sound only if the source is valid AND the existing slot's
    // soundParameter is non‑zero (original logic preserved)
    int newHandle = 0;
    if (newSource != 0 && g_chaseVehicleSounds[vehicleIndex].soundParameter != 0) {
        newHandle = SoundManager::createSound(newSource, soundParamBuffer);
    }
    g_chaseVehicleSounds[vehicleIndex].soundHandle = newHandle;

    // Play the sound if creation succeeded
    if (newHandle != 0) {
        SoundManager::playSound(newHandle, 0);
    }

    return 0;
}