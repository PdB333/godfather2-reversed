// FUNC_NAME: NetworkManager::constructor
NetworkManager* __thiscall NetworkManager::constructor(NetworkManager* this, void* sink, void* arg3, void* arg4) {
    // +0x04: unknown field
    this->field_4 = 0;
    // +0x08: temporary pointer, later overwritten
    this->field_8 = &PTR_LAB_00e31e48;

    // Global static initialization
    void** ppuVar2 = DAT_012054bc;
    bool bGlobalNull = (DAT_012054bc == nullptr);
    DAT_0122345c = this; // store this in global singleton

    // +0x00: vtable pointer
    this->vtable = &PTR_FUN_00e31e38;
    // +0x08: update to correct vtable entry
    this->field_8 = &PTR_LAB_00e31e44;
    // +0x0C: store sink parameter
    this->sink = sink;
    // Zero-initialize remaining fields
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;

    // Local GUID structure (or something similar)
    GUID localGuid = {0, 0, 0};

    if (bGlobalNull) {
        ppuVar2 = &PTR_PTR_0110ae94;
        DAT_012054bc = &PTR_PTR_0110ae94;
    }

    // Create a GUID/id and store at +0x34 and +0x38
    this->someId = FUN_004265d0(&localGuid, ppuVar2);
    this->somePtr = ppuVar2;

    // Call virtual function on the object pointed by ppuVar2
    (*(void (__thiscall**)(void*))(*ppuVar2 + 8))(nullptr);

    // +0x28, +0x2C, +0x30: more fields set to 0
    this->field_28 = 0;
    this->field_2C = 0;
    this->field_30 = 0;

    FUN_00ab5fb0(0, 1);

    // +0x70? Actually offset 0x1C in bytes, set to 0 (this->byteField)
    *(char*)((int)this + 0x1C) = 0;

    // Call virtual function on sink object
    (*(void (__thiscall**)(void*))(*(int*)this->sink + 8))(this->sink);

    // Register callbacks or something
    FUN_0049c6e0(&PTR_LAB_00e31e30, 1);
    FUN_0049c6e0(&PTR_LAB_00e31e34, 1);

    // Additional initialization routines with arg3 and arg4
    FUN_004630a0(arg3);
    FUN_00463260(arg4);

    return this;
}