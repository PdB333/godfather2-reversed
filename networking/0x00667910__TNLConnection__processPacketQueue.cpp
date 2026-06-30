// FUNC_NAME: TNLConnection::processPacketQueue
int TNLConnection::processPacketQueue(int *thisPtr)
{
  int result;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  int local_84 [3];
  byte *local_78;
  int local_74 [3];
  byte *local_68;
  int local_64 [3];
  byte *local_58;
  int local_54 [3];
  byte *local_48;
  int local_44 [3];
  byte *local_38;
  int local_34 [3];
  byte *local_28;
  int local_24 [3];
  byte *local_18;
  int local_14 [3];
  byte *local_8;
  
  // Check if connection is closed or not initialized
  if ((thisPtr[2] == 1) || (*thisPtr == 0)) {
    result = -3; // Connection error
  }
  else {
    // Check if there's data to send and the send buffer is ready
    if ((0 < *thisPtr) && ((*(byte *)thisPtr[3] & 1) != 0)) {
      result = FUN_00664cf0(); // sendPacket
      return result;
    }
    // Initialize packet queue iteration
    result = FUN_00667820(local_14,local_24,local_44,local_54,local_64,local_34,local_84,local_74,0);
    if (result == 0) {
      result = FUN_00665ce0(); // getNextPacket
      if ((result == 0) && (result = FUN_00665ce0(), result == 0)) {
        if ((local_14[0] < 1) ||
           ((((*local_8 & 1) != 0 || (local_24[0] < 1)) || ((*local_18 & 1) != 0)))) {
          result = FUN_00665ce0(); // getNextPacket
          if ((result == 0) && (result = FUN_00665ce0(), result == 0)) {
            FUN_0066a550(); // processAck
            FUN_0066a550(); // processAck
            do {
              bVar4 = local_44[0] == 0;
              while ((bVar4 || local_44[0] < 0 || ((*local_38 & 1) != 0))) {
                while ((0 < local_54[0] && ((*local_48 & 1) == 0))) {
                  result = FUN_00666240(local_54); // checkPacketFlag
                  if (((result != 0) ||
                      ((((0 < local_84[0] && ((*local_78 & 1) != 0)) ||
                        ((0 < local_74[0] && ((*local_68 & 1) != 0)))) &&
                       ((result = FUN_006657c0(local_84), result != 0 ||
                        (result = FUN_0066a780(local_74,local_14), result != 0)))))) ||
                     ((result = FUN_00666240(local_84), result != 0 ||
                      (result = FUN_00666240(local_74), result != 0)))) goto LAB_00667d13;
                }
                result = FUN_00665bd0(); // compareSequence
                if (result == -1) {
                  result = FUN_0066a780(local_54,local_44); // mergePackets
                  if ((result != 0) || (result = FUN_0066a780(local_84,local_64), result != 0))
                  goto LAB_00667d13;
                  piVar3 = local_74;
                  piVar2 = local_34;
                }
                else {
                  result = FUN_0066a780(local_44,local_54); // mergePackets
                  if ((result != 0) || (result = FUN_0066a780(local_64,local_84), result != 0))
                  goto LAB_00667d13;
                  piVar3 = local_34;
                  piVar2 = local_74;
                }
                result = FUN_0066a780(piVar3,piVar2); // mergePackets
                if (result != 0) goto LAB_00667d13;
                bVar4 = local_44[0] == 0;
                if (bVar4) {
                  result = FUN_00665c00(); // getNextPacket
                  if (result != 0) goto LAB_00667c8c;
                  result = FUN_00665c00(); // getNextPacket
                  goto joined_r0x00667ca4;
                }
              }
              result = FUN_00666240(local_44); // checkPacketFlag
            } while ((result == 0) &&
                    (((((local_64[0] < 1 || ((*local_58 & 1) == 0)) &&
                       ((local_34[0] < 1 || ((*local_28 & 1) == 0)))) ||
                      ((result = FUN_006657c0(local_64), result == 0 &&
                       (result = FUN_0066a780(local_34,local_14), result == 0)))) &&
                     ((result = FUN_00666240(local_64), result == 0 &&
                      (result = FUN_00666240(local_34), result == 0))))));
          }
        }
        else {
LAB_00667c8c:
          result = -3; // Connection error
        }
      }
      goto LAB_00667d13;
    }
  }
  return result;
joined_r0x00667ca4:
  if (result != -1) goto LAB_00667ccd;
  result = FUN_006657c0(local_84); // checkPacketFlag
  if (result != 0) goto LAB_00667d13;
  result = FUN_00665c00(); // getNextPacket
  goto joined_r0x00667ca4;
LAB_00667ccd:
  result = FUN_00665c30(); // getNextPacket
  while (result != -1) {
    result = FUN_0066a780(local_84,thisPtr); // mergePackets
    if (result != 0) goto LAB_00667d13;
    result = FUN_00665c30(); // getNextPacket
  }
  FUN_00666970(); // finalizePacketProcessing
  result = 0;
LAB_00667d13:
  FUN_00665b80(local_14,local_24,local_44,local_54,local_64,local_34,local_84,local_74,0); // cleanupPacketQueue
  return result;
}