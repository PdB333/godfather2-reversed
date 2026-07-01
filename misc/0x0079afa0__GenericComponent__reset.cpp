// FUNC_NAME: GenericComponent::reset
void __fastcall GenericComponent::reset(GenericComponent* this)
{
    // Set field at offset +0x04 to 0
    this->field_4 = 0;
    // External cleanup routine using the original value of the first field (offset +0x00)
    FUN_009c8f10(this->field_0);
    // Zero out first field (offset +0x00) and third field (offset +0x08)
    this->field_0 = 0;
    this->field_8 = 0;
}