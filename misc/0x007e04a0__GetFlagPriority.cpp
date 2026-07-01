// FUNC_NAME: GetFlagPriority
// Function address: 0x007e04a0
// Maps a flag value (bitmask) to a priority level (0-11).
// Used for determining the priority of capabilities or actions.
int GetFlagPriority(uint flag)
{
    if (flag > 0x8000) {
        if (flag < 0x400001) {
            if (flag == 0x400000) {
                return 1;
            }
            if (flag > 0x80000) {
                if (flag == 0x100000) {
                    return 1;
                }
                if (flag != 0x200000) {
                    return 0;
                }
                return 10;
            }
            if (flag == 0x80000) {
                return 1;
            }
            if (flag == 0x10000) {
                return 1;
            }
            if (flag == 0x20000) {
                return 1;
            }
            if (flag == 0x40000) {
                // Jump to common 1 return
                goto returnOne;
            }
            return 0;
        }
        if (flag < 0x10000001) {
            if (flag == 0x10000000) {
                return 2;
            }
            if (flag == 0x800000) {
                return 3;
            }
            if (flag == 0x1000000) {
                return 3;
            }
            if (flag == 0x2000000) {
                goto returnOne;
            }
            return 0;
        }
        if (flag == 0x20000000) {
            return 2;
        }
        if (flag != 0x40000000) {
            return 0;
        }
        // fall through to returnOne
        goto returnOne;
    }
    // flag <= 0x8000
    if (flag == 0x8000) {
        return 10;
    }
    if (flag < 0x101) {
        if (flag != 0x100) {
            switch (flag) {
                case 1:
                case 2:
                case 4:
                case 8:
                case 0x20:
                    goto returnOne;
                default:
                    return 0;
                case 0x10:
                    return 3;
                case 0x40:
                    return 0xb; // 11
                case 0x80:
                    return 9;
            }
        }
        // flag == 0x100
        return 6;
    }
    // flag between 0x101 and 0x1000 inclusive? Actually checks >0x1000 later
    if (flag > 0x1000) {
        if (flag == 0x2000) {
            return 0;
        }
        if (flag != 0x4000) {
            return 0;
        }
        return 10;
    }
    // flag <= 0x1000 but >= 0x101
    if (flag == 0x1000) {
        return 1;
    }
    if (flag == 0x200) {
        return 7;
    }
    if (flag == 0x400) {
        return 8;
    }
    if (flag == 0x800) {
        return 6;
    }
    return 0;

returnOne:
    return 1;
}