// FUNC_NAME: InputDeviceManager::InputDeviceManager
// Address: 0x0068d5f0
// Role: Constructor for the InputDeviceManager singleton (global instance DAT_01129810).
// Initializes internal vtable, device state, and optionally loads a pre-existing input buffer.

class InputDeviceManager {
public:
    // Virtual table pointers are at offset 0x00 (*this)
    // Members based on initializer:
    // +0x04: some flag (int)
    // +0x08: some count (int)
    // +0x0C: pointer to function table (vtable override?)
    // +0x10: unknown (int)
    // +0x14: pointer to data table (another vtable?)
    // +0x18: unknown (int) (set to 0 later)

    void* __fastcall constructor(InputDeviceManager* this);
};

void* __fastcall InputDeviceManager::constructor(InputDeviceManager* this) {
    // Initialize base class (or first stage)
    this->flag1 = 1;                        // offset +0x04 (bool/int)
    this->count = 0;                        // offset +0x08
    this->vtable1 = &g_InputDeviceVTableBase; // offset +0x0C, PTR_FUN_00e32808
    this->field10 = 0;                      // offset +0x10
    this->dataTable = &g_InputDeviceDataBase; // offset +0x14, PTR_LAB_00d5c660

    // Store singleton pointer
    g_InputDeviceManager = this;            // DAT_01129810

    // Override with derived class vtable
    *reinterpret_cast<void**>(this) = &g_InputDeviceVTableDerived; // PTR_FUN_00d5c66c
    this->vtable1 = &g_InputDeviceVTableOverride; // offset +0x0C, PTR_LAB_00d5c668
    this->dataTable = &g_InputDeviceDataOverride; // offset +0x14, PTR_LAB_00d5c664
    this->field18 = 0;                      // offset +0x18

    // Initialize subsystem
    FUN_0040eba0(0);                        // e.g., setupInput(0)

    // Load some global data pointer
    FUN_009cb330(g_DAT_00d5779c);          // e.g., loadConfiguration

    // If a pre-allocated input buffer exists, copy it into this object
    if (g_pInputBuffer != nullptr)          // DAT_01206940
    {
        FUN_00408900(this, &g_pInputBuffer, 0x8000); // e.g., memcpy(deviceData, buffer, 32768)
    }

    return this;
}