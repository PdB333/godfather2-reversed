// FUNC_NAME: PlayerSM::resetState
void __fastcall PlayerSM::resetState(PlayerSM* this)
{
    // Zero out various state flags and timers
    this->field_0xa56 = 0;          // +0xa56: byte, likely a flag
    this->field_0xa68 = 0;          // +0xa68: int, timer or counter
    this->field_0xa64 = 0;          // +0xa64: int, timer or counter
    this->field_0xa60 = 0;          // +0xa60: int, timer or counter
    this->field_0xa6c = _DAT_00d5780c; // +0xa6c: int, set to global constant (likely -1 or invalid state)

    // Initialize sub-component at offset 0xfa0 (4000) with parameter 0
    FUN_0045ee00(reinterpret_cast<uint8_t*>(this) + 0xfa0, 0);
}