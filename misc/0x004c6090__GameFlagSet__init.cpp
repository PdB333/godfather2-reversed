// FUNC_NAME: GameFlagSet::init
class GameFlagSet {
public:
    // Offsets: +0x00 : uint64_t field_0 (8 bytes, zeroed)
    //          +0x08 : uint64_t field_8 (8 bytes, zeroed)
    //          +0x10 : int32_t field_10 (set to some constant)
    //          +0x14 : int32_t field_14 (set to some constant)
    //          +0x18 : int32_t field_18 (set to 0x80000000)
    void __thiscall init() {
        // On entry: ecx = this

        // Zero first 16 bytes (two 8-byte fields)
        this->field_0 = 0;
        this->field_8 = 0;

        // Initialize flag/settings from global constants
        this->field_10 = DAT_00e445fc;   // +0x10: e.g., some threshold
        this->field_14 = DAT_00e445f8;   // +0x14: e.g., another threshold
        this->field_18 = 0x80000000;     // +0x18: set highest bit (enable/active flag)
    }
};