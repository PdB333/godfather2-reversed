// FUNC_NAME: PerformanceTracker::recordSample

class PerformanceTracker {
public:
    int m_counter;             // +0x9c
    DWORD m_timestampLow;      // +0xa8
    LONG m_timestampHigh;      // +0xac

    void __fastcall recordSample();
};

void __fastcall PerformanceTracker::recordSample() {
    m_counter++;
    LARGE_INTEGER performanceCount;
    QueryPerformanceCounter(&performanceCount);
    m_timestampLow = performanceCount.LowPart;
    m_timestampHigh = performanceCount.HighPart;
}