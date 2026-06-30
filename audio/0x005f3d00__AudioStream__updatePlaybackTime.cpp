// FUNC_NAME: AudioStream::updatePlaybackTime

#include <cstdint>

// External globals (from decompilation)
extern int* g_gameBase;                // DAT_01223510
extern double g_2p32;                  // _DAT_00e44708
extern double g_timeThreshold;         // DAT_00e2af60

// External engine functions (EARS)
extern int __stdcall FUN_005e9d10(void);
extern int __stdcall FUN_00c9cbe0(int, int, int, double*);
extern void __stdcall FUN_00c9eac0(void);
extern void __stdcall FUN_00c9cd40(int, double*);
extern void __stdcall FUN_00c9eae0(void);

// Class definition based on field offsets
class AudioStream {
public:
    // Offset 0x80: current playback time (seconds)
    double playTime;

    // Offset 0x9C: index into global stream slot array (0x10 per slot)
    int slotIndex;

    // Offset 0x104: stream duration (treated as unsigned, stored as signed int)
    int rawDuration;

    // Offset 0x10C: pointer to stream name string
    char* name;

    // Offset 0x134: flag (cleared to 0 on success)
    int updateFlag;

    // Constructor/destructor not fully known
};

// Reconstructed member function
int AudioStream::updatePlaybackTime() {
    int iVar1;
    int iVar3;
    double currentTime;       // local_50
    double adjustedTime;      // local_48 (reused)
    char* namePtr = this->name;   // local_30
    int unused = 0;           // local_18
    char* thisPtr = reinterpret_cast<char*>(this); // local_38
    int magicConstant = 0x2ea8fb98; // local_20

    // Check if the global game base and slot array entry are valid
    if (*(int*)(*(int*)(g_gameBase + (this->slotIndex * 0x10) + 0x81c4)) != 0) {
        iVar3 = FUN_005e9d10(); // Get some manager pointer
        iVar1 = *(int*)(g_gameBase + 0x580); // Another global pointer

        if ((iVar1 != 0) && (this->name[0] != '\0')) {
            // Get current stream time from the stream manager (slot identified by iVar3+0x10, parameter index 5)
            FUN_00c9cbe0(iVar1, *(int*)(iVar3 + 0x10), 5, &currentTime);

            // Convert rawDuration (signed int) to unsigned double
            adjustedTime = static_cast<double>(this->rawDuration);
            if (this->rawDuration < 0) {
                adjustedTime += g_2p32; // Account for unsigned overflow
            }

            // Prepare local variables for update callback (may be used by engine)
            namePtr = this->name;
            thisPtr = reinterpret_cast<char*>(this);
            magicConstant = 0x2ea8fb98;
            unused = 0;

            // Begin stream update transaction?
            FUN_00c9eac0();

            // Overwrite currentTime with the object's stored playTime
            currentTime = this->playTime;

            // Check if we are close to the playhead edge; if so, reset to 0
            // (Threshold g_timeThreshold, duration from global pointer at iVar2+0x580+8)
            if (currentTime - g_timeThreshold < *(double*)(*(int*)(g_gameBase + 0x580) + 8)) {
                currentTime = 0.0;
            }

            // Set stream parameter 5 to the computed time
            FUN_00c9cd40(5, &currentTime);

            // End stream update transaction
            FUN_00c9eae0();

            // Clear the update flag
            this->updateFlag = 0;
            return 1;
        }
    }
    return 0;
}