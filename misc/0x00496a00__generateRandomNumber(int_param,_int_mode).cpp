// FUNC_NAME: generateRandomNumber(int param, int mode)
int generateRandomNumber(int param, int mode)
{
    int randomValue;
    int result;

    switch (mode)
    {
    case 3:
        // Returns non-negative random value (clamped to 0 if negative)
        randomValue = getRandomInt(2);  // seed type 2
        return (randomValue < 1) ? 0 : randomValue;  // if <1 return 0, else unchanged
    case 4:
        // Returns positive absolute value of negative random, else 0
        randomValue = getRandomInt(2);
        if (randomValue < 0)
            return -randomValue;
        else
            return 0;
    case 5:
        // If random (type 1) is less than -param, return its absolute value
        randomValue = getRandomInt(1);
        if (randomValue < -param)
            return -randomValue;
        break;
    case 6:
        // Returns random (type 1) if <= param, else 0
        randomValue = getRandomInt(1);
        return (randomValue <= param) ? randomValue : 0;
    case 7:
        // Returns random (type 0) if <= param, else 0
        randomValue = getRandomInt(0);
        return (randomValue <= param) ? randomValue : 0;
    case 8:
        // If random (type 0) is less than -param, return its absolute value
        randomValue = getRandomInt(0);
        if (randomValue < -param)
            return -randomValue;
        break;
    default:
        break;
    }
    return 0;
}