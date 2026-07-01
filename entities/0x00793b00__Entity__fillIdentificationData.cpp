// FUNC_NAME: Entity::fillIdentificationData
void __thiscall Entity::fillIdentificationData(IdentificationData* outData)
{
    uint32_t localBuf[3]; // Stack buffer for virtual function output
    // Call virtual function at vtable+0x104 to fill first and third fields
    (*(void (__thiscall*)(Entity*, uint32_t*))(*this + 0x104))(this, localBuf);
    outData->field0 = localBuf[0];          // +0x00 from virtual call
    outData->field1 = *(uint32_t*)(FUN_00471610() + 0x34); // From global manager +0x34
    outData->field2 = localBuf[2];          // +0x08 from virtual call
}