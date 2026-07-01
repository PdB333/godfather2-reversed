// FUNC_NAME: InteractionValidator::tryStartInteraction
// Address: 0x007e0ff0
// Role: Checks if the player is within interaction range of a target entity and triggers the appropriate interaction (combat or dialog) based on target's interaction type flag.

typedef unsigned char undefined1;
typedef int int32;
typedef float float32;

class SimEntity;
// Global functions - likely returning player and current target sim entities
SimEntity* GetSimEntity(); // Returns pointer to current player sim (or similar)
// Functions to initiate interactions on target
bool StartCombat();   // FUN_00704990
bool StartDialog();   // FUN_00704a10
// Global float thresholds
extern float gVerticalDistanceThreshold; // _DAT_00d5780c
extern uint32 gVerticalMask;            // DAT_00e44680

class InteractionValidator {
public:
    // param_1: this pointer (InteractionValidator*)
    // param_2: target SimEntity* (with vtable and fields)
    undefined1 __thiscall tryStartInteraction(SimEntity* target);
};

undefined1 InteractionValidator::tryStartInteraction(SimEntity* target) {
    uint8 result = 0;
    if (target != nullptr) {
        // Virtual method at vtable offset 0x150 (likely IsValidForInteraction)
        // Pass field at this+0x58 as argument (maybe entity ID or context info)
        bool isValid = (**(bool (__thiscall**)(int))(*(uint32*)target + 0x150))(*(int32*)(this + 0x58));
        if (isValid) {
            // Get two sim entities (player and maybe another, e.g., current target)
            SimEntity* entityA = GetSimEntity(); // iVar2
            SimEntity* entityB = GetSimEntity(); // iVar3 (could be different due to global state)
            
            // Entity positions: offset 0x30 = x, 0x34 = y, 0x38 = z
            float dz = *(float32*)(entityB + 0x38) - *(float32*)(entityA + 0x38);
            float dx = *(float32*)(entityB + 0x30) - *(float32*)(entityA + 0x30);
            // Compute horizontal distance
            float horizontalDist = sqrt(dz * dz + dx * dx);
            
            // Check horizontal distance against target's range (offset 0x6c as float, i.e., param_2[0x6c] in int indexing = byte offset 0x1B0)
            float range = *(float32*)(target + 0x6c); // Actually param_2[0x6c] would be at offset 0x1B0, but here using byte offset directly
            // The decompiler used param_2[0x6c] which as int* index is wrong; correct byte offset is 0x6c. We'll assume 0x6c is the actual byte offset of range.
            // Actually param_2 is int* in decompiled, so param_2[0x6c] means offset 0x6c * 4 = 0x1B0. That's likely a float field. We'll use byte offset 0x1B0.
            // But to match the decompiled code, we'll keep the index as int* but adjust in comment.
            
            float targetRange = *(float32*)((int*)target + 0x6c); // confusing, but effectively offset 0x1B0 in bytes? I'll assume the struct uses 4-byte aligned fields, so offset 0x6c in bytes is actual. Many games store range as float at offset 0x6c.
            // Given uncertainty, I'll just use offset 0x6c as the actual float field.
            
            float dy = *(float32*)(entityB + 0x34) - *(float32*)(entityA + 0x34);
            uint32 dyBits = *(uint32*)&dy; // reinterpret as uint
            uint32 maskedDy = dyBits & gVerticalMask;
            float absVerticalDist = *(float32*)&maskedDy; // reinterpret back as float (this trick gives absolute value if mask isolates sign)
            
            if (horizontalDist < targetRange && absVerticalDist < gVerticalDistanceThreshold) {
                // Interaction type flag at offset 0x6a from target (int, byte offset 0x1A8)
                int interactionType = *(int32*)((int*)target + 0x6a); // offset 0x1A8
                bool success = false;
                if (interactionType == 0) {
                    success = StartCombat(); // FUN_00704990
                } else if (interactionType == 1) {
                    success = StartDialog(); // FUN_00704a10
                } else {
                    return 0;
                }
                if (success) {
                    result = 1;
                }
            }
        }
    }
    return result;
}