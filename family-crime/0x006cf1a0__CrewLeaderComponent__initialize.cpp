// FUNC_NAME: CrewLeaderComponent::initialize
void __thiscall CrewLeaderComponent::initialize(int this) // this is the component pointer
{
    uint32_t global1 = DAT_00d5f00c; // some global constant/resource
    uint32_t global2 = DAT_00e447a4; // another global constant
    uint32_t global3 = DAT_00d5780c; // shared default value for times
    uint32_t global4 = DAT_00d5f204; // global timer/interval
    uint32_t global5 = DAT_00d5ef94; // global timer/offset

    // Reset state fields at +0xa0..+0xb0
    *(uint32_t*)(this + 0xa0) = 0;              // +0xa0: state timer 0
    *(uint32_t*)(this + 0xa8) = 0;              // +0xa8: state timer 1
    *(uint32_t*)(this + 0xac) = 0;              // +0xac: state timer 2
    *(uint32_t*)(this + 0xa4) = global2;        // +0xa4: cooldown/limit
    *(uint32_t*)(this + 0xb0) = global1;        // +0xb0: duration/rate

    *(uint32_t*)(this + 0xc4) = 2;              // +0xc4: mode (e.g., state enum)

    // Allocate a sub-object: size 0x30, alignment 0x10
    uint32_t* subObj = (uint32_t*)FUN_004eb390(0x30, 0x10); // custom allocator
    if (subObj != nullptr)
    {
        subObj[0] = (uint32_t)&PTR_FUN_00e372b4; // vtable pointer
        subObj[1] = 0;                             // reference count initially 0
        subObj[4] = global3;                       // +0x10: value A (time threshold)
        subObj[5] = global3;                       // +0x14: value B
        subObj[6] = global3;                       // +0x18: value C
        subObj[7] = global3;                       // +0x1c: value D
        subObj[8] = 0;                             // +0x20: some flag
    }
    *(uint32_t*)(this + 0xd8) = (uint32_t)subObj; // +0xd8: pointer to sub-object
    if (subObj != nullptr)
    {
        subObj[1] += 1; // increment reference count (now 1 if allocation succeeded)
    }

    *(uint32_t*)(this + 0xe0) = 0;                 // +0xe0: zero
    *(uint32_t*)(this + 0xe4) = global4;           // +0xe4: interval/delay
    *(uint32_t*)(this + 0xe8) = global5;           // +0xe8: offset
    *(uint32_t*)(this + 0xec) = global3;           // +0xec: default duration

    // Clear 0x98-byte array starting at +0xf0 (likely action/state data)
    _memset((void*)(this + 0xf0), 0, 0x98);

    *(uint8_t*)(this + 0x188) = 0;                 // +0x188: boolean flag (false)
    return;
}