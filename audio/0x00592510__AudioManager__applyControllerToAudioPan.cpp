// FUNC_NAME: AudioManager::applyControllerToAudioPan
// Function address: 0x00592510
// Purpose: Converts controller axis values (from EAX) into audio panning coordinates and applies them.
// The function takes an implicit 'this' pointer in ECX, and expects a ushort* controller axis array in EAX.
// Global variables: g_fPanCenter (0x00e44564) and g_fPanScale (0x00e44820) control the panning range.
// Called from FUN_00589360 (likely a controller input handler).
// Note: There is an unreachable block at 0x0059257e, possibly a removed conditional deadzone check.

#include <cstdint>

// Forward declaration of the target function (at 0x0056d040), which sets the actual audio pan.
void setAudioPan(float leftRight, float frontBack, void *context); // context = param_1 = this?

class AudioManager {
public:
    // Global audio pan settings (likely read from config)
    static float g_fPanCenter;   // offset 0x00e44564 - center value for pan
    static float g_fPanScale;    // offset 0x00e44820 - scaling factor for axis

    // Takes a pointer to controller axis shorts (e.g., left thumbstick X and Y) in EAX.
    // param_1 is the 'this' pointer (passed in ECX), but the function uses it as context for setAudioPan.
    void applyControllerToAudioPan() {
        // in_EAX is a pointer to an array of ushort (e.g., axis[0] = X, axis[2] = Y)
        // This is not a parameter; it's passed in EAX by the caller.
        // For clarity, we'll cast the implicit register value.
        // Note: The decompiler shows ushort* in_EAX, so we assume the caller loads EAX before call.
        // To reconstruct valid C++, we need to assume EAX is a member or global variable.
        // Because we cannot directly use EAX in C++, we must deduce the source.
        // The most likely source is a member variable or a global controller state pointer.
        // Given the pattern, we'll assume the class holds a pointer to controller axis data.
        
        // In the original x86 code:
        // mov eax, [this + 0x??]   ; eax = pointer to controller axis array
        // call FUN_00592510
        // So we'll use a member variable 'm_pControllerAxis' representing that pointer.
        
        ushort *axisData = this->m_pControllerAxis; // Replaces in_EAX
        
        float leftRight = g_fPanCenter - (float)axisData[0] * g_fPanScale;
        float frontBack = g_fPanCenter - (float)axisData[2] * g_fPanScale;
        
        setAudioPan(leftRight, frontBack, this);
    }

private:
    ushort *m_pControllerAxis; // offset ??? - pointer to controller axis array (e.g., from InputManager)
};