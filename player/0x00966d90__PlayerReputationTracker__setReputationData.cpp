// FUNC_NAME: PlayerReputationTracker::setReputationData
void __fastcall PlayerReputationTracker::setReputationData(int this) {
  int reputationList;
  
  reputationList = DAT_01129930; // global reputation list instance
  *(undefined4 *)(reputationList + 0x1b8) = *(undefined4 *)(this + 0x50); // +0x1b8 = reputation1
  FUN_0095cf20(); // updateReputationValues()
  *(undefined4 *)(reputationList + 0x1b0) = *(undefined4 *)(this + 0x54); // +0x1b0 = reputation2
  *(undefined4 *)(reputationList + 0x1dc) = *(undefined4 *)(this + 0x58); // +0x1dc = reputation3
  *(undefined4 *)(reputationList + 0x1cc) = *(undefined4 *)(this + 0x5c); // +0x1cc = reputation4
  *(undefined4 *)(reputationList + 0x1c8) = *(undefined4 *)(this + 0x60); // +0x1c8 = reputation5
  *(undefined1 *)(reputationList + 0x222) = *(undefined1 *)(this + 100);   // +0x222 = some flag/byte
  return;
}