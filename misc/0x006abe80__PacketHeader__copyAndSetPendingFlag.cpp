// FUNC_NAME: PacketHeader::copyAndSetPendingFlag
void __thiscall PacketHeader::copyAndSetPendingFlag(PacketHeader* other)
{
    // Copy all 12 DWORD fields (48 bytes)
    this->field0 = other->field0;
    this->field1 = other->field1;
    this->field2 = other->field2;
    this->field3 = other->field3;
    this->field4 = other->field4;
    this->field5 = other->field5;
    this->field6 = other->field6;
    this->field7 = other->field7;
    this->field8 = other->field8;
    this->field9 = other->field9;

    // Set bit 0 of field7 (presumably a "pending" or "dirty" flag)
    this->field7 |= 1;

    // Copy the remaining two fields
    this->field10 = other->field10;
    this->field11 = other->field11;
}