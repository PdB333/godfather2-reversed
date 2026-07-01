// FUNC_NAME: ChoiceDialog::processInput

// Reconstructed from Ghidra at 0x007bf490
// Handles keyboard input for a two-option dialog (keys '1' and '2')
// Sets internal state and plays menu sounds / audio events based on selection

#include <cstdint>

// Forward declarations of external functions
// These are likely from the EARS engine or game code
bool isOptionAvailable(int optionIndex);                              // FUN_0079e970
uint32_t getOptionStatus(int optionIndex);                            // FUN_00798f50 – returns a handle or resource ID
bool isContextActive();                                               // FUN_00481640 – e.g., cutscene active?
void playMenuSound(int soundIndex, void* audioManager);               // FUN_007fb9b0 – 0=select, 1=back?
void playAudioEvent(uint32_t eventHash, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, float arg7); // FUN_004ac480
void* g_audioManager = reinterpret_cast<void*>(0x00d6e188);          // Global audio manager pointer

// Base class handler for unrecognized keys
uint32_t baseProcessInput(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6);

class ChoiceDialog {
public:
    // Offsets:
    // +0x74: int m_selectedOption (1 or 2)
    // +0x58: void* m_pContextData → pointer to context struct:
    //   +0x2358: bool m_bFlag (byte)
    //   +0x2360: int m_optionValue

    uint32_t processInput(uint32_t param2, uint32_t param3, uint32_t param4, int keyCode, uint32_t param6) {
        if (keyCode == 0x31) { // ASCII '1'
            // First try option index 5
            uint32_t optionHandle = getOptionStatus(5);
            if (isOptionAvailable(optionHandle)) {
                m_selectedOption = 2;
                playMenuSound(0, g_audioManager);
                return 1;
            }
            // Then try option index 6
            optionHandle = getOptionStatus(6);
            if (isOptionAvailable(optionHandle)) {
                m_selectedOption = 1;
                playMenuSound(1, g_audioManager);
                return 1;
            }
            // Fallback: check context
            if (isContextActive()) {
                char* flagPtr = reinterpret_cast<char*>(m_pContextData) + 0x2358;
                if (*flagPtr == '\0') {
                    int optionValue = *reinterpret_cast<int*>(reinterpret_cast<char*>(m_pContextData) + 0x2360);
                    if (optionValue != 0) {
                        m_selectedOption = 2;
                        playMenuSound(0, g_audioManager);
                        *flagPtr = 1;
                    } else {
                        m_selectedOption = 1;
                        playMenuSound(1, g_audioManager);
                        *flagPtr = 1;
                    }
                }
            }
        } else if (keyCode == 0x32) { // ASCII '2'
            if (m_selectedOption == 1) {
                playAudioEvent(0x2a900f8, 0, 0xffffffff, 1, 0, 1, 0, 1.0f);
            } else if (m_selectedOption == 2) {
                playAudioEvent(0x21587bcb, 0, 0xffffffff, 1, 0, 1, 0, 1.0f);
            }
        } else {
            // Delegate to base class
            return baseProcessInput(reinterpret_cast<uint32_t>(this), param2, param3, param4, keyCode, param6);
        }
        return 1;
    }

private:
    int m_selectedOption;       // +0x74
    void* m_pContextData;       // +0x58 – points to a larger context structure
};