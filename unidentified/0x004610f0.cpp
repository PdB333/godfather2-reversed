// FUNC_004610f0: Entity::updateMotionEvent
void Entity::updateMotionEvent()
{
    sub_471b10(); // generic update, unknown functionality

    // +0x218: pointer to animation state (AnimState)
    AnimState* pAnimState = *(AnimState**)((uint8_t*)this + 0x218);
    AnimSet* pAnimSet = nullptr;
    AnimEntry* pAnimEntry = nullptr;

    if (pAnimState)
    {
        // +0x70: pointer to animation set (AnimSet)
        pAnimSet = *(AnimSet**)((uint8_t*)pAnimState + 0x70);
    }

    if (pAnimSet)
    {
        // +0x18: number of animations in set
        int numAnims = *(int*)((uint8_t*)pAnimSet + 0x18);
        // +0x76: animation index (short)
        short animIndex = *(short*)((uint8_t*)pAnimState + 0x76);
        // Validity checks: array pointer non-null, count>0, index in range
        if (numAnims > 0 && *(int*)((uint8_t*)pAnimSet + 0x1c) != 0 && animIndex >= 0 && animIndex < numAnims)
        {
            // +0x1c: base of anim entry array (each entry 0x18 bytes)
            pAnimEntry = (AnimEntry*)(*(int*)((uint8_t*)pAnimSet + 0x1c) + animIndex * 0x18);
        }
    }

    // +0x264: some motion identifier (or sound/effect ID)
    int motionId = *(int*)((uint8_t*)this + 0x264);
    // +0x104: speed/amplitude from anim state (float)
    float speedValue = pAnimState ? *(float*)((uint8_t*)pAnimState + 0x104) : 0.0f;
    // +0x10: event/payload from the animation entry
    int eventId = pAnimEntry ? *(int*)((uint8_t*)pAnimEntry + 0x10) : 0;

    // === Build event payload on a custom stack (script/event system) ===
    // Global stack pointer at DAT_01206880 + 0x14
    int* stackPtr = (int*)(g_EventStack + 0x14); // address of stack pointer variable
    // Push a vtable pointer (function table for the event handler)
    *(int**)stackPtr = &PTR_LAB_0110b960;
    int* stack = *(int**)stackPtr;

    // First argument: pointer to entity transform at +0x54
    *stack = (int)((uint8_t*)this + 0x54);
    stack++; // advance past first argument

    // Align stack to 4-byte boundary (round up to next multiple of 4)
    int alignedAddr = ((int)stack + 7) & ~3;
    uint64_t* quadSlot = (uint64_t*)alignedAddr;

    // Store combined 64-bit value: lower 32 bits = speedValue, upper = motionId
    *quadSlot = ((uint64_t)motionId << 32) | *(uint32_t*)&speedValue;

    // Store eventId in the following 32-bit slot
    *(uint32_t*)(quadSlot + 1) = eventId;

    // Update stack pointer past the three consumed 32-bit words (transform ptr, quad, eventId)
    stack = (int*)((int)stack + 0xC);

    // Update the global stack pointer
    *(int**)g_EventStack = stack;

    // === Update flags based on whether motion data is zero ===
    // +0x15e: unsigned short flags (bit 0x4000 = some "has motion" flag)
    if (speedValue == 0.0f && motionId == 0)
    {
        *(uint16_t*)((uint8_t*)this + 0x15E) &= ~0x4000; // clear flag
    }
    else
    {
        *(uint16_t*)((uint8_t*)this + 0x15E) |= 0x4000;  // set flag
    }
}