// FUNC_NAME: InputDeviceManager::constructor
// Address: 0x0071e9a0
// Reconstructed C++ for The Godfather 2 (EARS engine)
// Member function: __thiscall
// Initializes singleton and calibration data for input device manager.

// Global singleton instance pointer
static InputDeviceManager* g_pInputDeviceManager; // DAT_0112ad48

// Random/floating-point table for calibration generation
static float g_randomFloatTable[ /* size unknown */ ]; // DAT_010c2680

// Base offsets for calibration values (6 bytes)
static unsigned char g_baseCalibrationOffsets[6]; // DAT_00d61efc

// Mask and counter for pseudo-random index selection
static unsigned int g_randMask; // DAT_010c2678
static unsigned int g_randCounter; // DAT_012054b4

class InputDeviceManager {
public:
    // vtable pointer (offset 0x00)
    void* vtable; // PTR_LAB_00d61f20

    // Calibration data for up to 6 analog axes (offset 0x04)
    // Typically: left stick X/Y (2), right stick X/Y (2), left/right triggers (2)
    char m_axisCalibration[6];

    // Constructor
    void __thiscall constructor() {
        g_pInputDeviceManager = this;
        this->vtable = &PTR_LAB_00d61f20; // InputDeviceManager vtable

        unsigned int i = 0;
        do {
            // Generate pseudo-random index into the float table
            unsigned int idx = g_randMask & g_randCounter;
            g_randCounter++;

            // Compute calibration byte:
            // (baseOffset[i] - 1) * randomFloat, then cast to char
            float factor = (float)((int)(g_baseCalibrationOffsets[i] - 1));
            float randomVal = *(float*)((unsigned char*)&g_randomFloatTable + idx * 4);
            char calibrated = (char)(int)(factor * randomVal);
            this->m_axisCalibration[i] = calibrated;

            i++;
        } while (i < 6);
    }
};