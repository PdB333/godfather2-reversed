// FUNC_NAME: RandomGenerator::getUint32
uint RandomGenerator::getUint32(void)
{
    uint value;

    // Static initialization of the random state (only once)
    if (!g_randomInitialized) {
        g_randomInitialized = true;
        RandomGenerator::initState(&g_randomState);     // Set up the state (e.g., seed)
        RandomGenerator::seedState(&g_randomState);     // Possibly additional seeding
    }

    // Read 4 bytes from the state as big-endian and convert to little-endian
    RandomGenerator::readBytes(&value, 4, &g_randomState);

    // Byte swap from big-endian to little-endian (network to host order)
    uint byte0 = (value & 0xFF) << 24;
    uint byte1 = ((value >> 8) & 0xFF) << 16;
    uint byte2 = ((value >> 16) & 0xFF) << 8;
    uint byte3 = (value >> 24);
    return byte0 | byte1 | byte2 | byte3;
}