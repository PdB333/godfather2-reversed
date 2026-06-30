// FUNC_NAME: SomeEARSComponent::~SomeEARSComponent
void __fastcall SomeEARSComponent::~SomeEARSComponent(SomeEARSComponent* this)
{
  // Set vtable to most derived (first in hierarchy), then perform destruction steps
  this->vtable = (SomeEARSComponentVTable*)&PTR_LAB_00d65c2c;
  // Release two resource pools (possibly audio/stream buffers)
  memFree(0x51);
  memFree(3);
  // Shutdown some subsystem (e.g., EARS engine shutdown)
  shutdown();
  // Delete member at offset +0x74 (likely a dynamically allocated child object)
  if (this->field_0x74 != (void*)0x0) {
    operatorDelete(&this->field_0x74);
  }
  // Switch vtable to base (second in hierarchy) and delete base member at offset +0x68
  this->vtable = (SomeEARSComponentVTable*)&PTR_LAB_00d63090;
  if (this->field_0x68 != (void*)0x0) {
    operatorDelete(&this->field_0x68);
  }
  // Final cleanup (may call base destructor or free object memory)
  finalCleanup();
}