// FUNC_NAME: TargetingManager::findNearestTarget
undefined4 __fastcall TargetingManager::findNearestTarget(TargetingManager* this) {
    // +0x10 = pointer to array of entity pointers (target list)
    // +0x14 = count of entries in the list
    // Entity offsets: +0x100 = posX, +0x104 = posY, +0x108 = posZ, +0x110 = detectionRadius (squared)

    float dx, dy, dz;
    int squaredRadius;
    int playerIndex = 0;
    int* currentArrayEntry;
    float distanceSquared;
    float diffX, diffY, diffZ;

    if (this->targetCount != 0 && 
        *(int**)**(int**)(DAT_012233a0 + 4) != (int*)0x0) {  // global manager vtable check
        // Call virtual function at vtable+0xc (likely Update or Prepare)
        (**(code**)(*(int*)**(int**)(DAT_012233a0 + 4) + 0xc))();

        // Get player object with position
        Player* pPlayer = (Player*)FUN_00471610();  // returns player pointer

        if (this->targetCount != 0) {
            currentArrayEntry = this->pTargetArray; // pointer to array of entity pointers
            while (true) {
                Entity* pEntity = (Entity*)*currentArrayEntry;
                // Calculate difference between player position and entity position
                diffX = pPlayer->posX - pEntity->posX;      // +0x30
                diffY = pPlayer->posY - pEntity->posY;      // +0x34
                diffZ = pPlayer->posZ - pEntity->posZ;      // +0x38

                squaredRadius = pEntity->detectionRadius * pEntity->detectionRadius; // +0x110
                distanceSquared = diffX * diffX + diffY * diffY + diffZ * diffZ;

                if (distanceSquared < (float)squaredRadius) {
                    // Found entity within radius
                    break;
                }
                playerIndex++;
                currentArrayEntry++;
                if ((uint)playerIndex >= this->targetCount) {
                    return 0;
                }
            }
            return pEntity;
        }
    }
    return 0;
}