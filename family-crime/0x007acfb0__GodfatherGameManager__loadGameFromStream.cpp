// FUNC_NAME: GodfatherGameManager::loadGameFromStream
void __thiscall GodfatherGameManager::loadGameFromStream(int thisPtr, undefined4 stream)
{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  
  FUN_0046c710(stream);
  FUN_0043aff0(stream,0xb3b90317);
  cVar2 = FUN_0043b120();
  while (cVar2 == '\0') {
    FUN_0043b210();
    uVar3 = FUN_0043ab70();
    switch(uVar3) {
    case 0:
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004089b0(thisPtr + 0xf8,uVar3);  // +0xF8: playerName
      break;
    case 1:
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004089b0(thisPtr + 0x100,uVar3);  // +0x100: familyName
      break;
    case 2:
      iVar4 = thisPtr + 0x114;  // +0x114: familyData
      FUN_0043b210(iVar4);
      FUN_0043ad10(iVar4);
      break;
    case 3:
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_00408980(thisPtr + 0x124,uVar3);  // +0x124: saveTimestamp
      break;
    case 4:
      iVar4 = FUN_0043b210();
      uVar1 = *(uint *)(iVar4 + 8);
      *(uint *)(thisPtr + 0x50) = uVar1;  // +0x50: gameFlags
      if ((uVar1 & 1) != 0) {
        FUN_00408680(thisPtr + 0x54);  // +0x54: playerMoney
        FUN_00408680(thisPtr + 0x5c);  // +0x5C: familyMoney
        FUN_00408680(thisPtr + 100);   // +0x64: reputation
        FUN_00408680(thisPtr + 0x6c);  // +0x6C: respect
        FUN_00408680(thisPtr + 0x74);  // +0x74: fear
        FUN_00408680(thisPtr + 0x7c);  // +0x7C: territoryCount
        FUN_00408680(thisPtr + 0x84);  // +0x84: racketCount
        FUN_00408680(thisPtr + 0x8c);  // +0x8C: compoundCount
        FUN_00408680(thisPtr + 0x94);  // +0x94: crewSize
        FUN_00408680(thisPtr + 0x9c);  // +0x9C: madeMenCount
        FUN_00408680(thisPtr + 0xa4);  // +0xA4: caposCount
        FUN_00408680(thisPtr + 0xac);  // +0xAC: underbossCount
        FUN_00408680(thisPtr + 0xb4);  // +0xB4: donCount
        FUN_00408680(thisPtr + 0xbc);  // +0xBC: totalKills
        FUN_00408680(thisPtr + 0xc4);  // +0xC4: totalArrests
        FUN_00408680(thisPtr + 0xcc);  // +0xCC: totalBribes
        FUN_00408680(thisPtr + 0xd4);  // +0xD4: totalAssassinations
        FUN_00408680(thisPtr + 0xdc);  // +0xDC: totalExtortions
        FUN_00408680(thisPtr + 0xe4);  // +0xE4: totalRobberies
        FUN_00408680(thisPtr + 0xec);  // +0xEC: totalFavors
      }
      break;
    case 5:
      iVar4 = FUN_0043b210();
      iVar4 = *(int *)(iVar4 + 8);
      *(int *)(thisPtr + 0x108) = iVar4;  // +0x108: currentChapter
      *(undefined1 *)(thisPtr + 0xf4) = 1;  // +0xF4: chapterUnlocked
      if ((((iVar4 == 5) || (iVar4 == 6)) || (iVar4 == 4)) ||
         (((iVar4 == 0x11 || (iVar4 == 0x12)) || (iVar4 == 0x13)))) {
        *(undefined1 *)(thisPtr + 0xf4) = 0;
      }
    }
    FUN_0043b1a0();
    cVar2 = FUN_0043b120();
  }
  if (DAT_0120e93c != 0) {
    FUN_00408900(thisPtr + 0x3c,&DAT_0120e93c,0x8000);  // +0x3C: saveDataBuffer
  }
  return;
}