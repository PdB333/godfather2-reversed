// FUNC_NAME: VehiclePhysics::updateMotion
#include <cmath>
#include <cstdint>

// Forward declarations of external functions
extern float sqrtApprox(float); // 0x00414a80
extern bool checkCollisionOrSomething(); // 0x00550b80

// Global constants (from .data)
extern const float g_one;        // DAT_00e44564
extern const float g_smallThreshold; // DAT_00e2d99c
extern const float g_speedScale;     // DAT_00e44868
extern const uint32_t g_frameCounter; // DAT_01205220

class VehiclePhysics {
public:
    // Offsets:
    // +0x00: vtable? etc.
    // +0x10: some factor? (used in velocity comparison)
    // +0x30: active flag (byte)
    // +0x50-0x5c: target velocity (desired linear/angular velocity)
    // +0x70-0x7c: current velocity (linear X,Y,Z + angular?)
    // +0x80: linear damping factor? (coeff for X)
    // +0x84: linear damping Y?
    // +0x88: linear damping Z?
    // +0x90: angular damping X?
    // +0x94: angular damping Y?
    // +0x98: angular damping Z?
    // +0x9c: angular damping W? (maybe angular factor for fourth component)
    // +0xa0: mass (float)
    // +0xb8: some integer (frames for braking? used in modulo)
    // +0xe4: flags (bit1 = 'stopped'?, bit5 = 'onGround'?)

