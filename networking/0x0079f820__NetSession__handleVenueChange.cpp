// FUNC_NAME: NetSession::handleVenueChange
void __fastcall NetSession::handleVenueChange(int this)
{
  char cVar1;
  int iVar2;
  char local_5;
  int local_4;

  FUN_007ff790(); // likely some session validation/check
  if ((*(uint *)(this + 0x8e8) >> 0x1d & 1) != 0) { // +0x8e8: flags bit 29 = session active?
    return;
  }
  local_4 = 0;
  local_5 = '\0';
  iVar2 = FUN_00471610(); // get current player/entity
  cVar1 = FUN_006afca0(iVar2 + 0x30, _DAT_00d5c458, DAT_00d5779c, &local_4, &local_5); // query venue change data
  if (cVar1 == '\0') {
    return;
  }
  if (local_5 == '\0') {
    FUN_007f6420(0x61); // hide venue change UI (0x61 = some UI element ID)
  } else {
    FUN_007f63e0(0x61); // show venue change UI
  }
  if (local_4 == *(int *)(this + 0x1ee8)) { // +0x1ee8: current venue ID
    return;
  }
  if (local_4 == 0) {
    *(undefined4 *)(this + 0x1ee8) = 0;
    FUN_00908660(0x53504750, 0x56454e55, 0); // SPGP VENU - clear venue
    FUN_009085c0(0x53504750, 0x504f534e, this); // SPGP POSN - update position
    FUN_004086d0(&DAT_0112a5e0); // some cleanup/event
    return;
  }
  iVar2 = FUN_006b07e0(local_4); // get venue data by ID
  if (iVar2 == 0) {
    return;
  }
  *(int *)(this + 0x1ee8) = local_4;
  FUN_00908660(0x53504750, 0x56454e55, local_4); // SPGP VENU - set venue
  FUN_009085c0(0x53504750, 0x504f534e, this); // SPGP POSN - update position
  FUN_006ae3f0(); // venue transition effect/load
  iVar2 = *(int *)(*(int *)(iVar2 + 0x180) + 0xc4); // +0x180: venue type data, +0xc4: venue type enum
  if (iVar2 == 4) {
    cVar1 = FUN_00481620(); // check if player is in vehicle?
    if (cVar1 == '\0') goto LAB_0079f947;
    this = this + 0x2fc4; // offset for vehicle venue data
  } else {
    if ((iVar2 != 5) || (cVar1 = FUN_00481620(), cVar1 == '\0')) goto LAB_0079f947;
    this = this + 0x2fe4; // offset for another venue type
  }
  if (this != 0) {
    FUN_007fff40(this); // apply venue-specific data
  }
LAB_0079f947:
  FUN_00408680(&DAT_0112a5e0); // finalize/notify
  return;
}