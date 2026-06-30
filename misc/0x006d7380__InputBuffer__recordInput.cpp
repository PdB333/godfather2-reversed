// FUNC_NAME: InputBuffer::recordInput
// Address: 0x006d7380
// This function records an input event into a circular history buffer.
// The buffer size is either 3 or 5 slots depending on a condition related to
// player state (float at player+0x11c). Returns a pointer to the end of the buffer
// (either &counter or past last slot).

#include <cstdint>

// Forward declarations of external functions
extern "C" int __fastcall isGameActive();  // FUN_00410eb0
extern "C" void* __fastcall getPlayerData(uint8_t playerId); // FUN_00411070

// Global variables from data section
extern float g_globalTimeDivisor;      // DAT_00d5780c / DAT_012067e8? Actually two separate globals
extern float g_timeScale;              // DAT_012067e8
extern float g_globalTime;             // _DAT_00d5780c
extern float g_someGlobalThreshold;    // _DAT_00d5f530
extern uint32_t g_gameManagerPtr;      // DAT_012233b4
extern float g_anotherGlobal;          // DAT_00d5f52c

class InputBuffer {
public:
    // Offsets:
    // +0x20C: array of (uVar4) uint32_t entries (buffer)
    // +0x220: uint32_t nextWriteIndex (modulo uVar4)
    // The buffer size uVar4 is either 5 (default) or 3 (if condition holds)
    
    // This method returns a pointer to the end of the buffer (address after last slot)
    void* __thiscall recordInput(uint32_t inputValue) {
        float ratio = g_globalTime / g_timeScale;
        bool gameActive = isGameActive() != 0;
        
        if (!gameActive || g_someGlobalThreshold >= ratio) {
            // Condition not met, return early (no recording)
            return (void*)((uintptr_t)this + 0x220); // or some other? Decompiler returns iVar1
        }
        
        uint32_t bufferSize = 5; // default size
        
        // Get player data from global pointer + offset 0x564 (probably playerId)
        uint8_t playerId = *(uint8_t*)(g_gameManagerPtr + 0x564);
        void* playerData = getPlayerData(playerId);
        
        // Check player's health or something at +0x11C
        float playerFloat = *(float*)((uintptr_t)playerData + 0x11C);
        if (g_anotherGlobal < playerFloat) {
            bufferSize = 3; // smaller buffer when condition holds
        }
        
        // Write inputValue to current slot
        uint32_t* buffer = (uint32_t*)((uintptr_t)this + 0x20C);
        uint32_t* nextIndexPtr = (uint32_t*)((uintptr_t)this + 0x220);
        uint32_t currentIndex = *nextIndexPtr;
        buffer[currentIndex] = inputValue;
        
        // Advance index circularly
        uint32_t newIndex = currentIndex + 1;
        *nextIndexPtr = newIndex % bufferSize;
        
        // Return pointer to the end of the buffer (or to the nextIndex location)
        // The original code computed this pointer; we mimic the logic.
        uint32_t iVar2 = 0;
        void* resultPtr;
        if (bufferSize > 3) {
            // bufferSize == 5 => return &nextIndexPtr (i.e., offset 0x220)
            resultPtr = (void*)((uintptr_t)this + 0x210 + 0x10); // => 0x220
        } else {
            // bufferSize == 3 => return address just after buffer end (0x20C + 3*4 = 0x218)
            resultPtr = (void*)((uintptr_t)this + 0x20C + (bufferSize - iVar2) * 4);
        }
        return resultPtr;
    }
};