// FUNC_NAME: AudioMixer::selectMixingStrategy
void AudioMixer::selectMixingStrategy(int* requestA, int* requestB, void* outputInfo)
{
    int priorityA = requestA[0];          // +0x00: priority/request size
    int priorityB = requestB[0];          // +0x00: priority/request size
    bool bFlagsDiffer = (requestA[2] != requestB[2]); // +0x08: flag comparison (e.g., looping)
    int minPriority;
    int sum = priorityA + priorityB + 1;

    minPriority = (priorityB <= priorityA) ? priorityB : priorityA;
    if (349 < minPriority)                // 0x15d: large threshold
    {
        mixLarge(requestB, outputInfo);
        *(uint32*)((uint8*)outputInfo + 8) = (uint32)bFlagsDiffer;
        return;
    }

    minPriority = (priorityB <= priorityA) ? priorityB : priorityA;
    if (108 < minPriority)                // 0x6c: medium threshold
    {
        mixMedium(requestB, outputInfo);
        *(uint32*)((uint8*)outputInfo + 8) = (uint32)bFlagsDiffer;
        return;
    }

    if ((sum < 512) && ((priorityB <= priorityA ? priorityB : priorityA) < 257))
    {
        mixSmall(requestB, outputInfo, sum);
        *(uint32*)((uint8*)outputInfo + 8) = (uint32)bFlagsDiffer;
        return;
    }

    mixDefault(requestA, requestB, outputInfo, sum);
    *(uint32*)((uint8*)outputInfo + 8) = (uint32)bFlagsDiffer;
}