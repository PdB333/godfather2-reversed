// FUNC_NAME: RandomGenerator::nextValue

// Lagged Fibonacci generator (lags 1 and 2, modulus 20)
// State: 20-element circular buffer + current index
static int s_randIndex;       // DAT_0119478c
static int s_randBuffer[20];  // DAT_01194790

int RandomGenerator::nextValue()
{
    int idxA = s_randIndex - 1;  // (current - 1) % 20
    int idxB = s_randIndex + 2;  // (current + 2) % 20

    // Wrap modulo 20
    if (idxA < 0) {
        idxA = 19;
    } else if (idxB > 19) {
        idxB = s_randIndex - 18;  // equivalent to idxB - 20
    }

    // new value = buffer[idxA] + buffer[idxB]
    s_randBuffer[idxA] += s_randBuffer[idxB];

    // advance index
    s_randIndex = idxA;

    return s_randBuffer[idxA];
}