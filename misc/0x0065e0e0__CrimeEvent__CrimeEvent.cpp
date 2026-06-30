// FUNC_NAME: CrimeEvent::CrimeEvent
void __fastcall CrimeEvent::CrimeEvent(CrimeEvent* this, SomeStruct* sourceInfo)
{
    // Initialize vtable pointer
    this->vtable = &PTR_LAB_00e42d64;
    // Zero out fields at offsets +4 and +8
    this->field_4 = 0;
    this->field_8 = 0;
    // Copy fields from sourceInfo (offsets 0x0C and 0x10)
    this->field_C = *(int*)(sourceInfo + 0x0C);
    this->field_10 = *(int*)(sourceInfo + 0x10);
    // Set flag byte at offset 0x14 (20) to 0
    *(char*)((int)this + 0x14) = 0;
}