// FUNC_NAME: ParticleEmitter::constructor
void __thiscall ParticleEmitter::constructor(ParticleEmitter *this, int data)
{
  int *prevPtr;
  byte bVar1;
  int headNode;
  bool bVar2;
  float fVar3;
  float fVar4;
  
  // vtable setup
  this->vtable = &PARTICLE_EMITTER_VTABLE;
  this->unk04 = 0;
  this->unk08 = 0;
  this->parentNode = 0;            // offset 0x18
  this->nextNode = 0;              // offset 0x1C
  this->refCountedPtr = 0;         // offset 0x20
  
  // large offset fields start at 0xB0
  this->someFlagField = 2;         // offset 0xB0 (index 0x2c)
  this->field_B4 = 0;              // offset 0xB4
  this->field_B8 = 0xffffffff;     // offset 0xB8
  this->field_BC = 0;              // offset 0xBC
  this->field_C4 = 0;              // offset 0xC4
  this->field_C8 = 0;              // offset 0xC8
  
  // Insert into global linked list
  prevPtr = &(this->parentNode);   // offset 0x18
  if (*prevPtr != g_pParticleListHead) {
    if (*prevPtr != 0) {
      linkedListRemove(prevPtr);    // FUN_004daf90
    }
    headNode = g_pParticleListHead;
    bVar2 = g_pParticleListHead != 0;
    *prevPtr = g_pParticleListHead; // set this->prev = head
    if (bVar2) {
      this->nextNode = *(int *)(headNode + 4); // move old head's next to this->next
      *(int **)(headNode + 4) = prevPtr;       // head->next = this (via prevPtr)
    }
  }
  
  // Copy data from the given template
  fVar3 = g_float_constant;        // DAT_00e2b1a4, likely 1.0f or similar
  this->flags = 0x10000000;        // offset 0x0C
  this->templateData = data;       // offset 0x10
  this->colorA = fVar3;            // offset 0xA0
  this->colorB = fVar3;            // offset 0xA4
  this->colorC = fVar3;            // offset 0xA8
  this->colorD = fVar3;            // offset 0xAC
  
  this->somePtr = *(int *)(data + 0x20); // offset 0x88
  
  // Transfer flags from data template
  if ((*(uint *)(data + 0x14) & 0x200) != 0) {
    this->flags = this->flags | 0x40000000;
  }
  if ((*(uint *)(data + 0x14) & 0x20000000) != 0) {
    this->flags = this->flags | 0x80000000;
  }
  if ((*(uint *)(data + 0x14) & 0x100) != 0) {
    this->flags = this->flags | 0x400000;
  }
  
  // Copy and modify a float value
  this->emissionFloat = *(float *)(data + 0x18); // offset 0xE0
  fVar4 = fVar3;
  if (g_thresholdFloat < *(float *)(data + 0x18)) // DAT_00e2b05c
  {
    bVar1 = *(byte *)(data + 0x16);
    randomFunction();               // FUN_004e41b0, might set a random seed
    fVar4 = g_float_constant;
    this->emissionFloat = (float)(bVar1 & 0x1f) * fVar3 * *(float *)(data + 0x18) * g_otherFloat + (float)this->emissionFloat;
  }
  
  // Handle reference counting on the refCountedPtr (offset 0x20)
  this->field_14 = 0;               // offset 0x14
  if (this->refCountedPtr != 0) {
    prevPtr = (int *)(this->refCountedPtr + 4);
    *prevPtr = *prevPtr - 1;
    if (*(int *)(this->refCountedPtr + 4) == 0) {
      (**(code **)(*(int *)this->refCountedPtr + 4))();
      fVar4 = g_float_constant;
    }
    this->refCountedPtr = 0;
  }
  
  // More initializations
  this->refCountedPtr = 0;
  this->field_7C = 0;              // offset 0x7C
  this->field_90 = fVar4;          // offset 0x90
  this->field_8C = fVar4;          // offset 0x8C
  
  // Short fields at 0x80 and 0x82
  *(short *)&(this->someShort) = 0;            // offset 0x80
  *(short *)((int)this + 0x82) = 0x1c;        // offset 0x82
  
  this->field_84 = 0xffffffff;     // offset 0x84
  
  // Zero out a range of floats
  this->posX = fVar4;              // offset 0x30 (index 0xc)
  this->posY = 0.0f;               // offset 0x34
  this->posZ = 0.0f;               // offset 0x38
  this->field_3C = 0.0f;           // offset 0x3C
  this->field_40 = 0.0f;           // offset 0x40
  this->field_44 = fVar4;          // offset 0x44
  this->field_48 = 0.0f;           // offset 0x48
  this->field_4C = 0.0f;           // offset 0x4C
  this->field_50 = 0.0f;           // offset 0x50
  this->field_54 = 0.0f;           // offset 0x54
  this->field_58 = fVar4;          // offset 0x58
  this->field_5C = 0.0f;           // offset 0x5C
  this->field_60 = 0.0f;           // offset 0x60
  this->field_64 = 0.0f;           // offset 0x64
  this->field_68 = 0.0f;           // offset 0x68
  this->field_6C = fVar4;          // offset 0x6C
  
  return;
}