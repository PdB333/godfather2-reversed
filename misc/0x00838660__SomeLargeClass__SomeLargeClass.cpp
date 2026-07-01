// FUNC_NAME: SomeLargeClass::SomeLargeClass
void __thiscall SomeLargeClass::SomeLargeClass(SomeLargeClass *this)
{
  // Set vtable pointer (base class vtable)
  this->vtable = &PTR_FUN_00d73ce4; // +0x00
  // Set additional vtable pointers for sub-objects
  this->field_0x3c = &PTR_LAB_00d73cd4; // +0x3C (offset 0x0F*4)
  this->field_0x48 = &PTR_LAB_00d73cd0; // +0x48 (offset 0x12*4)

  // Call base class constructor
  BaseClass::BaseClass(this); // FUN_0083a0c0

  // Static initialization (e.g., memory manager, input system)
  staticInit(); // FUN_00838200

  // Initialize 10 sub-object handles at offsets 0x94, 0x9C, ..., 0xDC
  initHandle(&this->handleArray[0]); // +0x94 (offset 0x25*4)
  initHandle(&this->handleArray[1]); // +0x9C (offset 0x27*4)
  initHandle(&this->handleArray[2]); // +0xA4 (offset 0x29*4)
  initHandle(&this->handleArray[3]); // +0xAC (offset 0x2B*4)
  initHandle(&this->handleArray[4]); // +0xB4 (offset 0x2D*4)
  initHandle(&this->handleArray[5]); // +0xBC (offset 0x2F*4)
  initHandle(&this->handleArray[6]); // +0xC4 (offset 0x31*4)
  initHandle(&this->handleArray[7]); // +0xCC (offset 0x33*4)
  initHandle(&this->handleArray[8]); // +0xD4 (offset 0x35*4)
  initHandle(&this->handleArray[9]); // +0xDC (offset 0x37*4)

  // Initialize global handles (static objects)
  initHandle(&g_globalHandle1); // DAT_0112dbec
  initHandle(&g_globalHandle2); // DAT_0112dbf4

  // Destroy any previously allocated sub-objects (safety cleanup)
  if (this->subObject1 != NULL) { // +0x18C (offset 0x63*4? Wait, param_1[99] is offset 0x18C)
    (this->subObject1Destructor)(this->subObject1); // +0x198 (offset 0x66*4)
  }
  if (this->subObject2 != NULL) { // +0x17C (offset 0x5F*4)
    (this->subObject2Destructor)(this->subObject2); // +0x188 (offset 0x62*4)
  }
  if (this->subObject3 != NULL) { // +0x16C (offset 0x5B*4)
    (this->subObject3Destructor)(this->subObject3); // +0x178 (offset 0x5E*4)
  }
  if (this->subObject4 != NULL) { // +0x15C (offset 0x57*4)
    (this->subObject4Destructor)(this->subObject4); // +0x168 (offset 0x5A*4)
  }
  if (this->subObject5 != NULL) { // +0x14C (offset 0x53*4)
    (this->subObject5Destructor)(this->subObject5); // +0x158 (offset 0x56*4)
  }
  if (this->subObject6 != NULL) { // +0x13C (offset 0x4F*4)
    (this->subObject6Destructor)(this->subObject6); // +0x148 (offset 0x52*4)
  }
  if (this->subObject7 != NULL) { // +0x12C (offset 0x4B*4)
    (this->subObject7Destructor)(this->subObject7); // +0x138 (offset 0x4E*4)
  }
  if (this->subObject8 != NULL) { // +0x60 (offset 0x18*4)
    (this->subObject8Destructor)(this->subObject8); // +0x6C (offset 0x1B*4)
  }
  if (this->subObject9 != NULL) { // +0x50 (offset 0x14*4)
    (this->subObject9Destructor)(this->subObject9); // +0x5C (offset 0x17*4)
  }

  // Post-construction initialization (e.g., register with manager)
  postConstructInit(); // FUN_0046c640
}