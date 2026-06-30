// FUNC_NAME: GodfatherGameManager::initializeSingleton
undefined4 * GodfatherGameManager::initializeSingleton(void)

{
  FUN_006126d0(); // likely EARS::Framework::SingletonBase::init()
  DAT_01219a48 = 0; // +0x0A8: some flag
  _DAT_012199e4 = 0; // +0x044: some state
  _DAT_012199e8 = 0; // +0x048: some state
  DAT_01219940 = &PTR_LAB_00e38498; // +0x000: vtable pointer
  _DAT_01219a00 = 0; // +0x060: some field
  _DAT_01219a04 = 0; // +0x064: some field
  _DAT_01219a08 = 0; // +0x068: some field
  _DAT_01219a0c = DAT_00e2b1a4; // +0x06C: copy from global constant
  _DAT_012199f0 = 0; // +0x050: some field
  _DAT_012199f4 = 0; // +0x054: some field
  _DAT_012199f8 = 0; // +0x058: some field
  _DAT_012199fc = 0; // +0x05C: some field
  _DAT_01219a14 = 0; // +0x074: some field
  _DAT_01219a10 = 0; // +0x070: some field
  return &DAT_01219940; // return pointer to singleton instance
}