// FUN_004a9d10: debugLogRandomString
void debugLogRandomString(void)
{
    int randomLength;
    char randomStringBuffer[132];  // 132 bytes buffer for random string

    // Generate a random integer in [0, 32) using some randomizer function
    FUN_0064b9e0(0x20, &randomLength);   // probably: randomLength = randomRange(0x20)

    // Fill buffer with random data of size (randomLength * 8) bytes
    FUN_0064b9e0(randomLength * 8, randomStringBuffer); // fills buffer with random bytes

    // Null-terminate at position randomLength (as a string terminator)
    randomStringBuffer[randomLength] = '\0';

    // Pass the random string to debug logging function (likely prints to console)
    FUN_004d3d90(randomStringBuffer);
}