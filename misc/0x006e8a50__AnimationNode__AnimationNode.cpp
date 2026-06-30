// FUNC_NAME: AnimationNode::AnimationNode
// Function address: 0x006e8a50
// Role: Constructor for an animation node that processes a stream of commands (actions) to set up initial transform state, rotation, and optionally a script callback.

#include <cstdint>

// Forward declarations (assuming these are defined elsewhere)
extern float DAT_00e44730;    // Default rotation parameter? (e.g., axis or angle)
extern float DAT_00d5eee4;    // Default rotation angle?
extern float DAT_00d5f540;    // Default speed/multiplier
extern float DAT_00d5ca18;    // Y offset constant (gravity?)
extern float DAT_00d5fb68;    // Another Y offset constant

// Known functions (reconstructed signatures)
float* __stdcall FUN_009c8e50(uint32_t size);                     // Allocator
void* __thiscall FUN_006e8950(void);                              // Initialize sub-object (returns pointer)
void __fastcall FUN_006e5d30(float value);                        // Set rotation axis?
void __fastcall FUN_006e5d60(float value);                        // Set scale?
void __thiscall FUN_006e5d90(float a, float b);                   // Apply rotation (axis, angle?)
void __fastcall FUN_004a36a0(char* dst);                          // String copy (to local buffer)
void __thiscall FUN_006e86c0(char* stackBuf);                     // Parse or process command string
void __thiscall FUN_006e5b40(char* stackBuf);                     // Execute command string

// Command data structure: each command has a value at offset 0 and a type at offset 0x10 (as float).
struct Command {
    float value;       // +0x00
    float unk1;        // +0x04
    float unk2;        // +0x08
    float unk3;        // +0x0C
    float type;        // +0x10
};

// Data source (provides command list)
struct CommandList {
    Command** commands; // +0x1C (pointer to array of Command*)
    uint16_t count;     // +0x20 (number of commands)
    // ... other fields
};

// Context for callbacks
struct ContextBase {
    int** vtable;       // +0x00
    // ... vtable at +0x08 is used for a specific callback
};

// Sub-object (target of animation commands) – size 0x8C
struct AnimationTarget {
    // offsets relative to pointer returned by FUN_006e8950
    float posX;         // +0x20
    float posY;         // +0x24
    float posZ;         // +0x28
    // ... other fields ...
    float targetPosX;   // +0x44
    float targetPosY;   // +0x48
    float targetPosZ;   // +0x4C
    // ... intermediate results ...
    float resultPosX;   // +0x68
    float resultPosY;   // +0x6C
    float resultPosZ;   // +0x70
    float extraPosX;    // +0x74 (only when flag == 8)
    float extraPosY;    // +0x78
    float extraPosZ;    // +0x7C
    uint8_t flags;      // +0x88 (bitmask: bit0=1 -> no motion? bit2=4 -> subtract? bit3=8 -> extra offset)
    uint8_t flags2;     // +0x8A (bit3 set after calculation)
    // ... ensures total size >= 0x8C
};

class AnimationNode {
public:
    // Constructor expects a command list and a context for optional script call.
    void* vtable;                 // +0x00
    CommandList* data;            // +0x04
    ContextBase* context;         // +0x08
    AnimationTarget* target;      // +0x0C

    // Constructor
    AnimationNode(CommandList* pData, ContextBase* pContext);
};

