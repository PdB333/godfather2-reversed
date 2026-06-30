// FUNC_NAME: EARSComponent::EARSComponent
int __thiscall EARSComponent::EARSComponent(EARSComponent *this, byte flags)
{
  // vtable at +0x28
  this->vtable = &EARSComponent_vtable_00e317cc;
  FUN_004530e0(); // Base class constructor
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete / cleanup
  }
  return (int)this;
}