// FUNC_NAME: Enemy::trySpawnEnemy
bool __fastcall Enemy::trySpawnEnemy(int this)
{
    char isValid;
    uint32_t someHandle;
    int spawnedEnemy;

    if (g_globalTime < *(float *)(this + 0x30)) { // +0x30: spawnCooldownTimer
        someHandle = FUN_00798f50(0x35); // likely spawn pool / factory function
        isValid = FUN_0079e920(someHandle); // check if valid spawn target exists
        if ((isValid != 0) && (isValid = FUN_007ab420(0x20), isValid != 0)) { // check additional conditions (0x20 = some flag)
            spawnedEnemy = FUN_007ab320(); // allocate / acquire enemy object
            FUN_0079d780(spawnedEnemy); // initialize / set up the enemy
            if (spawnedEnemy != 0) {
                return true;
            }
        }
    }
    return false;
}