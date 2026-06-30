// FUNC_NAME: UISlider::UISlider

// Constructor for a UI slider control in the Godfather 2 game.
// Address: 0x00748e10
// EARS engine UI system.

undefined4 * __thiscall UISlider::UISlider(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  float *pFloat;
  char bResult;
  int iTemp;

  // Call base class constructor (likely UIWidget::UIWidget)
  FUN_004ac120(param_2, param_3);

  // Set vtable pointer
  *this = &PTR_LAB_00d642b0;

  // +0x50: m_minValue
  this[0x14] = 0;
  // +0x58: m_maxValue
  this[0x16] = 0;
  // +0x5C: m_stepSize
  this[0x17] = 0;

  // +0x48: m_style (or m_flags)
  if (this[0x12] == 0) {
    iTemp = 0;
  } else {
    iTemp = this[0x12] + -0x48;
  }

  // +0x54: m_currentValue (float)
  pFloat = (float *)(this + 0x18);   // offset 0x60
  // +0x64: m_valueOffset (int)
  this[0x15] = iTemp;

  // Lookup a default value by hash 0x335c5c56 (likely a config key)
  bResult = FUN_008934e0(0x335c5c56, pFloat);
  if (bResult == '\0') {
    *pFloat = DAT_00d642a8;  // default float constant
  }

  // If there is a value offset, scale by a manager's field
  if (this[0x15] != 0) {
    iTemp = FUN_0043b870(DAT_01131040);  // get some manager singleton
    if (iTemp != 0) {
      // Multiply by manager's field at +0x3C (e.g., a resolution scale factor)
      *pFloat = *(float *)(iTemp + 0x3c) * *pFloat;
    }
  }

  // +0x64: m_initialValue (or m_dirty flag)
  this[0x19] = 0;
  return this;
}