// FUNC_NAME: PlayerSM::enterState
void __fastcall PlayerSM::enterState(PlayerSM* this)
{
    // Call base class enter state (likely CharacterSM or similar)
    CharacterSM::enterState((CharacterSM*)this);
    
    // Call method to initialize state-specific data
    // param_1 + 0x10 = some state context object
    // param_1 + 0xc0 = player input or movement parameters
    // param_1 + 0xb0 = state-specific data buffer
    initStateData(*(void**)&this[0x10], *(void**)&this[0xc0], &this[0xb0]);
}