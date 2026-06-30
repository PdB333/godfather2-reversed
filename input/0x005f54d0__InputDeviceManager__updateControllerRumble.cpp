// FUNC_NAME: InputDeviceManager::updateControllerRumble

#include <cstdint>

// Forward declarations for unknown callees (likely vibration/audio system)
void lockMutex(uint32_t* pMutex);
void unlockMutex(uint32_t* pMutex);

// Global function prototypes (likely from EARS::Sound::VibrationManager)
int FUN_005e9d10();                           // Check if vibration is enabled
void FUN_00ab4db0(void* param);               // Acquire some lock
void FUN_00ac2810();                          // Begin vibration update block
void FUN_00c9eac0();                          // Begin rumble channel access
void FUN_00c9cd00(int channel, float* outValue); // Get current rumble strength
void FUN_00c9cbe0(uint32_t obj1, uint32_t obj2, int mode, float* param); // Set vibration parameters
void FUN_00c9cd40(int mode, float* param);    // Apply/commit rumble
void FUN_00c9eae0();                          // End rumble channel access
void FUN_005ea0d0();                          // Remove/cleanup vibration source
void FUN_00ab4e70();                          // Release lock

extern float DAT_00e2b05c;                    // Sentinel value for vibration completion
extern void* DAT_00e2aea0;                    // Global mutex?

// ----------------------------------------------------------------------
// InputDeviceManager
// Processes rumble/force-feedback effects for a given controller slot.
// param_1: this pointer
// param_2: controller index (0-15, float cast to int)
// returns: 1 if any effect was processed, 0 otherwise
// ----------------------------------------------------------------------
uint8_t __thiscall InputDeviceManager::updateControllerRumble(int thisPtr, float controllerIndexFloat)
{
    int controllerIndex = (int)controllerIndexFloat;
    uint8_t result = 0;

    // Check if controller slot is valid and vibration system is active
    if (*(int*)(thisPtr + 0x580) != 0 && controllerIndex >= 0)
    {
        // Check if reference count for this controller (array at 0x81C4, stride 16) is nonzero
        int* refCountArray = (int*)(thisPtr + 0x81C4);
        int* controllerRefCount = &refCountArray[controllerIndex * 4]; // each entry is 16 bytes (4 ints)
        if (*controllerRefCount != 0)
        {
            int useVibration = FUN_005e9d10(); // returns 1 if vibration is globally enabled

            // Arrays of 10 vibration effects, each 0x5c bytes, starting at 0x8344
            // The pointer is manipulated as float* in the decompiler, but we treat it as char*
            // Actual interpretation: each element is a RumbleEffect struct of size 92 bytes
            char* effectPtr = (char*)(thisPtr + 0x8344);
            int effectCount = 10;
            do
            {
                // The struct members are accessed via negative offsets from effectPtr,
                // which in the original code actually points to the END of the current effect.
                // We offset the indices accordingly.

                // int sourceIndex = *(int*)(effectPtr - 0x98);   // pfVar5[-0x26]
                int sourceIndex = *(int*)(effectPtr - 0x98);
                // int activationFlag = *(int*)(effectPtr - 0x94); // pfVar5[-0x25] (>=0 means active)
                int activationFlag = *(int*)(effectPtr - 0x94);
                // uint32_t flags = *(uint32_t*)(effectPtr - 4);   // pfVar5[-1] bitfield
                uint32_t flags = *(uint32_t*)(effectPtr - 4);
                // float storedFlag = *(float*)(effectPtr - 0x90); // pfVar5[-0x24] tiny float
                float storedFlag = *(float*)(effectPtr - 0x90);
                // float durationRemaining = *(float*)(effectPtr - 0x3c); // pfVar5[-0xf]
                float durationRemaining = *(float*)(effectPtr - 0x3c);
                // float currentStrength = *(float*)(effectPtr);   // *pfVar5
                float currentStrength = *(float*)(effectPtr);

                // Check: effect is active (index >= 0), belongs to this controller, and not already stopping
                if (activationFlag >= 0 && sourceIndex == controllerIndex && ((flags >> 1) & 1) == 0)
                {
                    bool bStop = false;

                    FUN_00ab4db0(&DAT_00e2aea0); // Acquire global vibration lock

                    // If duration remaining is nonzero and stored flag is zero (initial state), start the vibration
                    if (durationRemaining != 0.0f && storedFlag == 1.4013e-45f) // 1.4013e-45f is a sentinel
                    {
                        FUN_00ac2810();
                        *(float*)(effectPtr - 0x90) = 2.8026e-45f; // Set new state
                    }

                    // If current strength is non-negative and vibration system is active
                    if (currentStrength >= 0.0f && useVibration != 0)
                    {
                        float currentRumble = 0.0f;
                        FUN_00c9eac0();                                      // Begin rumble channel access
                        FUN_00c9cd00(0, &currentRumble);                     // Get rumble strength for channel 0 (left?) 
                        if (currentStrength <= currentRumble)
                        {
                            if (currentRumble == currentStrength)
                            {
                                // Set vibration pattern: (obj1, obj2, mode=2, params)
                                FUN_00c9cbe0(
                                    *(uint32_t*)(thisPtr + 0x580),           // e.g., player handle
                                    *(uint32_t*)(useVibration + 0x10),        // from vibration manager
                                    2,
                                    (float*)(effectPtr - 0x98)               // some parameter array? (local_18)
                                    );
                                *(float*)(effectPtr - 0x98) = currentStrength; // update sourceIndex? Actually overwriting local_18 array
                                FUN_00c9cd40(2, (float*)(effectPtr - 0x98));   // Apply vibration for channel 2
                                // Check if vibration completed (sentinel match)
                                if (*(float*)(effectPtr - 0x98 + 16) == DAT_00e2b05c) // fStack_10 is at local_18[4]? depends
                                {
                                    // Mark effect as stopping
                                    *(uint32_t*)(effectPtr - 4) |= 2; // set bit 1 in flags
                                    bStop = false; // keep false? Actually set bStop false but we later check bStop
                                    *(int*)(effectPtr - 0x94) = -1; // deactivate (set to -NAN)
                                    FUN_00c9cd40(1, 0); // Stop vibration channel 1
                                }
                            }
                        }
                        else // currentStrength > currentRumble -> need to reduce
                        {
                            *(uint32_t*)(effectPtr - 4) |= 2;   // Mark stopping
                            bStop = false;
                            *(int*)(effectPtr - 0x94) = -1;    // Deactivate
                            FUN_00c9cd40(1, 0);                // Stop channel 1
                            *(float*)(effectPtr) = currentRumble; // Clamp to current rumble
                        }
                        FUN_00c9eae0(); // End rumble channel access
                    }

                    // If not stopped, or after stop logic
                    if (bStop)
                    {
                        if (sourceIndex >= 0)
                        {
                            int* refCountAddr = (int*)(thisPtr + 0x81BC + sourceIndex * 16); // Ref count for this source
                            lockMutex((uint32_t*)refCountAddr);
                            *refCountAddr -= 1;
                            unlockMutex((uint32_t*)refCountAddr);
                        }
                        FUN_005ea0d0(); // Cleanup effect
                    }
                    FUN_00ab4e70(); // Release global lock
                    result = 1;     // Indicate processed
                }
                effectPtr += 0x5c; // Move to next effect (sizeof(RumbleEffect) = 92 bytes)
                effectCount--;
                if (effectCount != 0)
                    result = result; // Keep original return behavior (decompiler artifact)
            } while (effectCount != 0);
        }
    }
    return result;
}