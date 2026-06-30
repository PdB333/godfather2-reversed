// FUNC_NAME: AnimationEngine::processBoneTransforms
undefined4 __thiscall AnimationEngine::processBoneTransforms(
    char *boneIndices, 
    bool isRotation, 
    int *outCount, 
    float (*outTransform)[7]   // Actually a structure of size 0x20 or 0x40, but we treat as float array here
)
{
    float seed = (float)getSeed();  // FUN_00b9a1c0
    float seedFlt = seed;
    int processed = 0;
    char *endPtr = boneIndices + in_EAX;  // in_EAX is presumably a member storing buffer length

    if (boneIndices != endPtr)
    {
        double doubleSeed = (double)seed;  // fVar6
        int *ptr4 = &outTransform[0][1];    // param_5 + 4
        int *ptr8 = &outTransform[0][2];    // param_5 + 8
        int *ptr12 = &outTransform[0][3];   // param_5 + 0xc
        int globalZero = DAT_00e2b1a4;      // Some constant, likely 0

        do
        {
            if ((boneIndices == 0) || (*boneIndices == 0x02))
            {
                if (isRotation == false)
                {
                    // Set rotation (7 floats)
                    this = setRotation((float)doubleSeed, this);
                    this = setRotation(seedFlt, this);
                    this = setRotation(seedFlt, this);
                    this = setRotation(seedFlt, this);
                    this = setRotation(seedFlt, this);
                    this = setRotation(seedFlt, this);
                    this = setRotation(seedFlt, this);
                    outTransform[0][7] = globalZero;  // offset 0x1c
                    int step = 0x20;  // size of rotation block
                }
                else
                {
                    // Set translation (7 floats at specific offsets)
                    setTranslation((float)doubleSeed, outTransform);
                    setTranslation(seedFlt, ptr4);
                    setTranslation(seedFlt, ptr8);
                    setTranslation(seedFlt, ptr12);
                    setTranslation(seedFlt, &((float*)outTransform)[8]);   // offset 0x20
                    setTranslation(seedFlt, &((float*)outTransform)[9]);   // offset 0x24
                    this = setTranslation(seedFlt, &((float*)outTransform)[10]); // offset 0x28
                    outTransform[0][15] = globalZero;  // offset 0x3c
                    outTransform[0][11] = globalZero;  // offset 0x2c
                    int step = 0x40;  // size of translation block
                }

                // Advance pointers by step
                ptr8 = (int*)((char*)ptr8 + step);
                ptr12 = (int*)((char*)ptr12 + step);
                outTransform = (float (*)[7])((char*)outTransform + step);
                ptr4 = (int*)((char*)ptr4 + step);
                doubleSeed = (double)seed;  // Reset from seed
                processed++;
            }
            else if (*boneIndices != '\0')
            {
                // For bone indices not 0x02 nor 0, do six dummy calls
                doSomething();
                doSomething();
                doSomething();
                doSomething();
                doSomething();
                doSomething();
                this = doSomething();
                doubleSeed = extraout_ST0;  // Unused
            }

            boneIndices++;
        } while (boneIndices != endPtr);

        *outCount = processed;
        return this;
    }

    *outCount = 0;
    return this;
}