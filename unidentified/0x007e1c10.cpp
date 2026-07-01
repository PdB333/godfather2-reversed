// FUN_NAME: Player::tryInteractWithObject

typedef void (__thiscall* GetValueFunc)(void* this, void* dest, void* src); // offset 0xa4
typedef void (__thiscall* ProcessFunc)(void* this, void* param, void* arg2); // offset 0x1ec

float __cdecl VectorLengthSquared2D(float2* outVec); // FUN_004702b0 - computes |outVec|^2 and returns it
bool __cdecl CheckInteractionAvailability(Player* player, uint32_t interactionId); // FUN_007f80e0
uint32_t __cdecl GetSomeID(); // FUN_0054eb10
void __cdecl StartAudioEvent(uint32_t eventId, uint32_t param1, uint32_t param2, uint32_t param3); // FUN_00540bc0
void __cdecl DoSomething(); // FUN_00471610
void __cdecl StopAudioEvent(uint32_t handle); // FUN_00540cc0
void __cdecl BuildInteractionData(void* buffer, void* input); // FUN_009e69d0

// Global constant – might be a sentinel (e.g., 0xFFFFFFFF or 0x00000000)
extern uint32_t _DAT_00d5780c; // +0x00d5780c

bool __thiscall Player::tryInteractWithObject(Player* this, Entity* target, float radiusThreshold, uint32_t interactionId)
{
    // vtable calls
    GetValueFunc getValue = (GetValueFunc)(*(uint32_t**)this)[0xa4]; // offset 0xa4
    ProcessFunc process = (ProcessFunc)(*(uint32_t**)this)[0x1ec];   // offset 0x1ec

    // Local buffers
    float local_posComp[1];   // 4 bytes – stores a component from target (e.g., position offset)
    float2 vecDiff;           // 8 bytes – difference vector
    uint32_t audioHandle;     // 4 bytes

    // Fetch some value from target: (param_2 + 4) is probably a 3D vector's X component
    getValue(this, local_posComp, (char*)target + 4);

    // Compute squared length of some vector (stored in vecDiff, likely set by VectorLengthSquared2D)
    float distSq = VectorLengthSquared2D(&vecDiff);

    // Compare against provided threshold squared
    if (distSq <= radiusThreshold * radiusThreshold)
    {
        // Check if the player can interact with this target (line of sight, etc.)
        if (CheckInteractionAvailability(this, interactionId))
        {
            // Retrieve an identifier for audio/event
            uint32_t someId = GetSomeID();

            // Start a specific audio event (0x40102 is likely a dialogue or interaction sound)
            StartAudioEvent(0x40102, someId, 0, 0);

            // Execute an engine routine (maybe notify other systems)
            DoSomething();

            // Stop the same audio event immediately?
            StopAudioEvent(&audioHandle);

            // Now call the virtual process function with the target entity and a stack buffer
            // This likely sets up an interaction state machine
            process(this, (char*)target + 0x????); // Note: second arg is missing in Ghidra? Actually it's param_2 and &stack0xffffff24 – but stack address may be an output struct.

            // Second virtual call: copy something from the target into a local structure
            getValue(this, &stack_buffer, &another_buffer); // approximate

            // Prepare an interaction descriptor on the stack
            InteractionDescriptor desc;
            desc.field_0 = _DAT_00d578c; // known constant
            desc.field_4 = 0xFFFFFFFF;   // -1
            desc.field_8 = 0xFFFFFFFF;   // -1
            desc.field_c = 0;            // 0
            InteractionResult* result = nullptr;

            // Build the interaction data (fills 'result' if successful)
            BuildInteractionData(&desc, someInput);

            // Validate the result – if result is null or its type is not 0xB (11), return success (1)
            if (result == nullptr || *(uint32_t*)(result->vtable + 0xc) != 0xB)
            {
                return true;
            }
        }
    }
    return false;
}