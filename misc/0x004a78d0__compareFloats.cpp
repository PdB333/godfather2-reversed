// FUNC_NAME: compareFloats
uint compareFloats(uint mode, float valA, float valB)
{
    // Evaluate float comparison based on mode:
    // 0: valA > valB
    // 1: valA < valB
    // 2: valA >= valB
    // 3: valA <= valB
    // 4: valA == valB
    // 5: valA != valB
    switch (mode)
    {
    case 0:
        if (valB < valA)
            return 1;
        break;
    case 1:
        if (valA < valB)
            return 1;
        break;
    case 2:
        if (valB <= valA)
            return 1;
        break;
    case 3:
        if (valA <= valB)
            return 1;
        break;
    case 4:
        if (valA == valB)
            return 1;
        break;
    case 5:
        if (valA != valB)
            return 1;
        break;
    default:
        // Invalid mode – return the upper 24 bits of mode as a fallback
        return mode & 0xffffff00;
    }
    return 0;
}