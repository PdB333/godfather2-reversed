// FUNC_NAME: randomFloat
float randomFloat(void)
{
    int randomValue;
    
    randomValue = _rand();
    return (float)randomValue * (float)DAT_00e44590; // DAT_00e44590 is likely 1.0f / RAND_MAX (0x7fff) to normalize to [0,1]
}