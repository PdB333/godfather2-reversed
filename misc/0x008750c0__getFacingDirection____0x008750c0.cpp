// FUNC_NAME: getFacingDirection // 0x008750c0

void getFacingDirection(float *outVector) {
    float tmpX, tmpY, tmpZ;
    int playerObj = getPlayerData(); // returns pointer to player data, offsets 0x20-0x28 are facing vector
    tmpX = *(float *)(playerObj + 0x20);
    tmpY = *(float *)(playerObj + 0x24);
    tmpZ = *(float *)(playerObj + 0x28);

    // Normalize the vector (in-place)
    vectorNormalize(&tmpX, &tmpX); // both arguments same, so modifies tmpX,tmpY,tmpZ

    outVector[0] = tmpX;
    outVector[1] = tmpY;
    outVector[2] = tmpZ;

    char *flagStr = (char *)checkSomeFlag(); // returns pointer to a string, probably global toggle indicator
    float scaleFactor = DAT_00d5ccf8; // global multiplier
    if (*flagStr != '\0') {
        outVector[0] *= scaleFactor;
        outVector[1] *= scaleFactor;
        outVector[2] *= scaleFactor;
    }
}