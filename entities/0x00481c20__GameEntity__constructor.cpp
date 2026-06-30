// FUNC_NAME: GameEntity::constructor

void __thiscall GameEntity::constructor(GameEntity* this, ParentClass* parent)
{
    int baseData;
    if (parent == 0) {
        baseData = 0;
    } else {
        baseData = *(int*)(parent + 0xc);  // +0xC: pointer to base class data
    }

    this->field1 = 0;   // +0x04
    this->field2 = 0;   // +0x08
    this->field4 = 0;   // +0x10
    this->field3 = 1;   // +0x0C

    this->vtable1 = &PTR_LAB_00e317dc;    // +0x00: first vtable for derived class
    this->field6 = 0;   // +0x18

    Fun_00452df0(baseData);                // call base class constructor

    this->field9 = 2;   // +0x24
    this->vtable1 = &PTR_LAB_00e33584;    // +0x00: override vtable (final derived vtable)
    this->vtable2 = &PTR_LAB_00e33608;    // +0x28: second base vtable for MI
    this->destructor = &LAB_00482420;     // +0x30: destructor/callback
    this->field_d = 0; // +0x34

    this->vtable2Pointer = &this->vtable2; // +0x14: pointer to second vtable slot (for compatibility)
}