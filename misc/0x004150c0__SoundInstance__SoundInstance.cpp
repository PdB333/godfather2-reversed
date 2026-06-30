// FUNC_NAME: SoundInstance::SoundInstance
SoundInstance * __thiscall SoundInstance::SoundInstance(SoundInstance *this, int param_2, uint64_t *guid, int param_4, int unknownData, int *refCountedPtr)
{
    int *refObj;

    FUN_004a7770(param_2, param_4);
    this->vtable = (void **)0x00e2f720;
    *(uint64_t *)(&this->field_4) = guid[0];    // +0x04: first 8 bytes of GUID
    *(uint64_t *)(&this->field_0xC) = guid[1];  // +0x0C: second 8 bytes of GUID
    this->field_0x14 = 0;                       // +0x14: zeroed word
    refObj = *refCountedPtr;                    // +0x18: pointer to ref-counted object
    this->refCounted = refObj;
    if (refObj != (int *)0x0) {
        // Increment reference count (at offset +4 of the referenced object)
        *(int *)(refObj + 1) = *(int *)(refObj + 1) + 1;
    }
    this->field_0x1C = unknownData;             // +0x1C: copy of unknownData
    this->field_0x20 = unknownData;             // +0x20: second copy of unknownData
    *(uint8_t *)(&this->field_0x24) = 0;        // +0x24: byte flag (0)
    *(uint8_t *)&this->field_0x25 = 1;          // +0x25: byte flag (1)
    *(uint8_t *)&this->field_0x26 = 0;          // +0x26: byte flag (0)
    return this;
}