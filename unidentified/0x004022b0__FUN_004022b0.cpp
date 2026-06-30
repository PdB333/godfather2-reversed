void FUN_004022b0()
{
    LARGE_INTEGER counter{};

    QueryPerformanceCounter(&counter);

    *unaff_ESI = static_cast<DWORD>(counter.LowPart);
    unaff_ESI[1] = static_cast<DWORD>(counter.HighPart);
}