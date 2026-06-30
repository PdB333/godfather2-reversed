// FUNC_NAME: Entity::applyMovementFromController
void __thiscall Entity::applyMovementFromController(int thisPtr, int* pController, float* outPosition)
{
    // Check freeze flag at offset +0xAC (bit 1)
    if ((*(byte *)(thisPtr + 0xAC) & 2) != 0) {
        // Frozen: use alternative position calculation
        FUN_00732460(outPosition, pController);
        return;
    }

    // Get pointer to global game state/time manager
    int* gameStateMgr = GetGameStateManager(); // FUN_00471610

    // Copy initial position from game state manager (x,y as double, z separately)
    // Offsets: +0x30 = x (float), +0x34 = y (float), +0x38 = z (float)
    *(double*)outPosition = *(double*)(gameStateMgr + 0x30);
    outPosition[2] = *(float*)(gameStateMgr + 0x38);

    // Call virtual function on controller to get orientation data
    // Vtable offset 0x40 -> function index 16 (0x40 / 4)
    // Output: local_38 (8 bytes, possibly two floats) and local_2c (4 bytes)
    float orientationData[3]; // Actually orientationData[0] from local_2c, orientationData[1] from local_38 low, etc.
    (*(code**)(*pController + 0x40))(orientationData, orientationData + 1); // approximate

    // Compute time delta from orientation and global constant
    float delta = (orientationData[1] - orientationData[0]) - GRAVITY_CONSTANT; // _DAT_00d5cf70

    // Get velocity components from game state manager
    // At offset +0x10: packed as double -> two floats (x, y velocity)
    // At offset +0x18: single float (z velocity)
    double packedVelocity = *(double*)(gameStateMgr + 0x10);
    float velX = (float)packedVelocity;  // low 32 bits
    float velY = (float)((unsigned long long)packedVelocity >> 32); // high 32 bits
    float velZ = *(float*)(gameStateMgr + 0x18);

    // Possibly normalize the 2D velocity vector (X,Y)
    NormalizeVector2D(&velX, &velY); // FUN_0056afa0

    // Apply velocity * delta to position
    outPosition[1] += velY * delta;
    outPosition[0] += velX * delta;
    outPosition[2] += velZ * delta;
}