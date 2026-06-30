// FUNC_NAME: StreamManager::setBackgroundAudioPair
// Address: 0x00536800
// Role: Sets the current background music pair based on an area index and a flag.
//       The two handles (gCurrentAudioA, gCurrentAudioB) are loaded with predefined
//       constants from the game's audio data. For area indices 2 and 3, the second
//       handle can be substituted if the flag is false (useAlternate == false).
//       If the audio manager pointer matches a specific sentinel instance, the
//       selected handles are activated via activateAudioHandle.

// Globals (offsets from .data section, not part of a struct):
extern unsigned int gCurrentAudioA;   // offset 0x0121a200
extern unsigned int gCurrentAudioB;   // offset 0x0121a204
extern unsigned int gAudioManagerInstance;   // offset 0x012058e8
extern unsigned int gSpecificAudioManagerInstance;   // offset 0x0121a1f0

// Predefined audio handle constants (could be pointers to stream assets)
extern unsigned int gAudioHandle_Area0_A;   // DAT_012198f8
extern unsigned int gAudioHandle_Area0_B;   // DAT_01219900
extern unsigned int gAudioHandle_Area1_A;   // DAT_0121a358
extern unsigned int gAudioHandle_Area1_B;   // DAT_0121a35c
extern unsigned int gAudioHandle_Area2_A;   // DAT_0121a350
extern unsigned int gAudioHandle_Area2_B;   // DAT_0121a360
extern unsigned int gAudioHandle_Area2_B_Alt;   // DAT_0121a354
extern unsigned int gAudioHandle_Area3_A;   // DAT_0121a364
extern unsigned int gAudioHandle_Area3_B;   // DAT_0121a360
extern unsigned int gAudioHandle_Area3_B_Alt;   // DAT_0121a354
extern unsigned int gAudioHandle_Area4_A;   // DAT_0121a368
extern unsigned int gAudioHandle_Area4_B;   // DAT_0121a36c
extern unsigned int gAudioHandle_Area5_A;   // DAT_0121a370
extern unsigned int gAudioHandle_Area5_B;   // DAT_0121a374

// Forward declaration of the function that activates the audio handle
void activateAudioHandle(unsigned int handle); // 0x0060a460

void __fastcall setBackgroundAudioPair(int areaIndex, bool useAlternate)
{
    switch (areaIndex) {
    case 0:
        gCurrentAudioB = gAudioHandle_Area0_A;  // DAT_012198f8
        gCurrentAudioA = gAudioHandle_Area0_B;  // DAT_01219900
        break;
    case 1:
        gCurrentAudioA = gAudioHandle_Area1_A;  // DAT_0121a358
        gCurrentAudioB = gAudioHandle_Area1_B;  // DAT_0121a35c
        break;
    case 2:
        gCurrentAudioA = gAudioHandle_Area2_A;   // DAT_0121a350
        gCurrentAudioB = gAudioHandle_Area2_B;   // DAT_0121a360
        if (!useAlternate) {
            gCurrentAudioB = gAudioHandle_Area2_B_Alt; // DAT_0121a354
        }
        break;
    case 3:
        gCurrentAudioB = gAudioHandle_Area3_B;   // DAT_0121a360
        if (!useAlternate) {
            gCurrentAudioB = gAudioHandle_Area3_B_Alt; // DAT_0121a354
        }
        gCurrentAudioA = gAudioHandle_Area3_A;   // DAT_0121a364
        break;
    case 4:
        gCurrentAudioA = gAudioHandle_Area4_A;   // DAT_0121a368
        gCurrentAudioB = gAudioHandle_Area4_B;   // DAT_0121a36c
        break;
    case 5:
        gCurrentAudioB = gAudioHandle_Area5_A;   // DAT_0121a370
        gCurrentAudioA = gAudioHandle_Area5_B;   // DAT_0121a374
        break;
    }

    // Only activate the audio if the global manager instance equals the sentinel
    if (gAudioManagerInstance == &gSpecificAudioManagerInstance) {
        activateAudioHandle(gCurrentAudioB);
        activateAudioHandle(gCurrentAudioA);
    }
}