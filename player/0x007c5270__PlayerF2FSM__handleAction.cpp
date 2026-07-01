// FUNC_NAME: PlayerF2FSM::handleAction
undefined1 __thiscall PlayerF2FSM::handleAction(int this, undefined4 param2, undefined4 param3, undefined4 param4, int actionId, undefined4 param6)
{
  float fVar1;
  float fVar2;
  char cVar3;
  undefined1 uVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint *puVar9;
  undefined4 uVar10;

  uVar4 = 1;
  switch(actionId + -0x31) {
  case 0: // Action 0x31
    break;
  case 1: // Action 0x32 - UseItem? 
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      FUN_007f6420(0x33); // showContextHint(0x33)
      return 1;
    }
    break;
  case 2: // Action 0x33 - HideItem?
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      FUN_007f63e0(0x33); // hideContextHint(0x33)
      return 1;
    }
    break;
  case 3: // Action 0x34 - Pick up object
    iVar6 = FUN_006252f0(); // getCurrentWeapon()
    iVar8 = FUN_007ab710(); // getLocalPlayer()
    if ((iVar8 != 0) && (cVar3 = FUN_00690150(0x33), cVar3 != '\0')) { // isObjectInteractable(0x33)
      FUN_007c4fa0(); // playPickupAnimation()
      FUN_007f6420(0x33); // showContextHint(0x33)
      if (iVar6 != 0x43) { // if not custom weapon
        FUN_0079f100(0xd,0); // playPickupSound(0xd,0)
        return 1;
      }
      FUN_0079f100(0xc,0); // playPickupSound(0xc,0)
      return 1;
    }
    break;
  case 4: // Action 0x35 - Throw/Punch/Hit something
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      iVar6 = FUN_006bc8d0(iVar6,0x369ac561); // getComponent(0x369ac561 - combat knowledge component)
      iVar8 = FUN_006ad770(iVar6); // getCombatTarget(iVar6)
      if ((iVar6 != 0) && (iVar8 != 0)) { // has target
        iVar6 = *(int *)(iVar8 + 0x1c); // target's combat state
        if ((iVar6 != 0) && (iVar6 != 0x3c)) { // not dead or invalid? (0x3c = 60 = dead)
          if (*(int *)(this + 0x90) == 0) { // if not in aiming state?
            uVar7 = *(undefined4 *)(iVar6 + 0x40); // get attack animation
          }
          else {
            uVar7 = *(undefined4 *)(iVar6 + 0x44); // get aimed attack animation
          }
          FUN_0078b270(3); // startMeleeAttack(3)
          FUN_0078b4b0(uVar7,1,1); // playAnimation(uVar7,1,1)
        }
        cVar3 = FUN_00732380(); // isLocalPlayerStealing?
        if (cVar3 != '\0') {
          uVar10 = 0;
          uVar7 = FUN_006fbc40(0,0); // beginSoundScope?
          FUN_007f96a0(0x3f77b494,100,uVar7,uVar10); // postEvent(0x3f77b494,100,...) - stealing sound
          FUN_006fbc70(); // endSoundScope()
          piVar5 = (int *)FUN_006ad7f0(*(undefined4 *)(this + 0x58)); // getControlledEntity
          (**(code **)(*piVar5 + 0x28))(0xf0ec4992,0,0xffffffff,0); // entity.sendEvent(0xf0ec4992,...) - start stealing
          cVar3 = FUN_0078a7d0(); // isPickpocketComplete?
          if (cVar3 != '\0') {
            uVar10 = 0;
            uVar7 = FUN_006fbc40(0,0); // beginSoundScope()
            FUN_007f96a0(0x76061e92,100,uVar7,uVar10); // postEvent(0x76061e92,100,...) - stolen sound
            FUN_006fbc70(); // endSoundScope()
            return 1;
          }
        }
      }
    }
    break;
  case 5: // Action 0x36 - Crouch
    FUN_007c5070(); // toggleCrouch()
    return 1;
  case 6: // Action 0x37 - Heavy attack / execute?
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      iVar6 = FUN_006bc8d0(iVar6,0x369ac561); // getCombatKnowledge()
      iVar8 = FUN_006ad770(iVar6); // getCombatTarget()
      if (((iVar6 != 0) && (iVar8 != 0)) &&
         ((iVar6 = *(int *)(iVar8 + 0x1c), iVar6 != 0 &&
          ((iVar6 != 0x3c && // target alive
           (iVar8 = FUN_007ab150(), fVar2 = DAT_012067e8, *(float *)(iVar8 + 0x38) <= 0.0)))))) {
             // player not sprinting
        fVar1 = *(float *)(iVar6 + 0x48); // get attack multiplier
        FUN_0078b270(10); // startHeavyAttack(10)
        FUN_0078b4b0(fVar2 * fVar1,1,1); // playAnimation with scaled speed
        return 1;
      }
    }
    break;
  case 7: // Action 0x38 - Use/Interact
    iVar6 = *(int *)(this + 0x58); // currentInteractable
    iVar8 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      uVar7 = 0;
      if (*(int *)(this + 0x90) == 0) {
        uVar10 = FUN_006fbc40(0,0); // beginSoundScope()
        FUN_007f96a0(0,0,uVar10,uVar7); // postEvent(0,0,...) - silent?
      }
      else {
        uVar10 = FUN_006fbc40(0,0); // beginSoundScope()
        FUN_007f96a0(0,0,uVar10,uVar7); // postEvent(0,0,...)
      }
      FUN_006fbc70(); // endSoundScope()
    }
    if (iVar8 != 0) {
      uVar7 = 0;
      if (*(int *)(this + 0x90) != 0) {
        uVar10 = FUN_006fbc40(0,0); // beginSoundScope()
        FUN_007f96a0(0,0,uVar10,uVar7); // postEvent(0,0,...)
        FUN_006fbc70(); // endSoundScope()
        return 1;
      }
      uVar10 = FUN_006fbc40(0,0); // beginSoundScope()
      FUN_007f96a0(0,0,uVar10,uVar7); // postEvent(0,0,...)
      FUN_006fbc70(); // endSoundScope()
      return 1;
    }
    break;
  case 8: // Action 0x39 - Toggle something
    puVar9 = (uint *)(*(int *)(this + 0x58) + 0x249c); // +0x249c is a flag field
    *puVar9 = *puVar9 | 0x400; // set flag 0x400
    return 1;
  case 9: // Action 0x3a
    FUN_006901e0(10); // somethingWithIndex(10)
    return 1;
  case 10: // Action 0x3b
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      FUN_007fb9b0(6,_DAT_00d5c458); // selectWeapon(6, someWeaponId)
      return 1;
    }
    break;
  case 0xb: // Action 0x3c
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (iVar6 != 0) {
      FUN_007fb9b0(6,_DAT_00d6e6a4); // selectWeapon(6, anotherWeaponId)
      return 1;
    }
    break;
  case 0xc: // Action 0x3d - Pickpocket
    iVar6 = FUN_007ab710(); // getLocalPlayer()
    if (((iVar6 != 0) && (iVar6 = FUN_006ad770(iVar6), iVar6 != 0)) && // getCombatTarget
       (cVar3 = FUN_0078a7d0(), cVar3 != '\0')) { // pickpocketComplete?
      uVar10 = 0;
      uVar7 = FUN_006fbc40(0,0); // beginSoundScope()
      FUN_007f96a0(0xf12a7fc1,100,uVar7,uVar10); // postEvent(0xf12a7fc1,100,...) - pickpocket success sound
      FUN_006fbc70(); // endSoundScope()
      return 1;
    }
    break;
  default:
    uVar4 = FUN_007abec0(param2,param3,param4,actionId,param6); // default handler
  }
  return uVar4;
}