// FUNC_NAME: CoverHintNode::initDefaults
void __thiscall CoverHintNode::initDefaults(void)
{
  // +0x00: parent/previous node ID (invalid = -1)
  this->m_iParentNode = -1;
  // +0x04 through +0x20: child references, flags, counters (zeroed)
  this->m_iChild1 = 0;
  this->m_iChild2 = 0;
  this->m_iSibling = 0;
  this->m_iFlags1 = 0;
  this->m_iFlags2 = 0;
  this->m_iHeight = 0;
  this->m_iExtra1 = 0;
  this->m_iExtra2 = 0;
  // +0x24 (index 9) left uninitialized (skip)
  // +0x28: state field (default active)
  this->m_iActiveState = 1;
  // +0x2C: secondary state (default walkable)
  this->m_iWalkableState = 1;
  // +0x30: debug flag (default off)
  this->m_bDebugDraw = 0;
  // +0x34: usage counter (default 0)
  this->m_iUseCount = 0;
  // +0x38: associated target entity ID (invalid = -1)
  this->m_iTargetID = -1;
  // +0x3C: debug draw color (opaque black)
  this->m_uDebugColor = 0xFF000000;
  // +0x40: cover type (3 = eCoverType3, e.g. high cover)?
  this->m_iCoverType = 3;
  // indices 17..21 (offsets 0x44..0x54) left uninitialized
  // +0x58: reserved field (0)
  this->m_iReserved = 0;
}