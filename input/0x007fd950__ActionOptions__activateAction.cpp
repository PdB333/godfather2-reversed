// FUNC_NAME: ActionOptions::activateAction

// Reconstructed from 0x007fd950 - Sets up an action effect (e.g., shoot/cover/hurt) on entity
// NOTE: This is a member function of some game object (likely associated with action flags and effects)
// Offsets are relative to this pointer (unknown class size ~0x1b90+)

#include <windows.h> // for TlsGetValue

// Forward declarations for known EA EARs/Godfather engine functions
extern void* getIdentityTransform();
extern void setActiveEffect(void* effect);
extern void* allocateMemory(int size, int hint);
extern void* createSoundEffect(const char* soundName);
extern void* createSoundEffectWithPosition(void* effectParams, void* effectParams2, const char* soundName);

// Action IDs (partial guess)
enum ActionId : uint8_t {
    ACTION_NONE = 0,
    ACTION_SHOOT = 9, // triggers extra effect setup
    // ... others unknown
};

// Known sound names (from global data references)
extern const char* const snd_ActionShoot;     // DAT_00d71c38
extern const char* const snd_ActionDefault;   // _DAT_00d5cf70
extern const char* const snd_ActionCover;     // DAT_00d71bc8
extern const char* const snd_ActionHurt;      // DAT_00d5f520
extern const char* const snd_ActionHurt2;     // DAT_00d71bd8

// Effect parameters structure used for positional effects
struct EffectParams {
    float field_00;  // position or time component
    float field_04;
    float field_08;
    float field_0c;
    float field_10;
    float field_14;
    float field_18;
    float field_1c;
};

