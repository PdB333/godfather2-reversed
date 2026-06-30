// FUNC_NAME: EARSObject::getFields18And1C
void __thiscall EARSObject::getFields18And1C(int* outField1C, int* outField18)
{
    // +0x18: field18
    // +0x1C: field1C
    *outField1C = *(int*)((uint8_t*)this + 0x1C);
    *outField18 = *(int*)((uint8_t*)this + 0x18);
}