// Constructor implementation
AnimationNode::AnimationNode(CommandList* pData, ContextBase* pContext)
{
    // Store parameters
    this->data = pData;
    this->context = pContext;
    this->vtable = (void*)&PTR_FUN_00d5fb78;   // Set vtable (global symbol assumed)
    this->target = nullptr;

    // Allocate and initialize the animation target sub-object
    uint32_t allocSize = 0x8C;
    this->target = static_cast<AnimationTarget*>(FUN_009c8e50(allocSize));
    if (this->target != nullptr) {
        // Initialize target's default state
        this->target = static_cast<AnimationTarget*>(FUN_006e8950());
    }

    // Accumulators for rotation and scale parameters
    float rotationAxis = DAT_00d5eee4;   // Default rotation axis/index
    float rotationAngle = DAT_00e44730;  // Default rotation angle/amount
    float speed = DAT_00d5f540;          // Default speed/multiplier

    // Process command stream if there are any commands
    if (pData->count != 0) {
        for (uint32_t i = 0; i < pData->count; i++) {
            Command* cmd = pData->commands[i];
            float cmdType = cmd->type;   // Command identifier as float
            float cmdValue = cmd->value; // Parameter

            // Categorize commands by comparing the type float to a large threshold
            if (cmdType < 0xB02940B3f) {
                // First group: rotation and position commands
                if (cmdType == -6.157378e-10f) {
                    // Set rotation axis
                    rotationAxis = cmdValue;
                }
                else if (cmdType == 9.000423e-10f) {
                    // Set rotation angle
                    FUN_006e5d30(cmdValue);
                }
                else if (cmdType == 1.804863e+22f) {
                    // Set position
                    rotationAngle = cmdValue;
                }
                else if (cmdType == 4.7095128e+26f) {
                    // Set scale
                    FUN_006e5d60(cmdValue);
                }
            }
            else {
                // Second group: flags and script commands
                if (cmdType == -1.48274e-06f) {
                    // Set a flag on the target based on value's low byte
                    uint8_t bit = static_cast<uint8_t>(cmdValue) & 0x1F;
                    this->target->flags |= (1 << bit);
                }
                else if (cmdType == -1.4321715e+13f) {
                    // Script callback: copy a string from context, call virtual, then process
                    char strBuffer[64];                         // local_90
                    char stackBuffer[76];                       // auStack_50
                    FUN_004a36a0(strBuffer);                     // likely copies a string from somewhere
                    // Call context's virtual function (vtable at +8, method at +4)
                    int** ctxVtable = *reinterpret_cast<int**>(this->context);
                    void (*callback)() = reinterpret_cast<void(*)()>(ctxVtable[2]); // vtable index 2 (offset 8)
                    callback();
                    // Parse and execute the script string
                    FUN_006e86c0(stackBuffer);
                    FUN_006e5b40(stackBuffer);
                }
                else if (cmdType == -3.5940283e+17f) {
                    // Set speed/multiplier
                    speed = cmdValue;
                }
            }
        }
    }

    // Apply accumulated rotation (axis and angle)
    FUN_006e5d90(rotationAxis, rotationAngle);

    // Now compute the final displacement based on the target's current position and the speed.
    float deltaX = this->target->posX * speed;
    float deltaY = this->target->posY * speed;
    float deltaZ = this->target->posZ * speed;

    // Check a flag that modifies the operation
    if ((this->target->flags & 1) == 0) {
        // Normal case: add or subtract the delta based on flag bit 2 (value 4)
        if (this->target->flags == 4) {
            // Subtract delta from target position
            this->target->resultPosX = this->target->targetPosX - deltaX;
            this->target->resultPosY = this->target->targetPosY - deltaY;
            this->target->resultPosZ = this->target->targetPosZ - deltaZ;
        }
        else {
            // Add delta to target position
            this->target->resultPosX = this->target->targetPosX + deltaX;
            this->target->resultPosY = this->target->targetPosY + deltaY;
            this->target->resultPosZ = this->target->targetPosZ + deltaZ;

            // If flag has bit 3 (value 8), also set an extra offset
            if (this->target->flags == 8) {
                this->target->extraPosX = this->target->targetPosX + deltaX;
                this->target->extraPosY = this->target->targetPosY + deltaY;
                this->target->extraPosZ = this->target->targetPosZ + deltaZ;
            }
        }
        // Apply a constant Y offset (e.g., gravity or base height)
        this->target->resultPosY += DAT_00d5ca18;
    }
    else {
        // Flag bit 0 is set: no motion, just copy target position to result
        this->target->resultPosX = this->target->targetPosX;
        this->target->resultPosY = this->target->targetPosY + DAT_00d5fb68; // different constant
        this->target->resultPosZ = this->target->targetPosZ;
        // Also set extra to same position
        this->target->extraPosX = this->target->targetPosX;
        this->target->extraPosY = this->target->targetPosY;
        this->target->extraPosZ = this->target->targetPosZ;
    }

    // Mark that the position has been calculated (bit 3)
    this->target->flags2 |= 8;

    // Return this pointer (optional, in decompiled code it returns param_1)
    // No need to return explicitly as constructor returns implicitly.
}