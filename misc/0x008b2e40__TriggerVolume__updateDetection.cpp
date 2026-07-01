// FUNC_NAME: TriggerVolume::updateDetection
void __thiscall TriggerVolume::updateDetection(int thisPtr, undefined4 point, int entityId)
{
  int shape;
  uint distance;
  char isPlayer;
  int globalPtr;
  
  // If no shape allocated yet, create one using data at this+0x64
  if (*(int *)(thisPtr + 0x74) == 0) {
    *(int *)(thisPtr + 0x74) = FUN_00446100(thisPtr + 0x64, 0); // allocateShape(data, 0)
  }
  
  shape = *(int *)(thisPtr + 0x74);
  if (shape != 0) {
    // Compute distance metric from point to shape
    distance = FUN_00895d80(point, entityId, 0xffffffff,
                           *(undefined4 *)(shape + 0x50),    // shape center/offset
                           *(undefined4 *)(shape + 0x64),    // shape radius/param
                           *(undefined4 *)(shape + 0x68),    // shape extent2
                           *(undefined4 *)(shape + 0x6c));   // shape extent3
    // Check if distance is within the activation range [minDist, maxDist]
    if (distance >= *(uint *)(thisPtr + 0x78) && distance <= *(uint *)(thisPtr + 0x7c)) {
      // Get global game manager pointer
      globalPtr = **(int **)(DAT_012233a0 + 4);
      if (globalPtr != 0 && globalPtr != 0x1f30) {
        // Check if entityId matches the object ID stored 0x38 bytes before globalPtr
        if (*(int *)(globalPtr - 0x38) == entityId) {
          isPlayer = FUN_00481620(); // isPlayerCharacter()
          if (isPlayer != '\0') {
            FUN_007a3760(thisPtr + 0x80); // triggerActivation(this+0x80)
          }
        }
      }
    }
  }
}