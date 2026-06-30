// FUNC_NAME: PlayerState::initDefault
void __thiscall PlayerState::initDefault(uint *this)
{
    uint uVar1 = DAT_00e2b1a4; // global default value (e.g., invalid ID or sentinel)
    // Initialize three groups: indices 0,5,10 set to default; rest zeroed
    this[0] = uVar1;
    this[1] = 0;
    this[2] = 0;
    this[3] = 0;
    this[4] = 0;
    this[5] = uVar1;
    this[6] = 0;
    this[7] = 0;
    this[8] = 0;
    this[9] = 0;
    this[10] = uVar1;
    this[11] = 0;
}