    uint32_t updateMotion(float dt) {
        float mass = *(float*)(this + 0xa0); // +0xa0
        uint32_t flags = *(uint32_t*)(this + 0xe4);
        uint8_t active = *(uint8_t*)(this + 0x30);

        if (active == 0) {
            // Active path: apply damping forces
            float velX = *(float*)(this + 0x70);
            float velY = *(float*)(this + 0x74);
            float velZ = *(float*)(this + 0x78);
            float velW = *(float*)(this + 0x7c); // angular or extra

            float dampX = *(float*)(this + 0x80);
            float dampY = *(float*)(this + 0x84);
            float dampZ = *(float*)(this + 0x88);
            float angDampX = *(float*)(this + 0x90);
            float angDampY = *(float*)(this + 0x94);
            float angDampZ = *(float*)(this + 0x98);
            float angDampW = *(float*)(this + 0x9c);

            // Compute damping forces (simplified: (g_one - damping * angDamp * mass * dt) )
            float forceX = g_one - dampX * angDampX * mass * dt;
            float forceY = g_one - dampY * angDampY * mass * dt;
            float forceZ = g_one - dampZ * angDampZ * mass * dt;

            // Update velocity
            velX += forceX;
            velY += forceY;
            velZ += forceZ;
            // velW unchanged? Actually the code does not modify velW directly, but adds something:
            // In decomp: *(float *)(unaff_ESI + 0x78) = fVar4 + (fVar2 - ... )? Wait careful.

            // Re-read the original more carefully:
            // fVar4 = *(float *)(unaff_ESI + 0xa0); // mass
            // fVar3 = DAT_00e44564 - *(float *)(unaff_ESI + 0x80) * *(float *)(unaff_ESI + 0x90) * fVar4 * param_1;
            // fVar5 = DAT_00e44564 - *(float *)(unaff_ESI + 0x94) * *(float *)(unaff_ESI + 0x84) * fVar4 * param_1;
            // *(float *)(unaff_ESI + 0x70) = fVar3 + *(float *)(unaff_ESI + 0x70);
            // *(float *)(unaff_ESI + 0x74) = *(float *)(unaff_ESI + 0x74) + fVar5;
            // fVar4 = *(float *)(unaff_ESI + 0x78) + (fVar2 - *(float *)(unaff_ESI + 0x98) * *(float *)(unaff_ESI + 0x88) * fVar4 * param_1);
            // where fVar2 = DAT_00e44564 initially? Actually fVar2 = DAT_00e44564; then fVar4 is used as mass in the last line.

            // So the pattern: for X and Y: newVel = oldVel + (1 - damp * angDamp * mass * dt)
            // For Z: newVel = oldVel + (1 - dampZ * angDampZ * mass * dt)
            // But note the indices: In Z, they used *(float *)(unaff_ESI + 0x98) (angDampZ?) and *(float *)(unaff_ESI + 0x88) (dampZ?). Yes.

            // Also note: For Y, they used angDampY and dampY, but order: dampY first, then angDampY? In code: *(0x94) * *(0x84) => angDampY * dampY. But the result subtracted from 1.
            // For X: *(0x80) * *(0x90) => dampX * angDampX

            // So reconstruct:

            float factorX = g_one - dampX * angDampX * mass * dt;
            float factorY = g_one - dampY * angDampY * mass * dt;
            float factorZ = g_one - dampZ * angDampZ * mass * dt;

            *(float*)(this + 0x70) += factorX;
            *(float*)(this + 0x74) += factorY;
            *(float*)(this + 0x78) += factorZ;
            // velW (0x7c) is not updated in this branch (only read/written in else?)

            // Now get current velocity for magnitude check
            float vx = *(float*)(this + 0x70);
            float vy = *(float*)(this + 0x74);
            float vz = *(float*)(this + 0x78);

            float magSq = vx*vx + vy*vy + vz*vz;
            float mag = sqrtApprox(magSq); // sqrt (0x414a80)

            // Compare with some threshold: fVar2 = *(float*)(this+0x10) * *(float*)(this+0x84) 
            float threshold = *(float*)(this + 0x10) * dampY; // dampY at +0x84
            if (threshold < mag) {
                // Normalize and set velocity to some target scaled by (g_one - threshold)
                float scale = g_one - threshold;
                *(float*)(this + 0x70) = angDampX * scale;
                *(float*)(this + 0x74) = angDampY * scale;
                *(float*)(this + 0x78) = angDampZ * scale;
                *(float*)(this + 0x7c) = angDampW * scale;
            }

            return 0; // or some value? actually returns uVar1 which is unused? The code returns uVar1 which is the result of magnitude calculation? In this branch, uVar1 is set to sqrt. But the function returns that, so we need to return something. Let's see: uVar1 = FUN_00414a80(...); then it returns uVar1 at the end of this branch (before else). So we return mag (as uint? but sqrt returns float, cast to uint? Possibly returns a uint status? Actually the original returns `uint`, and the sqrt result is cast? It could be that sqrt returns uint (maybe a hash?). Since we don't know, we'll return 0 for now. But the decompiled return uVar1 after the if block, so we should return something. I'll return the uint of the magnitude cast? Probably not. Better to return 0 as placeholder. However, the function is called and the return value may be used as a flag. In the else branch, it calls FUN_00550b80 which returns a uint, and returns that if true. So we should keep the return value as uint.

            // In the original, after the if block, it returns uVar1 (the sqrt result). So:
            return *(uint32_t*)&mag; // reinterpret cast? That's weird. Alternatively, the sqrt function might return an integer. Let's assume sqrtApprox returns float and we return reinterpreted bits? Not good. We'll return 0 for now, but need to match original.

            // Actually from the decompiled code: after the if block, it returns uVar1 which is the result of sqrt. So we must return that. So:
            // uint32_t magInt = *(uint32_t*)&mag; // but that's implementation-defined. Better to keep as float and return via union.
        } else {
            // Inactive: copy target velocity (from +0x50) to current velocity (+0x70)
            *(float*)(this + 0x70) = *(float*)(this + 0x50);
            *(float*)(this + 0x74) = *(float*)(this + 0x54);
            *(float*)(this + 0x78) = *(float*)(this + 0x58);
            *(float*)(this + 0x7c) = *(float*)(this + 0x5c);

            uint32_t flags = *(uint32_t*)(this + 0xe4);
            // Check bit1 (0x2) -> if set, skip further processing
            if ((flags & 0x2) == 0) {
                // Check bit5 (0x20) or modulus condition
                if ((flags & 0x20) != 0 ||
                    (g_frameCounter / *(uint32_t*)(this + 0xb8) == 0)) {
                    // Call external function (maybe environment check)
                    if (checkCollisionOrSomething()) {
                        // Compute current velocity magnitude
                        float vx = *(float*)(this + 0x70);
                        float vy = *(float*)(this + 0x74);
                        float vz = *(float*)(this + 0x78);
                        float magSq = vx*vx + vy*vy + vz*vz;
                        float mag = sqrtApprox(magSq);
                        if (mag < g_smallThreshold) {
                            // Scale target velocity
                            float scale = dampY * g_speedScale; // dampY from +0x84, but note: in decomp, it used *(this+0x84) which is dampY? Actually fVar2 = *(float *)(unaff_ESI + 0x84) * DAT_00e44868;
                            *(float*)(this + 0x70) = angDampX * scale;
                            *(float*)(this + 0x74) = angDampY * scale;
                            *(float*)(this + 0x78) = angDampZ * scale;
                            *(float*)(this + 0x7c) = angDampW * scale;
                        }
                        *(uint32_t*)(this + 0xe4) |= 0x20; // Set bit 5
                        return 1; // Return true from external call
                    } else {
                        *(uint32_t*)(this + 0xe4) &= ~0x20; // Clear bit 5
                        return 0;
                    }
                }
            }
        }
        return 0; // Fallback
    }
};