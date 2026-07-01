// FUNC_NAME: GameTime::addTime
void __thiscall GameTime::addTime(int* pThis, int iAddYears, int iAddDays, int iAddHours, int iAddMinutes, int iAddSeconds)
{
    // Structure offsets (5 ints):
    // +0x00: m_years
    // +0x04: m_days (modulo 24 – likely a game‑specific calendar unit, e.g., 24‑day months)
    // +0x08: m_hours
    // +0x0C: m_minutes
    // +0x10: m_seconds

    int overflow;
    long total;

    // Add seconds
    overflow = pThis[4];
    pThis[4] = (overflow + iAddSeconds) % 60;                 // seconds wrap at 60
    total = pThis[3] + (overflow + iAddSeconds) / 60 + iAddMinutes;

    // Add minutes
    pThis[3] = total % 60;                                    // minutes wrap at 60
    overflow = total / 60 + iAddHours + pThis[2];

    // Add hours
    pThis[2] = overflow % 24;                                 // hours wrap at 24
    overflow = overflow / 24 + iAddDays + pThis[1];           // overflow from hours → days

    // Add days (modulo 24)
    pThis[1] = overflow % 24;                                 // days wrap at 24 (game‑specific)
    // Advance years by the number of full 365‑day cycles captured in the days overflow
    *pThis = *pThis + overflow / 365 + iAddYears;
}