// FUNC_NAME: SoundEmitter::playAtPosition (audio playback with position check)
// Address: 0x005ef160
// Reconstructed C++ for The Godfather 2 (EARS engine)

// Known callees:
// FUN_005e9d10 - probably isSoundValid or canPlay
// FUN_00c9eac0 - startUpdate / lock
// FUN_00c9cd40 - setAudioParameter(which, value) e.g., 0=position,1=minDist,4=maxDist,5=stop
// FUN_00c9eae0 - endUpdate / unlock

// Global threshold (likely maximum audible distance)
extern float DAT_00e2b05c;

// Unknown helper functions
bool __fastcall FUN_005e9d10();                    // check if sound system is ready
void __fastcall FUN_00c9eac0();                    // begin audio update lock
void __fastcall FUN_00c9cd40(int which, void* value); // set audio parameter
void __fastcall FUN_00c9eae0();                    // end audio update unlock

bool __thiscall SoundEmitter::playAtPosition(int param_1, int param_2)
{
    // Field at +0x580: pointer to sound instance or audio channel
    if (*(int*)(param_1 + 0x580) != 0) {
        if (FUN_005e9d10() != 0) {
            FUN_00c9eac0();                // begin update

            // param_2 is actually a float (x-coordinate) passed as integer
            float positionX = (float)param_2;
            float positionY;               // uninitialized (potentially written by setPosition)
            FUN_00c9cd40(0, &positionX);   // set source position (only x set, y unset?)

            // Compare global threshold with the y component (which may have been set by the previous call)
            // Since positionX is only one float, positionY remains on stack and may be garbage or set by setPosition
            if (DAT_00e2b05c < positionY) {
                // Sound is audible (within range?) -> play it
                FUN_00c9cd40(5, 0);        // possibly reset or stop
                FUN_00c9cd40(1, &positionX); // set min distance
                FUN_00c9cd40(4, &positionX); // set max distance

                // Store the sound ID (param_2) in field +0x04
                *(int*)(param_1 + 4) = param_2;

                FUN_00c9eae0();            // end update
                return 1;                  // success
            }
        }
        FUN_00c9eae0();                    // end update (on failure)
    }
    return 0;                              // failure
}