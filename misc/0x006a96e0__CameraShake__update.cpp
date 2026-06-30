// FUNC_NAME: CameraShake::update
// Function address: 0x006a96e0
// This function manages the lifecycle of a camera shake effect.
// It either initializes a new shake (if conditions are met) or resets the shake state.

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ulonglong;

// Global variables (from decompiled code)
extern float DAT_00e44598;          // Current time or threshold
extern float DAT_01205214;          // Default shake start value
extern uint DAT_010c2678;           // Random table base address (array of floats)
extern uint DAT_012054b4;           // Random index counter
extern uint DAT_012069c4;           // Timer or resource handle
extern ulonglong _DAT_00d5780c;     // Zero value (longlong)

// External functions
int __fastcall FUN_006a9870(void);  // Shake update/apply function
void __fastcall FUN_005e6660(int ptr); // Release/destroy resource
void __fastcall FUN_004086d0(uint* timer); // Reset timer

// Class definition (inferred from offsets)
class CameraShake {
public:
    // Offsets relative to this pointer
    // +0x88: pointer to resource A (e.g., sound effect)
    int* m_pResourceA;          // +0x88
    // +0x8c: padding? (not used)
    // +0x90: padding?
    // +0x94: padding?
    // +0x98: padding?
    // +0x9c: padding?
    // +0xa0: pointer to resource B
    int* m_pResourceB;          // +0xa0
    // +0xa4: padding?
    // +0xa8: padding?
    // +0xac: minimum shake magnitude
    float m_fMinMagnitude;      // +0xac
    // +0xb0: maximum shake magnitude
    float m_fMaxMagnitude;      // +0xb0
    // +0xb4: padding?
    // +0xb8: padding?
    // +0xbc: padding?
    // +0xc0: shake duration threshold (time to stop)
    float m_fDuration;          // +0xc0
    // +0xc4: start X offset
    float m_fStartX;            // +0xc4
    // +0xc8: padding?
    // +0xcc: end X offset
    float m_fEndX;              // +0xcc
    // +0xd0: start Y offset
    float m_fStartY;            // +0xd0
    // +0xd4: padding?
    // +0xd8: end Y offset
    float m_fEndY;              // +0xd8
    // +0xdc: current end X (or target)
    float m_fTargetX;           // +0xdc
    // +0xe0: current shake magnitude
    float m_fCurrentMagnitude;  // +0xe0
    // +0xe4: current end Y (or target)
    float m_fTargetY;           // +0xe4
    // +0xe8: shake enabled flag
    byte m_bEnabled;            // +0xe8
    // +0xe9: shake started flag
    byte m_bStarted;            // +0xe9
    // +0xea: padding
    // +0xeb: padding
    // +0xec: padding
    // +0xf0: padding
    // ... (size unknown)
};

// Reconstructed function
int __fastcall CameraShake::update(CameraShake* this) {
    // Check if shake is enabled, not yet started, and current time is less than duration
    if (this->m_bEnabled != 0 && this->m_bStarted == 0 && DAT_00e44598 < this->m_fDuration) {
        // Initialize shake start and end values
        // Copy target values to start and end offsets
        this->m_fStartX = this->m_fTargetX;
        this->m_fStartY = this->m_fTargetY;
        this->m_fEndX = this->m_fTargetX;
        this->m_fEndY = this->m_fTargetY;
        // Set start offsets to default shake value
        this->m_fStartX = DAT_01205214;
        this->m_fStartY = DAT_01205214;
        // Mark as started
        this->m_bStarted = 1;
        // Set target X to default plus duration (end time?)
        this->m_fTargetX = DAT_01205214 + this->m_fDuration;
        // Compute random magnitude using a global random table
        uint randomIndex = DAT_010c2678 & DAT_012054b4; // Mask with table size? (assumed power of 2)
        DAT_012054b4++; // Increment counter
        // Interpolate magnitude between min and max using random factor from table
        float randomFactor = *(float*)(&DAT_010c2680 + randomIndex * 4); // Table of floats
        this->m_fCurrentMagnitude = (this->m_fMaxMagnitude - this->m_fMinMagnitude) * randomFactor + this->m_fMinMagnitude;
        // Reset target Y to 0
        this->m_fTargetY = 0.0f;
        // Call the update/apply function
        FUN_006a9870();
        return 1;
    }

    // If shake is not active or time exceeded, release resources and reset state
    if (this->m_pResourceA != 0) {
        FUN_005e6660((int)this->m_pResourceA);
        this->m_pResourceA = 0;
    }
    if (this->m_pResourceB != 0) {
        FUN_005e6660((int)this->m_pResourceB);
        this->m_pResourceB = 0;
    }
    // Reset a global timer
    FUN_004086d0(&DAT_012069c4);
    // Zero out all shake state fields
    ulonglong zero = (ulonglong)_DAT_00d5780c; // Zero value
    this->m_fTargetX = *(float*)&zero; // Actually, the decompiled code sets longlong to zero, then splits into float and uint
    this->m_fStartX = *(float*)&zero;
    this->m_fStartY = *(float*)&zero;
    this->m_fTargetY = (float)(uint)zero; // The uint part of the longlong
    this->m_fEndX = (float)(uint)zero;
    this->m_fEndY = (float)(uint)zero;
    this->m_bEnabled = 0;
    this->m_bStarted = 0;
    return 1;
}