// FUNC_NAME: AudioDataManager::Constructor
// Function address: 0x006b7aa0
// Role: Constructor for AudioDataManager (EARS engine class)
// Sets up vtable, function table pointers, and initializes a 0x7FFF-sized buffer (likely lookup table for audio data)

// External base constructor (likely parent class or initializer)
void __thiscall AudioDataManager_BaseConstructor(uint32_t param2);

// Buffer clear function (likely memset-like)
void __cdecl ClearBuffer(void* buffer, int size);

// Global data referenced by this constructor
extern uint32_t DAT_00e448f0;          // global field value stored at +0x5C
extern void PTR_FUN_00d5e588;          // vtable pointer for this class
extern void PTR_LAB_00d5e578;          // function table pointer stored at +0x3C
extern void PTR_LAB_00d5e574;          // another function pointer stored at +0x48
extern uint8_t DAT_0120e93c[];         // buffer to be cleared (size 0x7FFF)

class AudioDataManager {
public:
    // Offset 0x00: vtable pointer
    void* vtable;
    // Offset 0x3C: pointer to some function dispatch table
    void* field_0x3C;
    // Offset 0x48: another function pointer
    void* field_0x48;
    // Offset 0x5C: reference to global data (DAT_00e448f0)
    uint32_t field_0x5C;
    // Offset 0x60: integer flag / counter
    uint32_t field_0x60;
    // Offset 0x64: boolean flag
    uint8_t  field_0x64;

    // Constructor (__thiscall in original x86)
    AudioDataManager* __thiscall Constructor(uint32_t param2);
};

// Constructor implementation
AudioDataManager* __thiscall AudioDataManager::Constructor(uint32_t param2) {
    // Call base constructor (unknown class)
    AudioDataManager_BaseConstructor(param2);

    // Set vtable
    this->vtable = &PTR_FUN_00d5e588;
    // Initialize function table references
    this->field_0x3C = &PTR_LAB_00d5e578;
    this->field_0x48 = &PTR_LAB_00d5e574;
    // Store global value
    this->field_0x5C = DAT_00e448f0;
    // Clear counter and byte flag
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    // Initialize the large buffer (likely a hash table or lookup table)
    ClearBuffer(&DAT_0120e93c, 0x7FFF);

    return this;
}