// FUNC_NAME: GameObject::initFromReplication
void GameObject::initFromReplication(void)
{
    undefined4 uVar1;
    undefined4 uVar2;
    bool bCanInit;
    int iResourceHandle;
    undefined4 uSomeValue;
    void *thisPtr;
    int globalState;
    undefined4 local_64[2]; // Actually local_1c and local_14 combined
    undefined2 local_10;
    undefined2 local_e;
    undefined4 local_c;

    callBaseConstructor();
    this->vtable = &PTR_FUN_00e380f8; // Set vtable for this class
    this->field_0x28 = 0; // +0xA0? Actually offset 0x28 * 4 = 0xA0, but likely a byte offset?
    this->field_0x29 = 0; // +0xA4
    if (*(byte *)(globalState + 0xd) != 0) {
        return;
    }
    bCanInit = checkInitializationFlag();
    if (!bCanInit) {
        *(byte *)(globalState + 0xc) = 1;
        return;
    }
    switch (this->stateByte_at_0x5b) {
        case 1:
            iResourceHandle = loadAnimation();
            break;
        case 2:
            iResourceHandle = loadModel();
            break;
        case 6:
            if ((*(uint *)(this->ptr9 + 0x104) & 0x400) != 0) {
                uSomeValue = getSomeValue();
                this->field_0x19 = uSomeValue; // +0x64
            } else {
                this->field_0x19 = 0;
            }
            goto endSwitch;
        default:
            goto endSwitch;
    }
    if (iResourceHandle != 0) {
        this->field_0x18 = iResourceHandle; // +0x60
    }
endSwitch:
    this->field_0x1a = 0; // +0x68
    this->field_0x1b = 0; // +0x6c
    uVar1 = *(undefined4 *)(this->ptr1 + 0x10); // ptr1 at +0x04, deref +0x10
    uVar2 = this->ptr10; // +0x28
    local_10 = *(undefined2 *)(this + 0x5c); // +0x5c
    local_e = *(undefined2 *)(this + 0x58); // +0x58
    local_c = CONCAT31(local_c._1_3_, this->stateByte_at_0x5b);
    buildMessagePayload(&local_64[0], (int)&local_64[0] + 4, &local_64[1]);
    sendReplicationMessage(this, CONCAT44(this->ptr9, uVar1), CONCAT44(local_64[0], uVar2),
                           local_64[0], CONCAT26(local_e, CONCAT24(local_10, local_64[1])), local_c,
                           this->field_0x10, this->field_0x14);
    return;
}