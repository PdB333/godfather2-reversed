// FUNC_NAME: Attitude::initializeFromEntityData
void __thiscall Attitude::initializeFromEntityData(Attitude *this, EntityDataProvider *data)
{
    int iVar1;
    uint uVar2;
    char *sourceStr;
    undefined8 uVar3;
    size_t maxLen;
    
    if (data != (EntityDataProvider *)0x0) {
        uVar2 = data->vtable->getSomeValue(data);  // vtable+0x50
        FUN_0095fb30(uVar2);  // unknown helper
        maxLen = 0x30;
        sourceStr = data->vtable->getName(data);  // vtable+0x18
        _strncpy(&this->name[0], sourceStr, maxLen);  // +0x9c, char[0x30]
        this->name[0x2f] = '\0';  // +0xcb, null-terminate
        this->field_0x88 = 0;  // +0x88
        if (this->useSavedData == '\0') {  // +0x4c
            if ((*(uint *)(DAT_01129930 + 0x6f4) >> 0xc & 1) == 0) {
                if (*(int *)(DAT_0112b9b4 + 0x34) != -1) {
                    iVar1 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4);
                    this->field_0x7c = *(undefined4 *)(iVar1 + 0x2c);  // +0x7c
                    this->field_0x80 = *(undefined4 *)(iVar1 + 0x34);  // +0x80
                }
            }
        }
        else {
            this->field_0x98 = this->field_0x48;  // +0x48 -> +0x98
            this->field_0x84 = this->field_0x40;  // +0x40 -> +0x84
            this->field_0x88 = this->field_0x44;  // +0x44 -> +0x88
            this->field_0x94 = this->field_0x38;  // +0x38 -> +0x94
        }
        uVar2 = data->vtable->getSomeInt(data, 0);  // vtable+0x24
        this->field_0xdc = uVar2;
        this->field_0xe0 = 2;
        uVar2 = data->vtable->getAnotherInt(data, 0);  // vtable+0x20
        this->field_0xe4 = uVar2;
        uVar2 = data->vtable->getFloatValue(data);  // vtable+0x40
        this->field_0xe8 = uVar2;
        uVar3 = data->vtable->getDoubleValue(data);  // vtable+0x3c
        *(undefined8 *)&this->field_0xf0 = uVar3;  // +0xf0 (8 bytes)
        uVar2 = data->vtable->getAnother(data);  // vtable+0x10
        this->field_0x100 = uVar2;
        uVar2 = data->vtable->getOneMore(data);  // vtable+0xc
        this->field_0xfc = uVar2;
    }
    return;
}