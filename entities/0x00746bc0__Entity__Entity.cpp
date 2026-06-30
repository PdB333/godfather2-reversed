// FUNC_NAME: Entity::Entity
__thiscall Entity::Entity(Entity *this, void *baseArg1, int baseArg2) {
    // Call base class constructor (likely Object or SimObject)
    Object::Object(baseArg1, baseArg2);

    // Set vtable pointer for Entity
    this->vtable = &Entity_vtable; // 0x00d63f60

    // Initialize fields at various offsets
    this->field_0x88 = 0; // offset +0x88
    this->field_0x8C = 0; // offset +0x8C
    this->field_0x90 = 0; // offset +0x90
    this->field_0x94 = 0; // offset +0x94
    this->field_0x98 = 0; // offset +0x98
    this->field_0x7C = 0; // offset +0x7C

    // Retrieve data pointer from base class (offset +0x48)
    // If not null, derive a manager object from it (subtract 0x48 to get vtable base)
    DataManager *mgr = nullptr;
    if (this->baseDataPtr != nullptr) {
        mgr = (DataManager *)(this->baseDataPtr - 0x48);
    }

    // Attempt to register this entity with a class hash via a virtual function in the data manager
    int regResult = 0;
    if (mgr != nullptr) {
        // Virtual function at vtable+0x10 (fourth entry)
        regResult = mgr->VtableRegister(0x369ac561, &baseArg2); // expects bool return as char
    }

    if (regResult != 0) {
        // On successful registration, store an identifier (likely from return address, but simplified here)
        this->regId = (uint)regResult; // offset +0x50 (param_1[0x14])
        // Fetch a script object from global manager
        this->scriptObject = (ScriptObject *)GlobalScriptManager::GetInstance().GetObject(); // FUN_0043b870 with DAT_01131064
    } else {
        this->regId = 0;
        this->scriptObject = nullptr;
    }

    return this;
}