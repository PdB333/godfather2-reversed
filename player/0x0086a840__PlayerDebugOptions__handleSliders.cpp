// FUNC_NAME: PlayerDebugOptions::handleSliders
void __thiscall PlayerDebugOptions::handleSliders(int *this, uint uiEventContext)
{
  // uiEventContext is some UI context handle (e.g., from a widget manager)

  // Push/pop UI context with a hash identifier
  UI::pushContext(uiEventContext);  // FUN_00879d90
  UI::pushHash(uiEventContext, 0xb390b11a); // FUN_0043aff0
  UI::beginGroup(1); // FUN_0043af00

  // Check if slider interaction is active
  bool bIsDragging = UI::isSliderDragging(); // FUN_0043b120
  if (!bIsDragging)
  {
    // Get world transform matrix (likely from current camera or object)
    float *pMatrix = (float *)UI::getCurrentTransform(); // FUN_00471610
    // +0x3ce: Store axis scale lengths (X, Y, Z) as integers
    this[0x3ce] = (int)SQRT(pMatrix[2] * pMatrix[2] + pMatrix[1] * pMatrix[1] + pMatrix[0] * pMatrix[0]);
    this[0x3cf] = (int)SQRT(pMatrix[6] * pMatrix[6] + pMatrix[5] * pMatrix[5] + pMatrix[4] * pMatrix[4]);
    this[0x3d0] = (int)SQRT(pMatrix[10] * pMatrix[10] + pMatrix[9] * pMatrix[9] + pMatrix[8] * pMatrix[8]);
    // +0x3ca: Clear bit 24 (0x01000000) – probably "dirty" or "needs update"
    this[0x3ca] &= 0xfeffffff;
  }

  UI::pushHash(uiEventContext, 0x10e5319e); // FUN_0043aff0
  // Load slider range bounds from globals
  float fUpperBound = g_fSliderMax;   // _DAT_00d63484
  float fLowerBound = g_fSliderMin;   // DAT_00d5833c

  bIsDragging = UI::isSliderDragging(); // re-check after pushing hash
  do
  {
    if (bIsDragging != false)
    {
      // Slider is being dragged
      uint uiSliderIndex = g_uiSliderCount & g_uiSliderCurrentIndex; // DAT_010c2678 & DAT_012054b4
      g_uiSliderCurrentIndex++; // DAT_012054b4

      // vtable offset 0x198: likely "update" or "apply" callback
      void (*pUpdate)(void) = (void(*)(void))this[vtable + 0x198];
      // +0x3d6: Compute interpolated slider value from global array
      this[0x3d6] = (int)((fUpperBound - fLowerBound) * g_fSliderPositions[uiSliderIndex] + fLowerBound);
      // +0x40d: Set some scaling factor based on another parameter
      this[0x40d] = (int)(*(float *)(this[0xe0] + 8) * g_fSomeFactor); // DAT_00e44748

      if (!pUpdate())
      {
        // If update returns false, call another function
        // (possibly finalize/commit the changes)
        (**(void (__thiscall **)(int))(*(int *)this[0x2a8] + 4))(); // vtable call, offset +4
        UI::applyDebugChanges(1, 0, 0); // FUN_00868d70
      }
      return;
    }

    // Process UI events while not dragging
    UI::popGroup(); // FUN_0043b210 (returns something)
    uint uiEventType = UI::getCurrentEvent(); // FUN_0043ab70 (0..7)
    int pElementData;

    switch(uiEventType)
    {
    case 0: // Slider value changed? (0 = release or touch end)
      pElementData = UI::getCurrentElementData(); // FUN_0043b210
      if (*(int *)(pElementData + 8) == 0)
      {
        UI::enableElement(); // FUN_008622a0
        // Check and clear a specific flag (bit 19? 0x00080000)
        if ((this[0x322] & 0xfff7ffffU) != this[0x322])
        {
          (**(void (__thiscall **)(int))(this[0x16] + 0x28))(0x10); // vtable offset +0x28, arg 0x10
          this[0x322] = this[0x322] & 0xfff7ffff;
        }
      }
      else
      {
        UI::disableElement(); // FUN_008621d0
        // Check and set a different flag (0x00080000)
        if ((this[0x322] | 0x80000U) != this[0x322])
        {
          (**(void (__thiscall **)(int))(this[0x16] + 0x28))(0x10);
          this[0x322] = this[0x322] | 0x80000;
          this[0x3ca] = this[0x3ca] & 0xfeffffff;
          break;
        }
      }
      this[0x3ca] &= 0xfeffffff;
      break;

    case 1: // New slider index selected
      pElementData = UI::getCurrentElementData(); // FUN_0043b210
      this[0x3E7] = *(int *)(pElementData + 8); // Store as some kind of index/ID
      break;

    case 2: // Lower bound updated
      pElementData = UI::getCurrentElementData();
      fLowerBound = *(float *)(pElementData + 8);
      break;

    case 3: // Upper bound updated
      pElementData = UI::getCurrentElementData();
      fUpperBound = *(float *)(pElementData + 8);
      break;

    case 4: // Parameter A divisor
      pElementData = UI::getCurrentElementData();
      this[0x40a] = (int)(g_fBaseDivisor / *(float *)(pElementData + 8)); // _DAT_00d5780c
      break;

    case 5: // Parameter B divisor
      pElementData = UI::getCurrentElementData();
      this[0x40b] = (int)(g_fBaseDivisor / *(float *)(pElementData + 8));
      break;

    case 6: // Integer parameter C
      pElementData = UI::getCurrentElementData();
      this[0x469] = *(int *)(pElementData + 8);
      break;

    case 7: // Float parameter D scaled
      pElementData = UI::getCurrentElementData();
      this[0x46a] = (int)(*(float *)(pElementData + 8) * g_fScaleFactor); // DAT_00e445c8
      break;
    }

    UI::popGroup(); // FUN_0043b1a0
    bIsDragging = UI::isSliderDragging(); // FUN_0043b120
  } while(true);
}