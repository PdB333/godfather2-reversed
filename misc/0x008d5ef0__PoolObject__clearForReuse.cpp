// FUNC_NAME: PoolObject::clearForReuse
void __fastcall PoolObject::clearForReuse(PoolObject* this)
{
    this->field_0x00 = 0; // +0x00: first usage flag
    this->field_0x04 = 0; // +0x04: second state field
    this->field_0x0C = 0; // +0x0C: fourth field (offset +0x08 is deliberately left untouched)
}