// FUNC_NAME: SmallData::operator=
void __fastcall SmallData::operator=(SmallData* this, SmallData* other) // 0x004ddc00
{
    // Self-assignment check
    if (this != other)
    {
        // Copy fields, offsets based on decompiled output
        // +0x00: field0 (dword)
        // +0x04: field1 (dword)
        // +0x08: field2 (dword)
        // +0x0C: field3 (short)
        this->field0 = other->field0;            // *in_EAX = *param_1
        this->field1 = other->field1;            // in_EAX[1] = param_1[1]
        *(short*)((int)this + 0x0C) = *(short*)((int)other + 0x0C); // *(short*)(in_EAX+3)=*(short*)(param_1+3)
        this->field2 = other->field2;            // in_EAX[2] = param_1[2]
    }
}