void __thiscall ActionOptions::activateAction(void* this_ptr, uint8_t actionId, uintptr_t actionData, uint32_t actionFlags)
{
    auto* const obj = (uintptr_t)this_ptr;

    // Set flag at +0x604 for this action
    *(uint32_t*)(obj + 0x604) |= (1 << (actionId & 0x1f));

    // If extra flags provided, OR them into a separate bitfield at +0x60c
    if (actionFlags != 0) {
        *(uint32_t*)(obj + 0x60c) |= actionFlags;
    }

    // Store the action data at +0x1b90
    *(uintptr_t*)(obj + 0x1b90) = actionData;

    // Initialize a transform matrix/vector at +0x8b4 (5 floats)
    uint32_t* transform = (uint32_t*)(obj + 0x8b4);
    transform[0] = 0; // +0x8b4
    transform[1] = 0; // +0x8b8
    transform[2] = 0; // +0x8bc
    transform[3] = 0; // +0x8c0
    transform[4] = 0; // +0x8c4

    // Get an identity transform from engine
    *transform = (uint32_t)getIdentityTransform();

    // Set pointer to this transform at +0x8d4
    *(uint32_t**)(obj + 0x8d4) = transform;
    // Set count/reference at +0x8d8
    *(int*)(obj + 0x8d8) = 1;

    // Only proceed with special effect setup for action 9 (e.g., shoot)
    if (actionId != ACTION_SHOOT) {
        return;
    }

    // Get pointer to target entity from +0x74c
    auto* pTarget = *(uintptr_t*)(obj + 0x74c);
    if (pTarget == 0) goto cleanup;
    if (pTarget == 0x48) goto cleanup; // 0x48 may be sentinel/null type
    auto* pTargetType = *(uintptr_t*)(pTarget + 0x20);
    if (pTargetType == 0 || pTargetType == 0x48) goto cleanup;
    // Check a flag at +0x8e0 bit 10 (maybe "in combat")
    if (!((*(uint32_t*)(obj + 0x8e0) >> 10) & 1)) goto cleanup;

    // Decide effect type based on target state byte at +0x161
    uint32_t targetActionId = *(uint32_t*)(pTarget + 0x1c8) >> 2; // some ID
    int8_t targetState = *(int8_t*)(pTarget + 0x161);
    bool useStaticEffect = true; // if true, use simpler effect (sound only)
    const char* effectSoundName = nullptr;
    const char* effectPositionSound = nullptr; // for positional effect
    const char* extraSound = nullptr;

    switch (targetState) {
        case 1: // e.g., Idle/Standing
            effectSoundName = snd_ActionShoot;
            break;
        case 2: // e.g., Cover
            effectSoundName = snd_ActionDefault;
            useStaticEffect = false;
            extraSound = snd_ActionCover;
            break;
        case 3: // e.g., Hurt1
        case 4: // Hurt2
        {
            int8_t subState = *(int8_t*)(pTarget + 0x163);
            effectPositionSound = (subState != 0) ? snd_ActionHurt2 : snd_ActionHurt;
            effectSoundName = snd_ActionDefault;
            useStaticEffect = false;
            break;
        }
        default:
            goto cleanup; // unknown state -> skip
    }

    // Clear previous active effect if exists
    if (*(uintptr_t*)(obj + 0x1b20) != 0) {
        setActiveEffect(nullptr);
    }

    uint32_t* effectMemory;
    if (useStaticEffect) {
        // Simple static sound effect
        TlsGetValue(*(uint32_t*)0x1139810); // likely thread-local storage for allocator
        effectMemory = (uint32_t*)allocateMemory(0x20, 0x27);
        *(uint16_t*)(effectMemory + 4) = 0x20; // size field?
        void* newEffect = createSoundEffect(effectSoundName);
        effectMemory = (uint32_t*)newEffect; // overwrite? Probably create returns pointer to same block
    } else {
        // Positional effect: fill in EffectParams structure on stack
        EffectParams params = {};
        params.field_00 = 0.0f; // from local_20
        params.field_04 = 0.0f; // from local_1c
        params.field_08 = 0.0f; // from local_18
        params.field_0c = 0.0f; // from local_14
        params.field_10 = 0.0f; // from local_30
        // local_28 is extraSound? Actually local_28 is set to effectPositionSound? 
        // In original, local_28 = local_38 (extraSound from case 2 or local_38 set earlier)
        // local_2c = local_40 (effectPositionSound from hurt)
        // local_30 = local_28 (which is extraSound)
        // We ignore exact layout for brevity; assume EffectParams contains at least:
        // field_00 - field_14 are vectors/times, field_18 = position sound? Actually store extraSound in it.
        // For reconstruction we just pass the two pointers and sound name.
        TlsGetValue(*(uint32_t*)0x1139810);
        effectMemory = (uint32_t*)allocateMemory(0x40, 0x27);
        *(uint16_t*)(effectMemory + 4) = 0x40;
        void* newEffect = createSoundEffectWithPosition(&params.field_00, &params.field_10, effectSoundName);
        effectMemory = (uint32_t*)newEffect;
    }

    setActiveEffect(effectMemory);

    // Decrement reference count on effect object at offset +6 (usually refCount)
    if (*(int16_t*)(effectMemory + 1) != 0) { // note: +1 because uint32_t* pointer arithmetic? Original: *(short *)(puVar5 + 1) means byte offset 4? Let's recheck.
        // Original code: if ((*(short *)(puVar5 + 1) != 0) && (*(short *)((int)puVar5 + 6) = ..., *(short *)((int)puVar5 + 6) == 0))
        // puVar5 is uint32_t*, so puVar5+1 is offset 4. But short is 2 bytes, so at offset 4 and 6.
        // Better: treat effectMemory as byte pointer for clarity.
        int16_t* refCount = (int16_t*)((uint8_t*)effectMemory + 6);
        if (*(int16_t*)((uint8_t*)effectMemory + 4) != 0) { // check something? Actually original checks *(puVar5+1) as short. That is likely a type/size.
            // Decrement
            *refCount -= 1;
            if (*refCount == 0) {
                // Call first vtable entry with argument 1 (destructor?)
                (*(void(__thiscall**)(int32_t))(**(uint32_t**)effectMemory))(1);
            }
        }
    }

    // Compare target action ID with current action IDs from object fields
    uint32_t curActionId1 = *(uint32_t*)(obj + 0x70c) >> 2;
    uint32_t curActionId2 = *(uint32_t*)(obj + 0x710) >> 2; // second current action slot
    // Store self reference
    *(uintptr_t*)(obj + 0x1b6c) = obj;

    if (targetActionId == curActionId1 || targetActionId == curActionId2) {
        // Match found: store the matching current action ID
        *(uint32_t*)(obj + 0x1b70) = targetActionId == curActionId1 ? curActionId1 : curActionId2;
        return;
    }

    // No match: clear effect and flag
    setActiveEffect(nullptr);

cleanup:
    // Clear the action flag at bit 9 (since we were processing action 9)
    *(uint32_t*)(obj + 0x604) &= ~(1 << 9);
    // Clear the stored action data
    *(uintptr_t*)(obj + 0x1b90) = 0;
    return;
}