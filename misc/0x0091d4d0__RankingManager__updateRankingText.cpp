// FUNC_NAME: RankingManager::updateRankingText
void __fastcall RankingManager::updateRankingText(int this)
{
  int *pRankingCount;
  int rankingCount;
  int loopCount;
  
  pRankingCount = (int *)(this + 0xc0); // +0xC0: pointer to ranking count
  if (*(int *)(this + 0xb4) + *(int *)(this + 0xc0) != 0) { // +0xB4: some offset, +0xC0: ranking count
    FUN_00402050(&DAT_011301c0,0); // likely a mutex lock or critical section
  }
  for (loopCount = *(int *)(this + 0xb4) + 10; loopCount != 0; loopCount = loopCount + -1) {
    rankingCount = *(int *)(this + 0xb4);
    if (((DAT_00e54d1c == '\0') && ((uint)(*pRankingCount + rankingCount) < 10)) && (1 < DAT_00e54d2c)) {
      if (DAT_00e54d2c < 6) {
        DAT_00e54d24 = 1;
      }
      else {
        DAT_00e54d24 = DAT_00e54d2c - 5;
      }
      DAT_00e54d20 = DAT_00e54d2c - 1;
      FUN_0091cd80(0,0); // likely updateRankingDisplay
    }
    FUN_0095c540(pRankingCount,rankingCount); // likely processRankingEntry
  }
  FUN_00918940(*(int *)(this + 0xb4) + *pRankingCount,*(undefined4 *)(this + 0xf0),0x80); // likely copyRankingData
  FUN_005a04a0("UpdateRankingText",0,&DAT_00d8510c,1,*(undefined4 *)(this + 0xf0)); // likely sendEvent or log
  return;
}