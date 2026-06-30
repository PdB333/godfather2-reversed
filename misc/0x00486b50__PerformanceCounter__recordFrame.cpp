// FUNC_NAME: PerformanceCounter::recordFrame

void __fastcall PerformanceCounter::recordFrame()
{
    // Increment frame counter at offset +0xa0
    this->frameCount++;

    LARGE_INTEGER performanceCount;
    QueryPerformanceCounter(&performanceCount);

    // Store high-resolution timestamp at offsets +0xb0 and +0xb4
    this->qpcLow  = performanceCount.LowPart;
    this->qpcHigh = performanceCount.HighPart;
}