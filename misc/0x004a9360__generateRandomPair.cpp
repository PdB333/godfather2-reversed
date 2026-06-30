// FUNC_NAME: generateRandomPair
void generateRandomPair(uint32_t unused, uint32_t *outPair)
{
    uint32_t r0, r1;

    // Fill 32 bytes of random data and take first word
    getRandomBytes(0x20, &r0);
    getRandomBytes(0x20, &r1);

    outPair[0] = r0;
    outPair[1] = r1;
}