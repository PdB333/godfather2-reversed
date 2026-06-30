// FUNC_NAME: SomeClass::sendReliableMessage
void __thiscall SomeClass::sendReliableMessage(uint64_t *param_2, uint32_t param_3, char *param_4, uint32_t param_5, uint64_t *param_6)
{
    char cVar1;
    uint32_t uVar2;
    uint32_t *in_EAX; // Value of EAX at function entry (possibly an implicit parameter)
    uint32_t *piVar3;
    char *pcVar4;
    uint64_t local_18;
    uint64_t local_10;
    uint64_t local_8;
    
    // +0x0c: flag indicating whether this object's ID has been registered
    if (*(char *)(this + 0xc) == '\0') {
        uVar2 = *(uint32_t *)(this + 4); // +0x04: object ID
        // Global pool at DAT_01206880 + 0x14 is a pointer to a write location
        piVar3 = (uint32_t *)(*(uint32_t *)0x01206880 + 0x14);
        // Write a pointer to a static table entry (PTR_LAB_01123d28) then the object ID
        **(uint32_t **)(*(uint32_t *)0x01206880 + 0x14) = &PTR_LAB_01123d28;
        *piVar3 = *piVar3 + 4;
        *(uint32_t *)*piVar3 = uVar2;
        *piVar3 = *piVar3 + 4;
        *(char *)(this + 0xc) = 1; // Mark as registered
    }
    local_10 = 0;
    local_18 = ((uint64_t)param_5 << 32) | param_3; // Combine two 32-bit values into a 64-bit tag
    if (in_EAX == (uint32_t *)0x0) {
        local_8 = 0;
    } else {
        local_8 = ((uint64_t)2 << 32) | *in_EAX; // High 32 bits set to 2, low from EAX
    }
    if (param_6 != (uint64_t *)0x0) {
        local_10 = *param_6; // Optional extra 64-bit data
        local_8 = local_8 | 0x100000000; // Set a flag bit in high 32 bits
    }
    if (param_4 == (char *)0x0) {
        pcVar4 = (char *)0x0; // No string length if null
    } else {
        pcVar4 = param_4;
        do {
            cVar1 = *pcVar4;
            pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        pcVar4 = pcVar4 + (1 - (int)(param_4 + 1)); // Compute string length (simplified)
    }
    // Call underlying function to actually send/queue the message
    FUN_0048cee0(*(uint32_t *)(this + 4),   // object ID
                 *(uint32_t *)(this + 8),   // +0x08: another ID (e.g., connection type)
                 *param_2,                  // first 64-bit word from param_2
                 local_18,                  // constructed tag
                 local_10,                  // optional extra (or 0)
                 local_8,                  // tag from EAX + optional flag
                 param_4,                   // payload string
                 pcVar4,                    // string length
                 1);                        // boolean (likely "send now" flag)
    return;
}