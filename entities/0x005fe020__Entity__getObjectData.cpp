// FUNC_NAME: Entity::getObjectData
uint __thiscall Entity::getObjectData(void *this, uint32_t *outData)
{
    uint32_t uVar2 = DAT_00e2b1a4; // global constant, maybe alpha or something
    uint32_t uVar3 = in_EAX & 0xffffff00; // preserve upper 24 bits of input
    int32_t iVar4;

    // Field at +0x4c is likely a state/type indicator; 0x48 seems to be a special value
    uint32_t stateOrType = *(uint32_t *)((char *)this + 0x4c);

    if (stateOrType != 0 && stateOrType != 0x48) {
        if (stateOrType == 0) {
            iVar4 = 0;
        } else {
            iVar4 = stateOrType - 0x48;
        }
        // Read three 4-byte values from the structure pointed by iVar4, plus a global
        outData[0] = *(uint32_t *)(iVar4 + 0x100);
        outData[1] = *(uint32_t *)(iVar4 + 0x104);
        outData[2] = *(uint32_t *)(iVar4 + 0x108);
        outData[3] = uVar2;

        // Modify return value: set lowest byte to 1, upper 24 bits come from iVar4>>8
        uVar3 = ((uint32_t)(iVar4 >> 8) & 0xffffff00) | 1;
    }
    // If condition fails, return the original preserved upper bits? (but lower byte might be zero)
    return uVar3;
}