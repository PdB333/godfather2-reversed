// FUNC_NAME: ProjectileSpawnData::init
// Address: 0x005205b0
// Role: Initializes projectile spawn parameters from an emitter and a 4x4 matrix (passed in EAX).
// The object at 'this' stores the matrix at +0x50..+0x8c, and uses the source structure to compute
// initial speed, spread, and angular velocity based on random and global constants.

#include <cmath>

// Forward decl: the emitter/source structure
struct ProjectileSource {
    // +0x44: bit flags (bit0 = randomize speed? bit1 = randomize direction?)
    unsigned char flags48[0x4c]; // placeholder
    float spreadBase;           // +0x4c
    float spreadRate;           // +0x50
    float speedBase;            // +0x70
    float speedRandomFactor;    // +0x74
    float directionXFactor;     // +0xb0
    float directionYFactor;     // +0xb4
};

// Global constants (likely set from config)
extern float g_speedScale;    // DAT_00e44760
extern float g_spreadAngle;   // DAT_00e2b1a4

// External functions (EA random, sin, cos)
extern float getRandomFloat();       // FUN_004e41b0
extern double cos(double);          // FUN_00b99fcb
extern double sin(double);          // FUN_00b99e20

class ProjectileSpawnData {
public:
    // Fields:
    // +0x00 - vtable? (not used here)
    // +0x10: pointer to source (ProjectileSource)
    // +0x14: int (unused? set to 0)
    // +0x18: int (unused? set to 0)
    // +0x1c: float (initial speed computed)
    // +0x20: float (horizontal spread velocity)
    // +0x24: float (vertical spread velocity)
    // +0x38: float (spread angle azimuth)
    // +0x3c: float (spread angle elevation)
    // +0x50..+0x8c: 4x4 transformation matrix (16 floats)

    // __thiscall: this in ECX, param1 in stack, param2 in stack, matrix pointer in EAX
    void __thiscall init(ProjectileSource* source, float* outSpeed, const float* matrix) {
        // Store the matrix from EAX (convention: 16 floats)
        float* dest = reinterpret_cast<float*>(this) + 0x50 / 4; // offset +0x50
        for (int i = 0; i < 16; i++) {
            dest[i] = matrix[i];
        }

        // Store source pointer
        *(ProjectileSource**)((char*)this + 0x10) = source;

        // Clear unused fields ?
        *(int*)((char*)this + 0x14) = 0;
        *(int*)((char*)this + 0x18) = 0;

        // Initialize base speed from source
        float speed = *(float*)((char*)source + 0x70); // source->speedBase
        *(float*)((char*)this + 0x1c) = speed;

        // If source has speed randomization, apply random offset
        if (*(float*)((char*)source + 0x74) != 0.0f) { // source->speedRandomFactor
            float r = getRandomFloat();
            speed += r * *(float*)((char*)source + 0x74);
            *(float*)((char*)this + 0x1c) = speed;
        }

        // Handle spread angles
        if (!(*(unsigned char*)((char*)source + 0x44) & 1)) {
            // No spread randomization: use global constant, elevation zero
            *outSpeed = 0.0f;
            *(float*)((char*)this + 0x38) = g_spreadAngle;   // +0x38
            *(float*)((char*)this + 0x3c) = 0.0f;             // +0x3c
        } else {
            // Randomize spread angle
            float r = getRandomFloat();
            float angle = r * g_speedScale;  // g_speedScale maps to [0,1] * max?
            *outSpeed = angle;
            double dAngle = (double)angle;
            *(float*)((char*)this + 0x3c) = (float)sin(dAngle);
            *(float*)((char*)this + 0x38) = (float)cos(dAngle);
        }

        // Handle direction spread (bit 1)
        if (*(unsigned char*)((char*)source + 0x44) & 2) {
            float r = getRandomFloat();
            // Compute horizontal spread
            float spreadH = (float)(int)(r * *(float*)((char*)source + 0x4c)) * *(float*)((char*)source + 0xb0);
            *(float*)((char*)this + 0x20) = spreadH;

            // Compute vertical spread (reuse same random? Actually calls getRandomFloat again)
            r = getRandomFloat();
            float spreadV = (float)(int)(r * *(float*)((char*)source + 0x50)) * *(float*)((char*)source + 0xb4);
            *(float*)((char*)this + 0x24) = spreadV;
        } else {
            *(float*)((char*)this + 0x20) = 0.0f;
            *(float*)((char*)this + 0x24) = 0.0f;
        }
    }
};