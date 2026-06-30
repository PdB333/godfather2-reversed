// FUNC_NAME: SnapTargetManager::initDefaultSnapTargets
// This function initializes a global array of 16 snap targets (each 4 floats) for the aim assist system.
// It sets a rotating diagonal pattern: for target i, the field (i % 4) is set to kDefaultSnapValue, others to 0.
// Called from initialization routines at 0x004e2870 and 0x004e23c0.
// The constant at 0x00e2b1a4 is likely a float (e.g., 1.0f or -1.0f) defining the default snap offset.

static const float kDefaultSnapValue = *(float*)0x00e2b1a4; // default snap offset constant

struct SnapTarget {
    float x; // +0x00
    float y; // +0x04
    float w; // +0x08
    float h; // +0x0c
};

// Global array of 16 snap targets (at address 0x01218d40)
extern SnapTarget gSnapTargets[16];

void initDefaultSnapTargets() {
    for (int i = 0; i < 16; i++) {
        int field = i % 4; // rotating field index
        // Set the rotating field to the default value, others to zero
        gSnapTargets[i].x = (field == 0) ? kDefaultSnapValue : 0.0f;
        gSnapTargets[i].y = (field == 1) ? kDefaultSnapValue : 0.0f;
        gSnapTargets[i].w = (field == 2) ? kDefaultSnapValue : 0.0f;
        gSnapTargets[i].h = (field == 3) ? kDefaultSnapValue : 0.0f;
    }
}