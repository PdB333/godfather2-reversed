// FUNC_NAME: DonControlGadget::handleMenuInput
undefined4 __thiscall DonControlGadget::handleMenuInput(int this, int inputAction)
{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  uVar4 = 0;
  iVar3 = FUN_00466840(); // getConfirmAction()
  if (inputAction == iVar3) {
    uVar1 = *(uint *)(this + 0xc0); // m_selectedVenueIndex
    uVar4 = 0;
    if ((uVar1 != 0xffffffff) && (uVar1 < *(uint *)(this + 0x68))) { // m_venueCount
      uVar4 = FUN_006b0ee0(*(undefined4 *)(*(int *)(this + 100) + uVar1 * 4)); // getVenueDataFromIndex
    }
    iVar3 = FUN_0095a800(uVar4); // getVenueState
    if (iVar3 != 1) {
      if ((iVar3 != 2) && (iVar3 != 3)) {
        return 0;
      }
      FUN_0095b4d0(1, uVar4); // performVenueAction(1, venue)
      return 0;
    }
    FUN_0095b4d0(2, uVar4); // performVenueAction(2, venue)
    return 0;
  }
  iVar3 = FUN_00466860(); // getBackAction()
  if (inputAction == iVar3) {
    cVar2 = FUN_00957d00(); // isOwnerAlive()
    local_8 = 0;
    local_4 = 0;
    if (cVar2 == '\0') {
      local_c = DAT_011302c0; // string "DeadOwner"
      FUN_00408a00(&local_c, 0); // displayMessage
      return 0;
    }
    local_c = DAT_01130310; // string "OwnerAlive"
    FUN_00408a00(&local_c, 0); // displayMessage
    return 0;
  }
  switch(inputAction) {
  case 0: // UP
  case 3: // DOWN
  case 5: // LEFT
    uVar4 = 1;
    break;
  case 6: // RIGHT
    uVar4 = *(undefined4 *)(this + 0x68); // m_venueCount
    uVar5 = 0xffffffff;
    goto LAB_0095b9fb;
  case 7: // SELECT
    uVar4 = *(undefined4 *)(this + 0x68); // m_venueCount
    uVar5 = 1;
LAB_0095b9fb:
    FUN_0095b3c0(uVar4, this + 0xc0, uVar5, "UpdateVenueSelection", &DAT_011304d8, &DAT_011302c0); // changeSelection
    FUN_0095b320(500); // playSound(500)
    return 0;
  case 8: // MONOPOLY_UP
    uVar5 = *(undefined4 *)(this + 0x5c); // m_monopolyCount
    uVar6 = 1;
    goto LAB_0095b978;
  case 9: // MONOPOLY_DOWN
    uVar5 = *(undefined4 *)(this + 0x5c); // m_monopolyCount
    uVar6 = 0xffffffff;
LAB_0095b978:
    *(undefined4 *)(this + 0xc0) = 0xffffffff; // m_selectedVenueIndex = -1
    FUN_0095b3c0(uVar5, (int *)(this + 0x8c), uVar6, "UpdateMonopolySelection", &DAT_011301c0, &DAT_011302c0); // changeMonopolySelection
    FUN_0095b320(500); // playSound(500)
    iVar3 = *(int *)(this + 0x8c); // m_selectedMonopolyIndex
    if ((iVar3 != -1) && (*(char *)(this + 0x48) != '\0')) { // m_hasMonopoly
      FUN_00956a50(iVar3, 0); // selectMonopoly(iVar3, 0)
      return 0;
    }
    break;
  case 10: // CONFIRM_MONOPOLY
    uVar1 = *(uint *)(this + 0xc0); // m_selectedVenueIndex
    uVar5 = 0;
    if ((uVar1 != 0xffffffff) && (uVar1 < *(uint *)(this + 0x68))) { // m_venueCount
      uVar5 = FUN_006b0ee0(*(undefined4 *)(*(int *)(this + 100) + uVar1 * 4)); // getVenueDataFromIndex
    }
    iVar3 = FUN_0095a800(uVar5); // getVenueState
    if (iVar3 == 1) {
      FUN_0095b4d0(3, uVar5); // performVenueAction(3, venue)
      return 0;
    }
    if (iVar3 == 2) {
      FUN_0095b4a0(uVar5); // performSpecialAction(venue)
      return 0;
    }
    break;
  case 0xc: // BACK
    FUN_00922e20(5, 0); // closeGadget(5, 0)
    return 0;
  }
  return uVar4;
}