// FUNC_NAME: NPC::getModelHash
// Address: 0x00701720
// Returns a hash value for NPC model based on type, subtype, and variant fields.
uint32_t __thiscall NPC::getModelHash(void) const
{
    uint32_t iVar1;
    uint32_t uVar2;

    uVar2 = 0x35048678u; // default hash for unmatched combinations
    switch (*(int *)(this + 0x2D0 + 0x0C)) // +0x2DC: modelType (1-4)
                                            // 0x2D0 is probably base offset, but use actual 0x2DC
    {
    case 1:
        iVar1 = *(uint32_t *)(this + 0x510); // +0x510: subType (character variant)
        if (*(int *)(this + 0x334) == 2)      // +0x334: genderFlag or variantFlag
        {
            if (iVar1 == 2)
                return 0xDAF669BCu;
            if (iVar1 == 3)
                return 0x8C4D2BFBu;
            if (iVar1 == 4)
                return 0x3DA3EE3Au;
        }
        else
        {
            if (iVar1 == 2)
                return 0x59BFB800u;
            if (iVar1 == 3)
                return 0xB167A3Fu;
            if (iVar1 == 4)
                return 0xBC6D3C7Eu;
        }
        break;

    case 2:
        iVar1 = *(uint32_t *)(this + 0x510);
        if (iVar1 == 2)
            return 0x214B0EEEu;
        if (iVar1 == 3)
            return 0xD2A1D12Du;
        if (iVar1 == 4)
            return 0x83F8936Cu;
        break;

    case 3:
        iVar1 = *(uint32_t *)(this + 0x510);
        if (iVar1 == 2)
            return 0x3B3317A9u;
        if (iVar1 == 3)
            return 0xEC89D9E8u;
        if (iVar1 == 4)
            return 0x9DE09C27u;
        break;

    case 4:
        iVar1 = *(uint32_t *)(this + 0x510);
        if (iVar1 == 2)
            return 0x52631AABu;
        if (iVar1 == 3)
            return 0x3B9DCEAu;
        if (iVar1 == 4)
            uVar2 = 0xB5109F29u; // only set, not immediately returned
        break;

    default:
        break;
    }
    return uVar2;
}