// FUNC_NAME: AttributeComponent::computeAttributeValue
// Reconstructed from 0x0086fe50
// Class: AttributeComponent (inferred from offset patterns)
// This function computes a float attribute value based on flags and a config table.

#include <cstdlib> // for rand()

// Forward declarations
struct AttributeConfig;
extern AttributeConfig* getGlobalAttributeConfig(); // At 0x008fa210
extern void updateBeforeAttributeChange(); // At 0x0086e8b0 (likely does validation or pre-update logic)

// Global random scale factor (1.0f / RAND_MAX, where RAND_MAX is 32767 on MSVC)
static const float kRandScale = 1.0f / 32767.0f; // DAT_00e44590 assumed

class AttributeComponent {
    // Offsets relative to this pointer:
    // +0x6c: flags (uint32)
    // +0xa4: currentValue (float)
    // +0xa8: someCounter (int32)
    // +... other members

    enum Flags {
        kFlagOverride     = 0x80,   // bit 7: use config values instead of random
        kFlagUseSecondary = 0x200,  // bit 9: use secondary value from config
        kFlagValueSet     = 0x100   // bit 8: indicates a value has been explicitly set
    };

    uint32_t flags;        // +0x6c
    float currentValue;    // +0xa4
    int32_t someCounter;   // +0xa8

public:
    void computeAttributeValue();
};

// Config structure returned by getGlobalAttributeConfig()
struct AttributeConfig {
    // Offsets are absolute from pointer
    float baseValue;       // +0x8
    // Padding up to +0x68
    float secondaryValue;  // +0x68
    // Padding up to +0x90
    float minValue;        // +0x90
    float range;           // +0x94  (max - min)
};

void AttributeComponent::computeAttributeValue() {
    AttributeConfig* config = getGlobalAttributeConfig();
    if (config != nullptr) {
        updateBeforeAttributeChange();

        if (flags & kFlagOverride) {
            // Use config values directly
            someCounter = 0; // +0xa8 set to 0

            if (flags & kFlagUseSecondary) {
                currentValue = config->secondaryValue;
            } else {
                currentValue = config->baseValue;
            }
            flags |= kFlagValueSet; // Mark as explicitly set
            return;
        }

        // Not overridden: randomize between min and max
        int randomInt = rand();
        currentValue = (float)randomInt * kRandScale * config->range + config->minValue;
        flags &= ~kFlagValueSet; // Clear explicit-set flag
    }
}