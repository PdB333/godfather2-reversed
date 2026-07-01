// FUNC_NAME: CoverHintNode::destroy
void __fastcall CoverHintNode::destroy(CoverHintNode *this)
{
  // Deactivate or remove from some list if flag at +0x30 is set
  if (this->flag30)
  {
    FUN_0041e7d0(0);
  }
  this->flag30 = false;

  // If flag at +0x6 is set and a global visibility toggle is enabled, remove a visual marker at position
  if ((this->flag06) && (gMarkerVisibilityEnabled != 0))
  {
    // Parameters: id=0, x,y,z, unknown=0
    FUN_008269f0(0, this->posX, this->posY, this->posZ, 0);
    this->flag06 = false;
  }

  // Clear a large block of fields from +0x04 to +0x2F (44 bytes)
  memset(&this->unused04, 0, 0x2c);

  // Release a child object if flag at +0x31 is set
  if (this->flag31)
  {
    // Call virtual function at vtable+0x50 on the child object (e.g., release/delete)
    (*(void (__fastcall **)(int))(*(int *)gChildObjectVtable + 0x50))(this->childObject);

    // Store released child pointer globally and clear a global flag
    gCurrentChildObject = this->childObject;
    gObjectReleasedFlag = 0;

    this->flag31 = false;
  }
}