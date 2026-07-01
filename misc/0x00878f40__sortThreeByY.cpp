// FUNC_NAME: sortThreeByY
void sortThreeByY(float* pA, float* pB, float* pC)
{
    // Sort three 2-element vectors by their Y component (p[1]) in ascending order
    // Uses a sorting network: compare and swap pairs, ensuring final order A <= B <= C

    float tempX, tempY;

    // Compare B and A
    if (pB[1] <= pA[1] && pA[1] != pB[1]) {
        tempX = pB[0];
        tempY = pB[1];
        pB[0] = pA[0];
        pB[1] = pA[1];
        pA[0] = tempX;
        pA[1] = tempY;
    }

    // Compare C and B
    if (pC[1] <= pB[1] && pB[1] != pC[1]) {
        tempX = pC[0];
        tempY = pC[1];
        pC[0] = pB[0];
        pC[1] = pB[1];
        pB[0] = tempX;
        pB[1] = tempY;
    }

    // Compare B and A again (finalize order)
    if (pB[1] <= pA[1] && pA[1] != pB[1]) {
        tempX = pB[0];
        tempY = pB[1];
        pB[0] = pA[0];
        pB[1] = pA[1];
        pA[0] = tempX;
        pA[1] = tempY;
    }
}