// FUNC_NAME: CrewLeaderComponent::CrewLeaderComponent

undefined4 * __thiscall CrewLeaderComponent::CrewLeaderComponent(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely Component or GameObject)
  Component::Component(param_2);

  // Set up vtable pointers for multiple inheritance
  this[0x00] = &PTR_FUN_00d69c7c;           // Primary vtable pointer at +0x00
  this[0x0F] = &PTR_LAB_00d69c6c;           // Secondary vtable pointer at +0x3C
  this[0x12] = &PTR_LAB_00d69c68;           // Tertiary vtable pointer at +0x48
  this[0x14] = &PTR_LAB_00d69c50;           // Quaternary vtable pointer at +0x50

  // Initialize crew state fields
  this[0x15] = 0;                           // +0x54: m_crewStateFlags or similar
  this[0x16] = 0;                           // +0x58
  this[0x17] = 0;                           // +0x5C
  this[0x18] = 0;                           // +0x60
  this[0x19] = 0;                           // +0x64
  this[0x1A] = 0;                           // +0x68
  this[0x1B] = 0;                           // +0x6C
  this[0x1C] = 0;                           // +0x70
  this[0x1D] = 0;                           // +0x74
  this[0x1E] = 0;                           // +0x78
  this[0x1F] = 0;                           // +0x7C
  this[0x20] = 0;                           // +0x80
  this[0x21] = 0;                           // +0x84
  this[0x22] = 0;                           // +0x88
  this[0x23] = 0;                           // +0x8C
  this[0x24] = 0;                           // +0x90
  this[0x25] = 0;                           // +0x94
  this[0x26] = 0;                           // +0x98

  // Set a single byte at offset +0x98? Actually *(undefined1 *)(this + 0x2c) sets byte at address this+0xB0
  // Probably setting a flags field to 0
  *(uint8_t *)((int)this + 0xB0) = 0;       // +0xB0: m_bSomeFlag

  // Initialize invalid indices
  this[0x27] = 0xFFFFFFFF;                  // +0x9C: m_crewLeaderIndex = -1
  this[0x28] = 0xFFFFFFFF;                  // +0xA0: m_crewTargetIndex = -1
  this[0x2B] = 0;                           // +0xAC: m_crewCount = 0
  this[0x2A] = 0;                           // +0xA8: m_crewArray or similar
  this[0x29] = 0;                           // +0xA4: m_crewCapacity = 0

  return this;
}