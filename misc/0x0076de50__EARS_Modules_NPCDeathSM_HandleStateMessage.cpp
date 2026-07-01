// Xbox PDB: EARS_Modules_NPCDeathSM_HandleStateMessage
// FUNC_NAME: PlayerSM::handleMissionMomentEvent
undefined1 __thiscall PlayerSM::handleMissionMomentEvent(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)

{
  int iVar1;
  float fVar2;
  float fVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  int local_54;
  undefined1 local_50 [76];
  
  uVar4 = 1;
  switch(param_5) {
  case 0x23: // MissionMomentEvent::EnterCombat
  case 0x24: // MissionMomentEvent::ExitCombat
    FUN_0076d880(); // PlayerSM::handleCombatTransition
    return 1;
  case 0x25: // MissionMomentEvent::EnterVehicle
    FUN_0076db20(); // PlayerSM::enterVehicle
    FUN_00733740(); // VehicleManager::registerPlayerVehicle
    return 1;
  case 0x26: // MissionMomentEvent::ExitVehicle
    iVar1 = this[0x17]; // +0x5c player data pointer
    if ((*(uint *)(iVar1 + 0x8e0) >> 0x14 & 1) != 0) { // check vehicle flag
      FUN_0076daf0(0); // PlayerSM::disableVehicleControl
      return 1;
    }
    if ((*(byte *)(this + 0x1d) & 2) != 0) { // check exiting vehicle state
      fVar2 = (float)*(int *)(iVar1 + 0x1d90); // vehicle exit speed
      if (*(int *)(iVar1 + 0x1d90) < 0) {
        fVar2 = fVar2 + DAT_00e44578;
      }
      local_54 = this[0x1c] - DAT_01205224; // player height offset
      fVar3 = (float)local_54;
      if (local_54 < 0) {
        fVar3 = fVar3 + DAT_00e44578;
      }
      FUN_009397e0(iVar1, fVar2 - fVar3, fVar2); // Physics::applyExitVelocity
      return 1;
    }
    break;
  case 0x27: // MissionMomentEvent::EnterCover
    FUN_007f6420(0x17); // CoverSystem::registerPlayer
    FUN_0076daf0(1); // PlayerSM::enableVehicleControl
    return 1;
  case 0x28: // MissionMomentEvent::ExitCover
    (**(code **)(*this + 0x2c))(0x7de371f1, 1, 1, 0, 0x3f800000, 0x3f800000); // InventoryAction::dropWeapon
    return 1;
  case 0x29: // MissionMomentEvent::Execute
    *(uint *)(this[0x17] + 0x1b94) = *(uint *)(this[0x17] + 0x1b94) & 0xffffffbf; // clear execution flag
    *(byte *)(this + 0x1d) = *(byte *)(this + 0x1d) | 4; // set executed flag
    return 1;
  case 0x2a: // MissionMomentEvent::GetHurt
    FUN_004df590(); // AudioManager::getVoiceChannel
    uVar5 = FUN_00471610(); // getRandomAudioID
    FUN_0044b4e0(local_50, uVar5); // formatAudioName
    uVar5 = FUN_0045c740(&local_54, "mm_hurt", local_50, 0x1ff, 0, 0, 0xffffffff, 0); // loadWwiseEvent
    FUN_00414db0(uVar5); // playAudioEvent
    if (local_54 != 0) {
      *(undefined4 *)(local_54 + 8) = 0; // mark as playing
      return 1;
    }
    break;
  case 0x2b: // MissionMomentEvent::VoiceoverDone
    FUN_004df590(); // AudioManager::freeVoiceChannel
    return 1;
  case 0x2c: // MissionMomentEvent::ObjectiveTrigger
    (**(code **)(*(int *)this[0x14] + 0x260))(); // MissionManager::triggerObjective
    return 1;
  default:
    uVar4 = FUN_0073e610(param_2, param_3, param_4, param_5, param_6); // handleGenericEvent
  }
  return uVar4;
}