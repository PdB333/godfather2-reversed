// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(int this)
{
  int iVar1;
  
  iVar1 = this + 0x2e40;
  // Shutdown EARS framework subsystems
  FUN_005c3960(iVar1);  // EARS::Framework::Module::shutdown
  FUN_005c3c70(iVar1);  // EARS::Framework::Module::destroy
  
  // Call shutdown on various game subsystems via vtable offset 0x68 (shutdown method)
  (**(code **)(*(int *)(this + 0x2bc0) + 0x68))();  // +0x2BC0: some manager
  (**(code **)(*(int *)(this + 0x2a9c) + 0x68))();  // +0x2A9C: some manager
  (**(code **)(*(int *)(this + 0x29c4) + 0x68))();  // +0x29C4: some manager
  (**(code **)(*(int *)(this + 0x2a14) + 0x68))();  // +0x2A14: some manager
  (**(code **)(*(int *)(this + 0x2970) + 0x68))();  // +0x2970: some manager
  (**(code **)(*(int *)(this + 0x2590) + 0x68))();  // +0x2590: some manager
  (**(code **)(*(int *)(this + 0x2504) + 0x68))();  // +0x2504: some manager
  (**(code **)(*(int *)(this + 0x24a8) + 0x68))();  // +0x24A8: some manager
  (**(code **)(*(int *)(this + 0x2320) + 0x68))();  // +0x2320: some manager
  (**(code **)(*(int *)(this + 0xf60) + 0x68))();   // +0xF60: some manager
  (**(code **)(*(int *)(this + 0xedc) + 0x68))();   // +0xEDC: some manager
  
  FUN_005c1820();  // EARS::Framework::Module::update (flush)
  
  (**(code **)(*(int *)(this + 0xd48) + 0x68))();   // +0xD48: some manager
  (**(code **)(*(int *)(this + 0xc38) + 0x68))();   // +0xC38: some manager
  (**(code **)(*(int *)(this + 0xbd8) + 0x68))();   // +0xBD8: some manager
  (**(code **)(*(int *)(this + 0x4d0) + 0x68))();   // +0x4D0: some manager
  (**(code **)(*(int *)(this + 0x354) + 0x68))();   // +0x354: some manager
  (**(code **)(*(int *)(this + 0x250) + 0x68))();   // +0x250: some manager
  (**(code **)(*(int *)(this + 0x118) + 0x68))();   // +0x118: some manager
  
  FUN_005c1820();  // EARS::Framework::Module::update (flush)
  
  (**(code **)(*(int *)(this + 0x60) + 0x68))();    // +0x60: some manager
  
  FUN_005c1820();  // EARS::Framework::Module::update (flush)
  FUN_005c1820();  // EARS::Framework::Module::update (flush)
  
  // Reset vtable pointer for EARS module
  *(undefined ***)(this + 0x2e40) = &PTR_LAB_00e3e74c;
  
  // Shutdown various game systems
  FUN_0098c4a0();  // some system shutdown
  FUN_00986e50();  // some system shutdown
  FUN_00961690();  // some system shutdown
  FUN_00960330();  // some system shutdown
  FUN_00937110();  // some system shutdown
  FUN_00926db0();  // some system shutdown
  FUN_009238f0();  // some system shutdown
  FUN_00993060();  // some system shutdown
  FUN_0098fe10();  // some system shutdown
  FUN_00925550();  // some system shutdown
  FUN_00974fa0();  // some system shutdown
  
  // Set up vtable pointers for another subsystem
  *(undefined ***)(this + 0xe7c) = &PTR_FUN_00d84018;
  *(undefined ***)(this + 0xe8c) = &PTR_LAB_00d83ff4;
  *(undefined ***)(this + 0xec8) = &PTR_LAB_00d83ff0;
  *(undefined ***)(this + 0xec8) = &PTR_LAB_00d83fec;
  
  DAT_0112fe08 = 0;  // global flag
  
  FUN_005c16e0();  // EARS::Framework::Module::constructor
  
  // Set up vtable pointers for another subsystem
  *(undefined ***)(this + 0xde8) = &PTR_FUN_00d86000;
  *(undefined ***)(this + 0xdf8) = &PTR_LAB_00d85fdc;
  *(undefined ***)(this + 0xe34) = &PTR_LAB_00d85fd8;
  
  if (*(int *)(this + 0xe60) != 0) {
    (**(code **)(this + 0xe6c))(*(int *)(this + 0xe60));  // destructor call
  }
  
  *(undefined ***)(this + 0xe34) = &PTR_LAB_00d85d84;
  DAT_0112982c = 0;  // global flag
  
  FUN_005c16e0();  // EARS::Framework::Module::constructor
  
  // Final cleanup calls
  FUN_0098e470();  // some cleanup
  FUN_0091a7e0();  // some cleanup
  FUN_00961f10();  // some cleanup
  FUN_0096fbb0();  // some cleanup
  FUN_00986490();  // some cleanup
  FUN_00952890();  // some cleanup
  FUN_00989450();  // some cleanup
  FUN_00959ff0();  // some cleanup
  FUN_00930d60();  // some cleanup
  FUN_00911d50();  // some cleanup
  
  return;
}