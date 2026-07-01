// FUNC_NAME: ThreatEvaluator::updateReactionTimer
void __fastcall ThreatEvaluator::updateReactionTimer(int this) {
    int playerChar;
    int lookDirection;
    int targetChar;
    float dotProduct;
    int thresholdObj;
    
    // Conditions: reaction timer currently zero, local character exists, and character's type is not 0x48 (probably a vehicle or unique entity)
    if ((*(int *)(this + 0xAC)) == 0 &&
        (*(int *)(this + 0x50)) != 0 &&
        (playerChar = *(int *)(*(int *)(this + 0x50) + 0x70), playerChar != 0) &&
        playerChar != 0x48) {
        
        // Get pointers to three objects: likely player, target, and something else (maybe the player's look direction source)
        playerChar = FUN_00471610();  // get player character pointer
        lookDirection = FUN_00471610(); // get look direction source (e.g., camera or character's orientation)
        targetChar = FUN_00471610();  // get target character
        
        // Compute dot product: (lookDirection) dot (targetChar - playerChar)
        // lookDirection vector: (offset 0x20, 0x24, 0x28) - could be forward direction
        dotProduct = *(float *)(lookDirection + 0x24) * (*(float *)(targetChar + 0x34) - *(float *)(playerChar + 0x34)) +
                     *(float *)(lookDirection + 0x20) * (*(float *)(targetChar + 0x30) - *(float *)(playerChar + 0x30)) +
                     *(float *)(lookDirection + 0x28) * (*(float *)(targetChar + 0x38) - *(float *)(playerChar + 0x38));
        
        thresholdObj = FUN_008fa210(); // get a manager/object holding threshold and duration data
        if (thresholdObj != 0 &&
            *(float *)(thresholdObj + 0x5C) >= dotProduct &&  // if dot <= threshold (target not in front)
            dotProduct != *(float *)(thresholdObj + 0x5C)) {  // and not exactly equal (avoid edge case)
            // Set reaction timer to a value from threshold object's duration + global timer offset
            *(int *)(this + 0xAC) = *(int *)(thresholdObj + 0x60) + DAT_01205224;
            return;
        }
        // Otherwise set timer to 1 (immediate reaction or special flag)
        *(int *)(this + 0xAC) = 1;
    }
}