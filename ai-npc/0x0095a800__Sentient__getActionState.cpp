// FUNC_NAME: Sentient::getActionState
// Address: 0x0095a800
// Role: Determines action availability for a sentient entity.
// Returns 0 if action blocked, 1 if normal action allowed, 2 or 3 if special action allowed (based on flags and type)

// Forward declarations (assumed global)
extern int isGamePaused(void); // Likely checks global pause or game state

// Sentient class member function (__thiscall)
char Sentient::getActionState() const
{
    char result = 0;

    if (this == nullptr)
        return 0;

    if (isGamePaused() != 0)
        return 0;

    // Check flags at +0x34: bit 12 (stun/immobilize) must be clear
    uint32_t flags = *(uint32_t*)(this + 0x34);
    if ((~((uint8_t)(flags >> 0xC)) & 1) != 0) // bit 12 == 0
    {
        // Action state at +0xC4 must be 0 or 1
        int32_t actionState = *(int32_t*)(this + 0xC4);
        if (actionState == 0 || actionState == 1)
        {
            // Type identifier at +0x40
            int32_t typeId = *(int32_t*)(this + 0x40);
            if (typeId == 0x637B907) // e.g., player or specific object type
            {
                // Special action counter at +0xFC: non-zero ⇒ return 2 or 3?
                int32_t specialCounter = *(int32_t*)(this + 0xFC);
                result = (specialCounter != 0) + 2; // returns 2 if zero, 3 if non-zero
                return result;
            }

            // Fallthrough for other types or when specialCounter is zero
            int32_t specialCounter = *(int32_t*)(this + 0xFC);
            int32_t blockingFlag = *(int32_t*)(this + 0x174);
            if (specialCounter == 0 && blockingFlag == 0 && ((flags >> 0x1C) & 1) == 0) // bit 28 clear (e.g., aiming)
            {
                result = 1;
            }
        }
    }

    return result;
}