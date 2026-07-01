// Xbox PDB: EARS_Apt_UIGuardPanel_ShowNotEnoughMoneyPopup
// FUNC_NAME: GuardNoMoneyStrategy::create
void GuardNoMoneyStrategy::create(void)
{
  int strategy;
  
  // Allocate 240 bytes for the strategy object
  strategy = allocateMemory(0xf0);
  if (strategy == 0) {
    strategy = 0;
  }
  else {
    // Initialize the strategy with a base index of 0
    strategy = initStrategy(0);
  }
  
  // Load the asset string for this strategy type
  loadAssetString("$strat_guard_no_money");
  
  // Set state/type field to 3
  *(undefined4 *)(strategy + 0xc) = 3;
  
  // Set a unique identifier/hash for this strategy
  *(undefined4 *)(strategy + 0x20) = 0x510c352b;
  
  // Set the update function pointer
  *(code **)(strategy + 0x14) = guardNoMoneyUpdate;
  
  // Finalize registration of the strategy
  finalizeStrategyInit();
  return;
}