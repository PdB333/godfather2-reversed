// FUNC_NAME: CharacterController::updateActionState

void __thiscall CharacterController::updateActionState(CharacterController* this, void* pStateData, int actionType)
{
  int* pVtableBase;
  char bFlag;
  int iResult;
  int* pVtable;
  float* pMatrix;
  float fValue;
  float fStackLocal;
  uint uLocal;
  int iPlayer;
  undefined8 u64Var1;
  undefined4 u32Var2;
  undefined4 u32Array[7];
  undefined4 u32Stack;
  char acStack_70[12];
  undefined4 u32Stack2;
  undefined4 u32Stack3;
  char acStack_50[76];

  // Perform some initialization / sync
  FUN_00806590();

  iPlayer = 0;

  // If speed > 0
  if (0.0 < *(float*)((int)pStateData + 0x2c))
  {
    if (actionType != 2)
    {
      *(int*)((int)this + 0x1df4) = 0;
      *(int*)((int)this + 0x1df8) = 0;
    }
    FUN_0084e400(*(int*)((int)pStateData + 0x2c));
    *(int*)((int)this + 0x233c) = DAT_01205224;   // some global threshold
  }

  pVtableBase = (int*)((int)this - 0x394);
  iResult = FUN_00800a90();
  if (iResult != 0)
  {
    FUN_00702fa0(*(int*)((int)pStateData + 0x2c));
  }

  iResult = FUN_007ff880();

  if (actionType == 3) goto LABEL_Done;

  if (iResult != 0)
  {
    if (*(int*)((int)pStateData + 4) == 0)
      iPlayer = 0;
    else
      iPlayer = *(int*)((int)pStateData + 4) - 0x48;

    if (iResult == iPlayer) goto LABEL_Done;
  }

  fValue = (float)(*(double*)(**(int**)(*pVtableBase + 0xc0)))();   // virtual: get some time delta
  if (fValue > 0.0f)
  {
    // Positive delta: process state transitions
    switch (*(int*)((int)pStateData + 0x30))
    {
      case 1:   // e.g. idle
        iPlayer = -0x7da0cddf;
        bFlag = FUN_00690150(0x18);
        if (bFlag)
          FUN_006901b0(0x15);
        break;

      case 2:   // e.g. walking
        iPlayer = -0x331f1844;
        bFlag = FUN_00481620();
        if (bFlag)
        {
          iResult = FUN_00471610();
          FUN_0093bb80(*(undefined8*)(iResult + 0x30), *(int*)(iResult + 0x38),
                       *(undefined8*)((int)pStateData + 0x14), *(int*)((int)pStateData + 0x1c));
        }
        break;

      case 3:
      case 4:
      case 5:
      case 7:   // various movement states
        bFlag = FUN_00481620();
        if (bFlag && !FUN_00481660() && FUN_007f41e0())
          FUN_004abc20(1);
        if (*(int*)((int)pStateData + 0xc) != 0 && *(int*)((int)pStateData + 0xc) != 0x48)
        {
          iPlayer = (*(int*)((int)pStateData + 0xc) == 0) ? 0 : (*(int*)((int)pStateData + 0xc) - 0x48);
          FUN_00714db0(iPlayer, pVtableBase, 9);   // set animation
        }
        FUN_0079d440(pStateData);   // update state
        break;

      default:
        goto LABEL_Done;

      case 9:   // exhausted / stamina recovery
        if (DAT_01205214 > *(float*)((int)this + 0x2d90) + _DAT_00d6a528)
          goto LABEL_Done;
        *(float*)((int)this + 0x2d90) = DAT_01205214;
        FUN_006901b0(0x10);
        uLocal = 0;
        (**(int (__thiscall**)(int))(**(int*)(pVtableBase) + 0x94))(pVtableBase); // vtable call

        // Copy some matrix
        pMatrix = (float*)FUN_00471610();
        for (int i = 0; i < 16; i++)
          u32Array[i] = *(int*)(pMatrix + i);
        // Start a sound sequence
        FUN_0044b4e0();
        FUN_0045c740(&fValue, "pc_electro", acStack_50, 0x1ff, 0, pVtableBase, uLocal >> 2, 0, acStack_50, u32Array);
        FUN_00414df0();
        break;
    }

    // Set a flag (bit 16)
    *(int*)((int)this + 0x2108) |= 0x10000;

    // Check if certain flags are clear
    if (((*(int*)((int)this + 0x550) >> 0xd) & 1) == 0 && ((*(int*)((int)this + 0x54c) >> 0xb) & 1) == 0)
    {
      // Determine source position from state data or player
      if (*(int*)((int)pStateData + 4) == 0 || *(int*)((int)pStateData + 4) == 0x48)
      {
        u32Var2 = *(int*)((int)pStateData + 0x1c);
        u64Var1 = *(undefined8*)((int)pStateData + 0x14);
      }
      else
      {
        iResult = FUN_00471610();
        u64Var1 = *(undefined8*)(iResult + 0x30);
        u32Var2 = *(int*)(iResult + 0x38);
      }

      iPlayer = FUN_00471610();
      int iSomeVal = FUN_00471610();
      fValue = (float)(iSomeVal + 0x30);

      double dForce = (*(double (__thiscall**)(int))(**(int*)(pVtableBase) + 0x21c))(pVtableBase); // vtable: get some force value
      bFlag = FUN_007f7f30(&u64Var1, fValue, iPlayer + 0x20, (float)dForce);

      uLocal = DAT_00d5f520;
      if (bFlag)
        uLocal = DAT_00d62b78;

      // Prepare some array for vtable call
      u32Array[3] = 0;
      u32Stack = 0;
      u32Stack2 = 0;
      u32Stack3 = _DAT_00d5780c;

      (**(int (__thiscall**)(int*, int, int))(**(int*)(pVtableBase) + 0x90))(u32Array, (int)this + 0x354, 1); // vtable call

      float fTime1 = FUN_0072bb80(acStack_70);   // from some struct
      fValue = fTime1;
      iResult = FUN_00471610();
      float fTime2 = FUN_0072bb80(iResult + 0x20); // from player struct
      FUN_007f7540((float)(fValue - fTime2), uLocal, DAT_00d5f520);   // apply impulse?

      if (*(int*)((int)pStateData + 0x30) == 9)
        FUN_007f6420(0x56);   // play exhaustion sound
    }
    else
    {
      // Play grunt sound if certain flags are set
      (**(int (__thiscall**)(int, const char*))(**(int*)(pVtableBase) + 500))(pVtableBase, "exertion_grunt");
    }

    if (iPlayer != 0)
    {
      (**(int (__thiscall**)(int))(**(int*)(pVtableBase) + 0xa8))(pVtableBase); // vtable call: finish update
    }
  }
  else
  {
    // Negative or zero delta: handle case where time is not moving
LABEL_Done:
    // Update some linked list element
    pVtable = (int*)((int)pStateData + 0xc);
    if (*(int*)((int)pStateData + 0xc) != 0 && *(int*)((int)pStateData + 0xc) != 0x48 &&
        _DAT_00d577a0 < *(float*)((int)pStateData + 0x2c) && *(int*)((int)pStateData + 0x30) != 3)
    {
      if (*pVtable == 0)
        iPlayer = 0;
      else
        iPlayer = *pVtable - 0x48;
      int iOther = (**(int (__thiscall**)(int))(*(int*)(*(int*)((int)this + 0x1b9c) + 0xc)))(); // vtable call
      if (iPlayer != iOther)
      {
        iResult = FUN_006bc8d0();
        if (iResult)
          *(int*)(iResult + 0x1f5c) &= ~0x400;   // clear bit
      }
    }

    // Manage intrusive list at offset 0x2e24
    int* pList = (int*)((int)this + 0x2e24);
    if (*pList != *pVtable)
    {
      if (*(int*)((int)this + 0x2e1c) != *pList)
        FUN_006bf990(pList);
      if (pList != pVtable)
      {
        iPlayer = *pVtable;
        if (*pList != iPlayer)
        {
          if (*pList != 0)
            FUN_004daf90(pList);
          *pList = iPlayer;
          if (iPlayer != 0)
          {
            *(int*)((int)this + 0x2e28) = *(int*)(iPlayer + 4);
            *(int**)(iPlayer + 4) = pList;
          }
        }
      }
    }
  }
}