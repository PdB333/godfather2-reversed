// FUNC_NAME: Sentient::getScaledAttribute

class Sentient; // forward declaration

extern float DEFAULT_MULTIPLIER; // _DAT_00d5780c - default scaling factor

void* getGlobalMultiplierProvider(); // FUN_00800a90 - returns pointer to a global multiplier object

float Sentient::getScaledAttribute(int index) {
    float multiplier = DEFAULT_MULTIPLIER;

    // Check flag at offset +0x10 -> +0x8e0, bit 10 (0x400)
    // If set, use multiplier from global provider
    if ((*(unsigned int*)(*(int*)(this + 0x10) + 0x8e0) >> 10 & 1) != 0) {
        void* provider = getGlobalMultiplierProvider();
        if (provider != nullptr) {
            // +0x338 is the multiplier value in the provider
            multiplier = *(float*)((int)provider + 0x338);
        }
    }

    // Array of floats at this+0x3c, indexed by parameter
    return *(float*)(this + 0x3c + index * 4) * multiplier;
}