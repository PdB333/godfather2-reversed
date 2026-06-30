// FUNC_NAME: VehicleBrain::constructor
// Address: 0x00749f60
class VehicleBrain : public BaseClass {
public:
    // Constructor
    // param_2 and param_3 likely passed to base (e.g., scene entity, config)
    VehicleBrain(void* param_2, void* param_3) {
        // Call base constructor
        BaseClass::constructor(param_2, param_3);

        // Set vtable to base class vtable (temporary)
        this->vtable = &kVehicleBrainBaseVTable;  // PTR_LAB_00d643d0

        // Initialize fields
        this->someFlag = 0;               // param_1[0x1c] at offset 0x70
        float randomFloat = (float)_rand() * kRandomMultiplier1 * kRandomMultiplier2 + kRandomOffset;
        this->randomValue = randomFloat;  // param_1[0x20] at offset 0x80

        // Set final vtable to derived class vtable
        this->vtable = &kVehicleBrainVTable; // PTR_LAB_00d6440c

        // Set byte fields
        this->someByte1 = 0;              // offset 0x84
        this->someByte2 = *(*(this + 0x17) + 0x2674); // offset 0x85, copy from data block at +0x5C, +0x2674

        // Copy data from global manager (likely a singleton providing transform or state)
        void* globalPtr = SingletonManager::getSomeData(); // FUN_00471610
        this->dataA = *(globalPtr + 0x30).as<int64>();    // param_1[0x1d]/[0x1e] at offsets 0x74/0x78
        this->dataB = *(globalPtr + 0x38).as<int>();      // param_1[0x1f] at offset 0x7C
    }

private:
    // Vtable pointer (offset 0x00)
    void* vtable;

    // Members determined from offsets:
    // +0x70: uint32 someFlag;
    // +0x74: uint32 dataA_lo;
    // +0x78: uint32 dataA_hi;
    // +0x7C: uint32 dataB;
    // +0x80: float randomValue;
    // +0x84: uint8 someByte1;
    // +0x85: uint8 someByte2;
    // Pointer at +0x5C to some data block
    // ...
};

// External globals used (from decompilation)
extern void* PTR_LAB_00d643d0;   // base class vtable
extern void* PTR_LAB_00d6440c;   // derived class vtable
extern float DAT_00e44590;       // random multiplier 1
extern float DAT_00d5c454;       // random multiplier 2
extern float _DAT_00d643cc;      // random offset
extern int _rand();              // standard C rand

// Base class constructor at 0x0073e160
// Singleton manager function at 0x00471610