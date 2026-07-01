// FUNC_NAME: CSACrewComponent::CSACrewComponent
CSACrewComponent * __thiscall CSACrewComponent::CSACrewComponent(CSACrewComponent *this, byte isAllocated)
{
  // Set primary vtable
  this->vtbl = &CSACrewComponent_vtable;                  // +0x00

  // Set additional interface vtable pointers for multiple inheritance
  this->interfaceVtbl1 = &CSACrewComponent_interface1_vtable;   // +0x3C (offset 0xF)
  this->interfaceVtbl2 = &CSACrewComponent_interface2_vtable;   // +0x48 (offset 0x12)
  this->interfaceVtbl3 = &CSACrewComponent_interface3_vtable;   // +0x50 (offset 0x14)

  // Initialize subobject at offset 0x68 (list/container)
  CSACrewComponent::initSubobject(&this->subObject);        // +0x68
  CSACrewComponent::postConstruct(&this->subObject);

  // Global registration or static initialization
  registerCSACrewComponent();

  // If this object was dynamically allocated, it must be freed immediately? (unusual, but follows Ghidra decomp)
  if (isAllocated & 1)
  {
    operatorDelete(this, sizeof(CSACrewComponent)); // CSACrewComponent = 0x70 bytes
  }
  return this;
}