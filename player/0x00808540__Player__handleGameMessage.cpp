// FUNC_NAME: Player::handleGameMessage
// Address: 0x00808540
// Role: Main message dispatch handler for Player objects. Processes a packet (message) containing an ID and optional data, 
//       and performs actions such as weapon switching, state changes, animation playback, and interactions.

void __thiscall Player::handleGameMessage(int *message)
{
  int msgId;
  char *payload;
  int dataPtr;
  int localVar1, localVar2;
  bool boolFlag;
  float vec3[3];
  undefined4 unkData0, unkData1;

  msgId = *message;

  // --- Handle specific known message IDs (global variables used as message type constants) ---

  // DAT_0112d94c - likely "startCombat" or "aggressiveMode"
  if (g_MessageStartCombat == msgId) {
    if ((this->field_fdc != 1) && (this->field_374 != 0)) {
      DEBUG_PRINT(4);                                // debug logging
      freeMessage(message);
      return;
    }
    goto DONE;
  }

  // DAT_0112c9b4 - likely "stopCombat"
  if (g_MessageStopCombat == msgId) {
    if (this->field_374 != 0) {
      DEBUG_PRINT(0x400);
      freeMessage(message);
      return;
    }
    goto DONE;
  }

  // DAT_0112d860 - "decrementCounter" or "useCharge"
  if (g_MessageDecrementCharge == msgId) {
    if (this->field_5c0 != 0) {
      this->field_5c0--;
    }
    if (this->field_5c0 == 0) {
      this->flags &= 0xFFF9FFFF;                    // clear bit 18 and 19
      freeMessage(message);
      return;
    }
    this->flags |= 0x60000;                         // set bits 18 and 19
    freeMessage(message);
    return;
  }

  // DAT_0112c82c - "toggleSomething"
  if (g_MessageToggleFlag1 == msgId) {
    if (this->field_1e34 != 0) {
      FUN_004df600();                               // called when condition met
      freeMessage(message);
      return;
    }
    goto DONE;
  }

  // DAT_0112d954 - "setAttachment" or "equipItem"
  if (g_MessageSetAttachment == msgId) {
    payload = (char *)message[1];
    if (*payload == 4) {
      this->field_1e80 = *(int *)(*(int *)(payload + 4) + 0x1c); // copy some object data
    }
    dataPtr = *(int *)(payload + 4);
    adjustAttachment(*(undefined1 *)(dataPtr + 4), *(int *)(dataPtr + 0xc) + 1,
                     1 << ((char)*(int *)(dataPtr + 0x14) - 1U & 0x1f)); // set bone attachment
    freeMessage(message);
    return;
  }

  // DAT_0112c81c - "playSound"
  if (g_MessagePlaySound == msgId) {
    FUN_007f7e00(*(undefined1 *)(*(int *)(message[1] + 4) + 4)); // play a sound from data
    freeMessage(message);
    return;
  }

  // DAT_0112ca64 - "adjustAttachmentAlt"
  if (g_MessageAdjustAttachment == msgId) {
    dataPtr = *(int *)(*(int *)(message[1] + 4) + 4);
    adjustAttachment(*(undefined1 *)(dataPtr + 4), *(int *)(dataPtr + 0xc) + 1, 10);
    freeMessage(message);
    return;
  }

  // DAT_0112c97c - "setFlag1"
  if (g_MessageSetFlag4000000 == msgId) {
    this->flags |= 0x4000000;
    freeMessage(message);
    return;
  }

  // DAT_0112c844 - "clearFlag1"
  if (g_MessageClearFlag4000000 == msgId) {
    this->flags &= 0xFBFFFFFF;
    freeMessage(message);
    return;
  }

  // DAT_0112c9a4 - "vtableCall264"
  if (g_MessageCallVtable264 == msgId) {
    (this->vtable->method264)();                     // virtual dispatch via vtable at -0x3c
    freeMessage(message);
    return;
  }

  // DAT_0112d91c - "vtableCall25C"
  if (g_MessageCallVtable25C == msgId) {
    (this->vtable->method25C)();
    freeMessage(message);
    return;
  }

  // DAT_0112c95c - "vtableCall260"
  if (g_MessageCallVtable260 == msgId) {
    (this->vtable->method260)();
    freeMessage(message);
    return;
  }

  // DAT_0112d92c - "weaponSwitch" or "setWeapon"
  if (g_MessageWeaponSwitch == msgId) {
    if ((message[1] != 0) && (dataPtr = *(int *)(message[1] + 4), dataPtr != 0)) {
      int weaponType = *(int *)(dataPtr + 4);       // 0 for left, 1 for right
      if ((*(int **)(g_GlobalPlayer + 4) != 0) && (*(int **)(g_GlobalPlayer + 4) != 0x1f30)) {
        FUN_00799b20();
        bool canEquip = FUN_004209a0();
        if (canEquip == 0) {
          FUN_007ff050(0);                           // disable input maybe
          int *weaponSlot = &this->field_1e60;          // current weapon slot pointer
          undefined4 result = FUN_00799b20(0,0,0,0);
          result = FUN_00856780(result);
          FUN_006906e0(result);
          if ((*weaponSlot != 0) && (*weaponSlot != 0x48)) {
            int baseWeapon = *weaponSlot;
            int weaponObj;
            const char *slotName;
            if (weaponType == 0) {   // left weapon
              weaponObj = (baseWeapon == 0) ? 0 : (int)(baseWeapon - 0x48);
              slotName = "l_weapon";
            } else {                 // right weapon
              weaponObj = (baseWeapon == 0) ? 0 : (int)(baseWeapon - 0x48);
              slotName = "r_weapon";
            }
            (this->vtable->attachToBone)(slotName, 0);   // attach weapon model
            // Call various weapon setup functions
            if (*weaponSlot == 0) {
              weaponObj = 0;
            } else {
              weaponObj = *weaponSlot - 0x48;
            }
            (weaponObj->vtable->setupWeapon)();
            FUN_007091d0();                         // some weapon state update
            if (*weaponSlot == 0) {
              weaponObj = 0;
            } else {
              weaponObj = *weaponSlot - 0x48;
            }
            (weaponObj->vtable->postAttach)(this);
            if (*weaponSlot == 0) {
              (0->vtable->method160)(0);             // null check, probably does nothing
            } else {
              ( (*weaponSlot - 0x48) -> vtable->finalizeWeapon)(0);
            }
          }
        }
      }
    }
    goto DONE;
  }

  // DAT_0112d914 - "disableInput"
  if (g_MessageDisableInput == msgId) {
    FUN_007ff050(0);
    goto DONE;
  }

  // DAT_0112c824 - "handleTarget" or "focus"
  if (g_MessageFocusTarget == msgId) {
    if ((message[1] != 0) && (dataPtr = *(int *)(message[1] + 4), dataPtr != 0)) {
      if ((dataPtr = *(int *)(dataPtr + 4), dataPtr != 0)) {
        undefined4 targetObj = FUN_004dafd0(dataPtr);
        FUN_007ff260(targetObj);
      }
    }
    goto DONE;
  }

  // DAT_0112d90c - "setInputMode1" ?
  if (g_MessageSetInputMode1 == msgId) {
    // fall through to disableInput? actually it seems to set input mode 0
    // But the structure: after checking DAT_0112d90c, there is no separate action, it jumps to outside.
    // Actually the code does: if (iVar8 != DAT_0112d914) { then handle other stuff } else { FUN_007ff050(0); }
    // So DAT_0112d90c is actually handled at the end by the same path? Let's keep it as fallthrough.
  }

  // DAT_0112c964 - "setInputMode2"
  if (g_MessageSetInputMode2 == msgId) {
    FUN_007ff050(2);
    goto DONE;
  }

  // DAT_0112d9ec - "setInputMode1"
  if (g_MessageSetInputMode1_alt == msgId) {
    FUN_007ff050(1);
    goto DONE;
  }

  // DAT_0112d944 - "setVibrationMode"
  if (g_MessageSetVibration == msgId) {
    uint flags = CONCAT31((uint3)(this->field_7e4 >> 0xf), ~(byte)(this->field_7e4 >> 7)) & 0xFFFFFF01;
    if (message[1] != 0) {
      int vibMode = *(int *)(*(int *)(message[1] + 4) + 4);
      undefined4 vibParams = (flags >> 8) & 0xFFFFFF;
      char flagsLow = (char)flags;
      if (vibMode == 0) {
        FUN_007f04d0(0);
        undefined4 result = CONCAT31(vibParams, flagsLow == 0);
        FUN_007f04a0(result);
        FUN_007f4f20(result);
        FUN_007f5000(0);
      } else if (vibMode == 1) {
        FUN_007f04d0(0);
        FUN_007f04a0(1);
        FUN_007f4f20(1);
        FUN_007f5000(0);
      } else if (vibMode == 2) {
        undefined4 result = CONCAT31(vibParams, flagsLow == 0);
        FUN_007f04a0(result);
        FUN_007f04d0(1);
        FUN_007f5000(1);
        FUN_007f4f20(result);
      }
    }
    goto DONE;
  }

  // DAT_0112d93c - "checkAndCallVtable268"
  if (g_MessageCheckCallVtable268 == msgId) {
    char result = FUN_00481620();
    if (result != 0) {
      (this->vtable->method268)();
    }
    goto DONE;
  }

  // --- Group of generic message IDs that trigger a sound/effect via FUN_006fbc40 + FUN_007f96a0 ---
  if ((msgId == g_MessageGenericSound1) || (msgId == g_MessageGenericSound2) ||
      (msgId == g_MessageGenericSound3) || (msgId == g_MessageGenericSound4) ||
      (msgId == g_MessageGenericSound5) || (msgId == g_MessageGenericSound6) ||
      (msgId == g_MessageGenericSound7) || (msgId == g_MessageGenericSound8)) {
    unkData0 = 0;
    unkData1 = FUN_006fbc40(0,0);
    FUN_007f96a0(unkData0, 0, unkData1, 0);
    FUN_006fbc70();
  }

  // DAT_0112d8e4 - "playSound2"
  else if (msgId == g_MessagePlaySound2) {
    FUN_007f7e00(*(undefined1 *)(*(int *)(message[1] + 4) + 4));
    goto DONE;
  }

  // DAT_0112d8dc - "triggerAnimation" or "setAnimationFlag"
  else if (msgId == g_MessageTriggerAnimation) {
    byte *array = (byte *)message[1];
    int animParam = 0;
    if (1 < *array) {
      animParam = *(int *)(*(int *)(array + 4) + 0xc);
    }
    int dataPtr2 = *(int *)(*(int *)(array + 4) + 4);
    if (dataPtr2 == 0) goto DONE;
    bool boolFlag = (animParam != 0);
    // Fall through to common animation call at the end
  }

  // --- More messages handled via vtable calls ---
  else if (msgId == g_MessageSetFlag2 || msgId == g_MessageSetFlag3 ||
           msgId == g_MessageSetFlag4 || msgId == g_MessageSetFlag5 ||
           msgId == g_MessageSetFlag6 || msgId == g_MessageSetFlag7) {
    int dataPtr2 = *(int *)(*(int *)(message[1] + 4) + 4);
    if (dataPtr2 == 0) goto DONE;
    // Determine if it's from a specific group
    if (((msgId == g_MessageSetFlag4) || (msgId == g_MessageSetFlag5)) ||
       ((msgId == g_MessageSetFlag6) || (boolFlag = false, msgId == g_MessageSetFlag7))) {
      boolFlag = true;
    }
    // Then call vtable method 0x2e8
    (this->vtable->method2E8)(boolFlag, dataPtr2);
  }

  // DAT_0112c834, DAT_0112ca6c, DAT_0112d8f4 - "setProperty" or "applyValue"
  else if ((msgId == g_MessageSetProperty1) || (msgId == g_MessageSetProperty2) || (msgId == g_MessageSetProperty3)) {
    int value = *(int *)(*(int *)(message[1] + 4) + 4);
    if (value != 0) {
      (this->vtable->method2D0)(value);
    }
    goto DONE;
  }

  // DAT_0112d924 - "playBark" or "voiceLine"
  else if (msgId == g_MessagePlayBark) {
    FUN_007f63e0(0x23);
    goto DONE;
  }

  // DAT_0112c994 - "playBarkAlt"
  else if (msgId == g_MessagePlayBarkAlt) {
    FUN_007f63e0(0x24);
    goto DONE;
  }

  // DAT_0112c854 - "setAnimationBool"
  else if (msgId == g_MessageSetAnimationBool) {
    (this->vtable->method234)(*(undefined1 *)(*(int *)(message[1] + 4) + 4), 1);
    goto DONE;
  }

  // DAT_0112c99c - "playBark3"
  else if (msgId == g_MessagePlayBark3) {
    FUN_007f63e0(0x33);
    goto DONE;
  }

  // DAT_0112c83c - "callVtable1F0"
  else if (msgId == g_MessageCallVtable1F0) {
    (this->vtable->method1F0)();
    goto DONE;
  }

  // DAT_0112c954 - "setValueVtable500" (offset 500 = 0x1F4)
  else if (msgId == g_MessageSetValue500) {
    (this->vtable->method500)(*(int *)(*(int *)(message[1] + 4) + 4));
    goto DONE;
  }

  // DAT_0112d934 - "setPlayerTarget" or "setFocus"
  else if (msgId == g_MessageSetPlayerTarget) {
    char result = FUN_00690150(0x68);
    if (result == 0) {
      undefined4 targetId = *(int *)(*(int *)(message[1] + 4) + 4);
      this->field_1b90 = targetId;
      FUN_007fbdf0(targetId);
      if (this->field_1b8c != 0) {
        FUN_007f04d0(0);
      }
    }
    goto DONE;
  }

  // DAT_0112c9ac - "useLeftWeaponAction"
  else if (msgId == g_MessageUseLeftWeapon) {
    if ((this->field_1e60 != 0) && (this->field_1e60 != 0x48)) {
      // both cases call same function, but different indices? it's the same call.
      FUN_00709120();                  // likely "fireLeftWeapon"
    }
    goto DONE;
  }

  // DAT_0112d8fc - "useRightWeaponAction"
  else if (msgId == g_MessageUseRightWeapon) {
    if ((this->field_1e60 != 0) && (this->field_1e60 != 0x48)) {
      FUN_007073b0();                  // likely "fireRightWeapon"
    }
    goto DONE;
  }

  // DAT_0120e93c - "specialAction"
  else if (msgId == g_MessageSpecialAction) {
    (this->vtable->method2EC)();
    FUN_007f85a0();                    // some cleanup
    goto DONE;
  }

  // Dynamic message IDs stored in the object (likely for custom events)
  else if (msgId == this->field_1cac) {
    this->flags |= 0x100;
    FUN_009c4ea0(1);                   // enable something
    goto DONE;
  }
  else if (msgId == this->field_1cb4) {
    this->flags &= 0xFFFFFEFF;
    FUN_009c4ea0(0);
    goto DONE;
  }
  else if (msgId == this->field_1cbc) {
    this->flags |= 0x40;
    goto DONE;
  }
  else if (msgId == this->field_1cc4) {
    this->flags |= 0x20;
    goto DONE;
  }
  else if (msgId == this->field_1ccc) {
    char result = FUN_007fd640();
    if (result == 0) {
      FUN_007fbe90();                  // some action
    }
    goto DONE;
  }
  else if (msgId == this->field_1cd4) {
    char result = FUN_007fd640();
    if (result == 0) {
      FUN_007fbe50();                  // opposite action
    }
    goto DONE;
  }

  // DAT_0112d9e4 - "proximityCheck"
  else if (msgId == g_MessageProximityCheck) {
    int data = message[1];
    getPosition(&vec3[0]);             // get own position
    int entity = FUN_00471610();        // get some entity
    vec3[0] = *(float *)(entity + 0x30) - vec3[0];
    vec3[1] = *(float *)(entity + 0x34) - vec3[1];
    vec3[2] = *(float *)(entity + 0x38) - vec3[2];
    float distSq = vec3[0]*vec3[0] + vec3[1]*vec3[1] + vec3[2]*vec3[2];
    if ((distSq < *(float *)(data + 0x4c)) &&
        ((float10)(this->vtable->methodC0)() > 0.0f)) {
      FUN_007fbf70(data + 4, *(int *)(data + 0x48), *(int *)(data + 0x50), *(int *)(data + 0x54));
    }
    goto DONE;
  }

  // DAT_0112d9d4 - "startSequence"
  else if (msgId == g_MessageStartSequence) {
    char result = FUN_007fd640();
    if (result != 0) {
      this->field_fed = 0;
      (this->vtable->method198)();      // start sequence
      this->field_1edc = 1;
    }
    goto DONE;
  }

  // DAT_0112c9c4 - "endSequence" or "stopCutscene"
  else if (msgId == g_MessageEndSequence) {
    char result = FUN_007fd640();
    if (result != 0) {
      this->field_1ed8 = 0;
      this->field_1edc = 0;
      int weaponObj = (this->field_fc0 == 0) ? 0 : (int)(this->field_fc0 - 0x48);
      weaponObj = FUN_006b1c70(weaponObj, 0x55859efa);
      if ((weaponObj != 0) && (result = FUN_007fd640(), result != 0)) {
        int data = message[1];
        this->field_fed = 1;
        undefined4 endingId = (data != 0 && (*(int *)(data + 4) != 0)) ? *(int *)(*(int *)(data + 4) + 4) : g_DefaultEndingId;
        this->field_fe0 = endingId;
        this->field_fe4 = endingId;
        this->field_1020 = endingId;
        this->field_101c = endingId;
      }
      (this->vtable->method2F4)();
    }
    goto DONE;
  }

  // DAT_0112edf4 / DAT_0112ef7c - "crosshairAction" or "aim assist"
  else if ((msgId == g_MessageCrosshairAction1) || (msgId == g_MessageCrosshairAction2)) {
    int *data = (int *)message[1];
    if ((data != 0) && (this->field_1ebc == *data) && (this->field_1ed0 != 0)) {
      FUN_00805c00(CONCAT31((int3)((uint)data >> 8), (msgId == g_MessageCrosshairAction1) ? 1 : 0));
    }
    goto DONE;
  }

  // DAT_0112f1dc - "respawn" or "teleport"
  else if (msgId == g_MessageRespawn) {
    char result = FUN_00481620();
    if (result != 0) {
      int playerIndex = *(int *)(g_SomeGlobal + 0x40);
      if ((g_CurrentPlayerObject != 0) && (*(int *)(g_CurrentPlayerObject + 0x378) != -1)) {
        FUN_007f8750(*(int *)(g_CurrentPlayerObject + 0x378));
      }
      if (playerIndex != 0) {
        FUN_008afb10(this);
      }
    }
    goto DONE;
  }

  // DAT_01131028 - "useAbility" or "activatePower"
  else if (msgId == g_MessageActivateAbility) {
    char result = FUN_00690150(0xc);
    if (result != 0) {
      FUN_007f63e0(0xd);
    }
    goto DONE;
  }

  // DAT_01131020 - "interactWithObject" (complex handler)
  else if (msgId == g_MessageInteract) {
    dataPtr = *(int *)(message[1] + 4);
    if (((dataPtr == 0) || (dataPtr == 0x48)) || 
        ((dataPtr = *(int *)(message[1] + 4), dataPtr == 0) || 
         (dataPtr = dataPtr - 0x48, dataPtr == 0))) goto DONE;
    int objType = FUN_00713340(dataPtr, 0x369ac561);
    if (objType != 0) {
      FUN_007fff40(this + 0x1ca4);
      int *somePtr = (int *)FUN_00726870(dataPtr);
      if (((somePtr == (int *)0x0) || (FUN_006eb940() == 0)) ||
          ((somePtr->vtable->method1C)(0x100) == 0)) {
        // handle different sub-types
        int subType = FUN_00806440();
        if (subType == 2) {
          unkData1 = 0;
          unkData0 = FUN_006fbc40(0,0);
          FUN_007f96a0(0xE0832B4F, 0, unkData0, unkData1);
          FUN_006fbc70();
        } else if (subType == 3) {
          unkData1 = 0;
          unkData0 = FUN_006fbc40(0,0);
          FUN_007f96a0(0xEE3D80D9, 0, unkData0, unkData1);
          FUN_006fbc70();
        } else {
          unkData0 = 0;
          subType = FUN_00806440();
          if (subType == 0) {
            if ((*(byte *)(objType + 0x1f54) & 1) == 0) {
              unkData1 = FUN_006fbc40(0,0);
              FUN_007f96a0(0xC6BFCCD2, 0, unkData1, unkData0);
            } else {
              unkData1 = FUN_006fbc40(0,0);
              FUN_007f96a0(0x14ADEDD1, 0, unkData1, unkData0);
            }
            FUN_006fbc70();
          } else {
            unkData1 = FUN_006fbc40(0,0);
            FUN_007f96a0(0x4EA55B08, 0, unkData1, unkData0);
            FUN_006fbc70();
          }
        }
      } else {
        unkData1 = 0;
        unkData0 = FUN_006fbc40(0,0);
        FUN_007f96a0(0x6D05D4B6, 0, unkData0, unkData1);
        FUN_006fbc70();
      }
      goto DONE;
    }
    // If not that type, try another
    dataPtr = FUN_006dc8e0(dataPtr, 0x383225a1);
    if (dataPtr == 0) goto DONE;
    unkData1 = 0;
    unkData0 = FUN_006fbc40(0,0);
    unkData0 = 0xC8F78536;  // Note: this overwrites unkData0, likely a bug in decompilation? Actually it sets unkData0 to a hash.
    // Then call the generic sound function
    FUN_007f96a0(0xC8F78536, 0, unkData0, unkData1); // note: unkData0 is reused incorrectly? Might be a variable confusion.
    FUN_006fbc70();
    goto DONE;
  }

  // DAT_012067dc - "anotherAction"
  else if (msgId == g_MessageAnotherAction) {
    FUN_00625030();
    goto DONE;
  }

  // Default: just goto DONE (no action)

DONE:
  freeMessage(message);
  return;
}