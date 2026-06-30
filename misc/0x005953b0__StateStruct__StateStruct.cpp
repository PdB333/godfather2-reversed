// FUNC_NAME: StateStruct::StateStruct

struct StateStruct {
    int flags;          // +0x00
    short field_4;      // +0x04
    short field_6;      // +0x06
    short type;         // +0x08, initialized to 4 (possibly enum or version)
    short field_10;     // +0x0A
    int data;           // +0x0C
};

void __fastcall StateStruct::StateStruct(StateStruct* this)
{
    this->flags = 0;
    this->field_4 = 0;
    this->field_6 = 0;
    this->data = 0;
    this->type = 4;
    this->field_10 = 0;
}