// FUNC_NAME: PlayerAimStateMachine::updateAiming
#include <cmath>

class PlayerAimStateMachine {
public:
    // +0x10: unknown parameter (e.g., float)
    // +0x14, +0x18, +0x1c: position (x, y, z) of something (e.g., last aim target)
    // +0x520: flag indicating aiming is active (0 = not aiming, 1 = aiming)
    // +0x524: current stance? (0 = standing, 0x48 = crouching)
    // +0x68c: last stance? (same enum)
    // +0x694: aiming mode? (0 = hip, 0x48 = iron sight?)
    // +0x69c: current animation frame counter? (for timing)
    // +0x6a0: max animation frame? (threshold)
    // +0x6a4: some condition variable (non-zero means something)
    // +0x6b8: lock-on flag (0 = free aim, 1 = locked)
    // +0x6c0: ... (not used)

    // External globals (from other modules)
    float _DAT_00d5d798; // squared distance threshold for re-aiming
    int* DAT_0112a53c;   // some global pointer, e.g., debug system
    // Method: get camera info (returns bool)
    bool getCameraInfo(void* out, int param);
    // Method: get aim target from camera info (returns bool)
    bool getAimTarget(void* cameraInfo, float* outTarget);
    // Method: start aiming sequence
    void startAiming();
    // Method: update aiming direction
    void updateAimDirection();
    // Method: set aiming mode (0 = start, 1 = stop?)
    void setAimMode(int mode);
    // Method: set current stance
    void setStance(int newStance);
    // Method: something related to animation
    void doSomething();
    // Method: format debug string
    void formatDebugString(char* out);
    // Method: send debug info to UI
    void sendDebugInfo(int* counter, const char* debugStr, int id, float* aimTarget, int param);
};

void __thiscall PlayerAimStateMachine::updateAiming() {
    int* animationCounter = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x6a0);
    if (*(int*)(reinterpret_cast<uintptr_t>(this) + 0x69c) <= *animationCounter) {
        return; // animation not yet complete
    }

    // Get camera info and aim target
    char cameraInfo[24]; // size from usage (local_3c, but actual size unknown)
    if (!getCameraInfo(&cameraInfo, 0)) {
        return;
    }

    float aimTarget[3]; // local_30, fStack_2c, local_28 -> x,y,z?
    if (!getAimTarget(&cameraInfo, aimTarget)) {
        return;
    }

    int currentAimMode = *(int*)(reinterpret_cast<uintptr_t>(this) + 0x694);
    // If not in hip mode and not in iron-sight mode, skip aiming update?
    if (currentAimMode == 0 || currentAimMode == 0x48) {
        int isAiming = *(int*)(reinterpret_cast<uintptr_t>(this) + 0x520);
        if (isAiming == 0) {
            // Not currently aiming
            if ((*(int*)(reinterpret_cast<uintptr_t>(this) + 0x6b8) == 0) &&
                (*(int*)(reinterpret_cast<uintptr_t>(this) + 0x6a4) != 0)) {
                // Condition to automatically start aiming (e.g., near a target)
                startAiming();
                if (*(int*)(reinterpret_cast<uintptr_t>(this) + 0x520) != 0) {
                    // Aiming was started, recurse to process again
                    updateAiming();
                    return;
                }
            }
            updateAimDirection();
            // Check if last stance differs from current stance
            int lastStance = *(int*)(reinterpret_cast<uintptr_t>(this) + 0x68c);
            if (lastStance != 0 && lastStance != 0x48) {
                int currentStance = *(int*)(reinterpret_cast<uintptr_t>(this) + 0x524);
                if (currentStance != lastStance) {
                    if (currentStance != 0 && currentStance != 0x48) {
                        setAimMode(0); // stop aiming?
                    }
                    setStance(reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x68c));
                    if (*(int*)(reinterpret_cast<uintptr_t>(this) + 0x524) == 0) {
                        setAimMode(1); // start aiming?
                    } else {
                        setAimMode(1);
                    }
                }
            }
            goto LAB_006a6909;
        } else {
            // Already aiming
            if ((*(int*)(reinterpret_cast<uintptr_t>(this) + 0x6b8) == 0) &&
                (*(int*)(reinterpret_cast<uintptr_t>(this) + 0x6a4) != 0)) {
                startAiming();
            }
            updateAimDirection();

            // Compute distance squared to current aim target
            float dx = aimTarget[2] - *(float*)(reinterpret_cast<uintptr_t>(this) + 0x1c);
            float dy = aimTarget[1] - *(float*)(reinterpret_cast<uintptr_t>(this) + 0x18);
            float dz = aimTarget[0] - *(float*)(reinterpret_cast<uintptr_t>(this) + 0x14);
            float distSq = dx*dx + dy*dy + dz*dz;
            if (distSq <= _DAT_00d5d798) goto LAB_006a6909;

            // Update target position
            *(uint64_t*)(reinterpret_cast<uintptr_t>(this) + 0x14) = 
                (static_cast<uint64_t>(*reinterpret_cast<uint32_t*>(&aimTarget[1])) << 32) |
                *reinterpret_cast<uint32_t*>(&aimTarget[0]);
            *(float*)(reinterpret_cast<uintptr_t>(this) + 0x1c) = aimTarget[2];
        }
    }

    doSomething();

LAB_006a6909:
    // Possibly send debug/HUD info
    int currentStance = *(int*)(reinterpret_cast<uintptr_t>(this) + 0x524);
    if (currentStance != 0 && currentStance != 0x48) {
        char debugString[32];
        formatDebugString(debugString);
        int id = *(int*)(DAT_0112a53c + 0x70); // some identifier
        sendDebugInfo(animationCounter, debugString, id, aimTarget, *(int*)(reinterpret_cast<uintptr_t>(this) + 0x10));
    }
    return;
}