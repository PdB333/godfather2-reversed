// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager *this)
{
  // Set vtable pointer (likely to base class destructor)
  *(int *)this = (int)&PTR_FUN_00d8cad8;
  this->field_0x10 = &PTR_LAB_00d8cab0; // +0x10
  this->field_0x50 = &PTR_LAB_00d8caac; // +0x50
  this->field_0x54 = &PTR_LAB_00d8ca94; // +0x54

  // Release various resource handles (likely texture/sound/effect handles)
  FUN_009c8f10(this->field_0x7c); // +0x7C
  FUN_009c8f10(this->field_0x80); // +0x80
  FUN_009c8f10(this->field_0x84); // +0x84
  FUN_009c8f10(this->field_0x88); // +0x88
  FUN_009c8f10(this->field_0x98); // +0x98
  FUN_009c8f10(this->field_0x9c); // +0x9C
  FUN_009c8f10(this->field_0xa0); // +0xA0
  FUN_009c8f10(this->field_0xa4); // +0xA4
  FUN_009c8f10(this->field_0xa8); // +0xA8
  FUN_009c8f10(this->field_0xac); // +0xAC

  // Release optional resources
  if (this->field_0x64 != 0) { // +0x64
    FUN_009c8f10(this->field_0x64);
  }
  if (this->field_0x58 != 0) { // +0x58
    FUN_009c8f10(this->field_0x58);
  }

  // Reset vtable pointer to base destructor
  this->field_0x50 = &PTR_LAB_00d8ca90; // +0x50

  // Clear global singleton pointer
  DAT_0113003c = 0;

  // Call cleanup function (likely memory manager or subsystem shutdown)
  FUN_00957d90();
}