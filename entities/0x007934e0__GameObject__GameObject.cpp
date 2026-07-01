//FUNC_NAME: GameObject::GameObject
GameObject* __thiscall GameObject::GameObject(GameObject* this, byte allocFlag) {
    // Set primary vtable at offset 0
    this->vtable = &PTR_FUN_00d69f20;
    // Set secondary vtable at offset 0x3C (60 bytes)
    this->vtable2 = &PTR_LAB_00d69f10;
    // Set tertiary vtable at offset 0x48 (72 bytes)
    this->vtable3 = &PTR_LAB_00d69f0c;
    // Set quaternary vtable at offset 0x50 (80 bytes)
    this->vtable4 = &PTR_LAB_00d69f08;
    // Set quinary vtable at offset 0x54 (84 bytes)
    this->vtable5 = &PTR_LAB_00d69ea8;
    // Set senary vtable at offset 0x58 (88 bytes)
    this->vtable6 = &PTR_LAB_00d69e40;

    // Call base class constructor (likely Sentient or Entity)
    BaseClass::BaseClass(this); // FUN_00795340

    // If allocFlag bit 0 is set, allocate additional memory (size 0x430 = 1072 bytes)
    if (allocFlag & 1) {
        allocateMemory(this, 0x430); // FUN_0043b960
    }

    return this;
}