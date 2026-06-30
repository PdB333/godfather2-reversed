// FUNC_NAME: GameObject::initDefaults
void GameObject::initDefaults() {
    // Initialize vtable pointer to static table
    this->vtable = (void*)&PTR_LAB_00e35c24; // +0x00

    // Load default field values from global constants
    this->field0x04 = DAT_01124734; // +0x04
    this->field0x08 = DAT_01124738; // +0x08
    this->field0x0c = DAT_0112473c; // +0x0c
    this->field0x10 = DAT_01124740; // +0x10
    this->field0x14 = DAT_01124744; // +0x14
    this->field0x18 = DAT_01124748; // +0x18
    this->field0x1c = DAT_0112474c; // +0x1c
}