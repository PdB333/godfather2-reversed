// FUNC_NAME: applySmoothFloatAdjustment

// Function at 0x00755410. Adjusts a 64-bit value (packed int+float) based on a difference threshold,
// then forwards to FUN_00754d30 with additional parameters.
// The adjustment smooths the float portion towards a target value from a global time manager.

// Known constants from global data (addresses from Ghidra)
static const float kThreshold = *reinterpret_cast<const float*>(0x00d577a0);
static const float kDamping = *reinterpret_cast<const float*>(0x00d5eee4);

// Forward declaration of the helper that gets a pointer to the game's time/target manager.
// Returns a pointer to a structure with a float at offset 0x34.
extern "C" void* getTimeManager();  // FUN_00471610

// Forward declaration of the function that processes the adjusted value.
extern "C" void processAdjustedValue(/* ... */); // FUN_00754d30 (signature unknown)

void FUN_00755410(uint64_t* pPackedValue, int param2, int param3, int param4, int param5)
{
    // Get the manager pointer. Assume it's a global singleton.
    void* timeManager = getTimeManager();
    
    // Extract the float part from the packed value (stored at high 32 bits).
    // The packed value layout: low 32 bits = integer ID or flag, high 32 bits = float value.
    union {
        uint64_t packed;
        struct {
            int integerPart;
            float floatPart;
        };
    } current = { .packed = *pPackedValue };
    
    // Compute difference between current float and target float at manager+0x34.
    float target = *(reinterpret_cast<float*>(static_cast<char*>(timeManager) + 0x34));
    float diff = current.floatPart - target;
    
    // If the difference exceeds the threshold, apply damping toward the target.
    if (kThreshold < diff) {   // Only applies when current > target by more than threshold
        // Note: The original code reads the high part as float from the packed uint64,
        // then subtracts diff * kDamping, recombining with the integer part.
        // We perform the same operation using the union.
        current.floatPart = current.floatPart - diff * kDamping;
        // The integer part remains unchanged.
    }
    
    // Call the next function with the (possibly adjusted) packed value and the original extra parameters.
    // The last argument '1' is a hardcoded flag (purpose unknown).
    processAdjustedValue(&current.packed, param2, param3, param4, param5, 1);
}