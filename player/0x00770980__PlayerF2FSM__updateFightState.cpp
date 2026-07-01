// FUNC_NAME: PlayerF2FSM::updateFightState
void __thiscall PlayerF2FSM::updateFightState(int *this, undefined4 param_2)
{
  uint uVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  
  cVar3 = *(char *)(this[0x14] + 0x1b8c); // +0x1b8c: fightState
  uVar1 = this[0x25]; // +0x94: currentAttackType
  cVar2 = FUN_0076ec60(); // isPlayerInCombat?
  if (cVar3 == '\0') {
    iVar4 = this[0x22]; // +0x88: currentAction
    if (iVar4 == 7) {
LAB_00770e1c:
      iVar4 = -0x6a39d686;
      goto LAB_00770e33;
    }
    if (iVar4 != 3) {
      if ((iVar4 == 4) || (uVar5 = FUN_0084d420(iVar4), (uVar5 & 8) != 0)) {
        FUN_0046ffe0(this + 0x1e,0); // stopAnimation
        *(uint *)(this[0x14] + 0x1b94) = *(uint *)(this[0x14] + 0x1b94) | 8; // set flag
        if ((*(byte *)(this + 0x15) & 8) == 0) {
          FUN_007f4490(1,0,DAT_00d5ef90); // playSound
          *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 8;
        }
        iVar4 = -0x36690fee;
      }
      else {
        if ((this[0x22] == 6) || (uVar5 = FUN_0084d420(this[0x22]), (uVar5 & 0x40) != 0)) {
          iVar4 = 0x4b0744eb;
          goto LAB_00770e33;
        }
        if ((this[0x22] != 9) && (cVar3 = FUN_0084d420(this[0x22]), -1 < cVar3)) {
          if (this[0x22] == 0xb) goto LAB_00770e1c;
          if ((this[0x19] == 0) || (this[0x19] == 0x48)) {
LAB_00770ae7:
            iVar4 = this[0x14];
            if (((uVar1 == *(uint *)(iVar4 + 0x68c) >> 2) ||
                (uVar1 == *(uint *)(iVar4 + 0x6b4) >> 2)) ||
               (uVar1 == *(uint *)(iVar4 + 0x674) >> 2)) {
              FUN_007708f0(param_2,cVar2,0x92883cc1,0x1b7c7d5b);
              return;
            }
            if (((((((uVar1 != *(uint *)(iVar4 + 0x678) >> 2) &&
                    (uVar1 != *(uint *)(iVar4 + 0x6a0) >> 2)) &&
                   (uVar1 != *(uint *)(iVar4 + 0x67c) >> 2)) &&
                  ((uVar1 != *(uint *)(iVar4 + 0x680) >> 2 &&
                   (uVar1 != *(uint *)(iVar4 + 0x684) >> 2)))) &&
                 (uVar1 != *(uint *)(iVar4 + 0x688) >> 2)) &&
                ((uVar1 != *(uint *)(iVar4 + 0x6a4) >> 2 && (uVar1 != *(uint *)(iVar4 + 0x6a8) >> 2)
                 ))) && ((uVar1 != *(uint *)(iVar4 + 0x6ac) >> 2 &&
                         ((uVar1 != *(uint *)(iVar4 + 0x6b0) >> 2 &&
                          (uVar1 != *(uint *)(iVar4 + 0x670) >> 2)))))) {
              if ((((uVar1 != *(uint *)(iVar4 + 0x6b8) >> 2) &&
                   (uVar1 != *(uint *)(iVar4 + 0x66c) >> 2)) &&
                  (uVar1 != *(uint *)(iVar4 + 0x668) >> 2)) &&
                 (((uVar1 != *(uint *)(iVar4 + 0x664) >> 2 &&
                   (uVar1 != *(uint *)(iVar4 + 0x660) >> 2)) &&
                  (((uVar1 != *(uint *)(iVar4 + 0x69c) >> 2 &&
                    ((uVar1 != *(uint *)(iVar4 + 0x698) >> 2 &&
                     (uVar1 != *(uint *)(iVar4 + 0x694) >> 2)))) &&
                   (uVar1 != *(uint *)(iVar4 + 0x690) >> 2)))))) {
                return;
              }
              FUN_007708f0(param_2,cVar2,0x1b7c7d5b,0x412eb0db);
              return;
            }
            FUN_007708f0(param_2,cVar2,0x92883cc1,0x412eb0db);
            return;
          }
          if (this[0x19] == 0) {
            iVar4 = 0;
          }
          else {
            iVar4 = this[0x19] + -0x48;
          }
          iVar4 = FUN_006b1c70(iVar4,0x55859efa);
          if ((((iVar4 == 0) || (cVar3 = FUN_00690150(0x39), cVar3 == '\0')) || (this[0x22] != 1)
              ) || ((cVar2 == '\0' || (iVar6 = _rand(), 2 < iVar6 % 10)))) goto LAB_00770ae7;
          goto LAB_007709d7;
        }
        iVar4 = FUN_0045eea0();
        if (iVar4 == 0x576992f2) goto LAB_00770d67;
        iVar4 = 0x576992f2;
      }
LAB_00770d60:
      (**(code **)(*this + 0x2c))(iVar4,1,1,0,0x3f800000,0x3f800000); // playAnimation
LAB_00770d67:
      *(undefined1 *)(this[0x14] + 0x1e08) = 0; // +0x1e08: animationState
      return;
    }
    if ((this[0x17] == 0) || (this[0x17] == 0x48)) goto LAB_007709df;
    if (this[0x17] == 0) goto LAB_007709d2;
    iVar4 = this[0x17] + -0x48;
LAB_007709d7:
    FUN_0046fd90(iVar4,0); // setAnimationSpeed
  }
  else if ((cVar3 == '\x01') || (cVar3 == '\x04')) {
    bVar7 = cVar3 == '\x01';
    iVar4 = this[0x22];
    if (iVar4 != 3) {
      if ((iVar4 == 4) || (uVar5 = FUN_0084d420(iVar4), (uVar5 & 8) != 0)) {
        FUN_0046ffe0(this + 0x1e,0);
        if (bVar7) {
          *(uint *)(this[0x14] + 0x1b94) = *(uint *)(this[0x14] + 0x1b94) | 8;
        }
        if ((char)param_2 == '\0') {
          (**(code **)(*this + 0x2c))
                    ((-(uint)bVar7 & 0x40ab0377) + 0x1c3d42ce,1,1,0,0x3f800000,0x3f800000);
          *(undefined1 *)(this[0x14] + 0x1e08) = 1;
          return;
        }
        iVar4 = -0x36690fee;
      }
      else {
        if ((this[0x22] == 6) || (uVar5 = FUN_0084d420(this[0x22]), (uVar5 & 0x40) != 0)) {
          iVar4 = (-(uint)bVar7 & 0x462665f7) + 0x785bf53d;
          goto LAB_00770e33;
        }
        if ((this[0x22] != 9) && (cVar3 = FUN_0084d420(this[0x22]), -1 < cVar3)) {
          iVar4 = this[0x14];
          if ((uVar1 == *(uint *)(iVar4 + 0x68c) >> 2) ||
             ((uVar1 == *(uint *)(iVar4 + 0x6b4) >> 2 || (uVar1 == *(uint *)(iVar4 + 0x674) >> 2))))
          {
            iVar4 = (-(uint)bVar7 & 0x9089aec9) + 0xcb6b249e;
            iVar6 = (-(uint)bVar7 & 0x40ab0377) + 0x1c3d42ce;
          }
          else if ((((uVar1 == *(uint *)(iVar4 + 0x678) >> 2) ||
                    (uVar1 == *(uint *)(iVar4 + 0x67c) >> 2)) ||
                   (uVar1 == *(uint *)(iVar4 + 0x680) >> 2)) ||
                  ((uVar1 == *(uint *)(iVar4 + 0x684) >> 2 ||
                   (uVar1 == *(uint *)(iVar4 + 0x688) >> 2)))) {
            iVar4 = (-(uint)bVar7 & 0x98dc5577) + 0xa71dab76;
            iVar6 = (-(uint)bVar7 & 0xf3b00849) + 0x19d37946;
          }
          else if (((uVar1 == *(uint *)(iVar4 + 0x6a0) >> 2) ||
                   (uVar1 == *(uint *)(iVar4 + 0x6a4) >> 2)) ||
                  ((uVar1 == *(uint *)(iVar4 + 0x6a8) >> 2 ||
                   ((uVar1 == *(uint *)(iVar4 + 0x6ac) >> 2 ||
                    (uVar1 == *(uint *)(iVar4 + 0x6b0) >> 2)))))) {
            iVar4 = (-(uint)bVar7 & 0xf3b00849) + 0xd76434c1;
            iVar6 = (-(uint)bVar7 & 0x9b09f7) + 0xdff1daf1;
          }
          else {
            if (((((((uVar1 != *(uint *)(iVar4 + 0x670) >> 2) &&
                    (uVar1 != *(uint *)(iVar4 + 0x6b8) >> 2)) &&
                   (uVar1 != *(uint *)(iVar4 + 0x66c) >> 2)) &&
                  ((uVar1 != *(uint *)(iVar4 + 0x668) >> 2 &&
                   (uVar1 != *(uint *)(iVar4 + 0x664) >> 2)))) &&
                 ((uVar1 != *(uint *)(iVar4 + 0x660) >> 2 &&
                  ((uVar1 != *(uint *)(iVar4 + 0x69c) >> 2 &&
                   (uVar1 != *(uint *)(iVar4 + 0x698) >> 2)))))) &&
                (uVar1 != *(uint *)(iVar4 + 0x694) >> 2)) &&
               (uVar1 != *(uint *)(iVar4 + 0x690) >> 2)) {
              return;
            }
            iVar4 = (-(uint)bVar7 & 0x462665f7) + 0x785bf53d;
            iVar6 = (-(uint)bVar7 & 0x64b245c9) + 0x96d23f45;
          }
          FUN_007708f0(param_2,cVar2,iVar6,iVar4);
          return;
        }
        iVar4 = (-(uint)bVar7 & 0x462665f7) + 0x785bf53d;
      }
      goto LAB_00770d60;
    }
    if ((this[0x17] != 0) && (this[0x17] != 0x48)) {
      if (this[0x17] == 0) goto LAB_007709d2;
      iVar4 = this[0x17] + -0x48;
      goto LAB_007709d7;
    }
  }
  else {
    if (cVar3 != '\x02') {
      if (cVar3 != '\x03') {
        return;
      }
      goto LAB_00770e1c;
    }
    if (this[0x22] != 3) {
      if (this[0x22] != 6) {
        (**(code **)(*this + 0x2c))(0x854f637a,1,1,0,0x3f800000,0x3f800000);
        *(undefined1 *)(this[0x14] + 0x1e08) = 0;
        return;
      }
      (**(code **)(*this + 0x2c))(0x6d4224e5,1,1,0,0x3f800000,0x3f800000);
      *(undefined1 *)(this[0x14] + 0x1e08) = 0;
      return;
    }
    if ((this[0x17] != 0) && (this[0x17] != 0x48)) {
      if (this[0x17] == 0) {
LAB_007709d2:
        iVar4 = 0;
      }
      else {
        iVar4 = this[0x17] + -0x48;
      }
      goto LAB_007709d7;
    }
  }
LAB_007709df:
  if ((*(byte *)(this + 0x15) & 8) == 0) {
    FUN_007f4490(1,0,DAT_00d5ef90); // playSound
    *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 8;
  }
  iVar4 = -0x7e302ad7;
LAB_00770e33:
  (**(code **)(*this + 0x2c))(iVar4,1,1,0,0x3f800000,0x3f800000); // playAnimation
  *(undefined1 *)(this[0x14] + 0x1e08) = 0; // +0x1e08: animationState
  return;
}