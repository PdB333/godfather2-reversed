// FUNC_NAME: EARSObject::processFlagMessage
// Address: 0x004abb80
// Role: Handles flag manipulation commands (set, clear, replace) and special action #6.
// Offsets:
//   this+0x3C: uint32_t flags
//   this+0x1C: EARSObject* pOwner (or nullptr)
//   pOwner+0x44: char isEnabled (0 = disabled)

__thiscall uint8_t EARSObject::processFlagMessage(
    int this,
    uint32_t arg1,
    uint32_t arg2,
    uint32_t arg3,
    uint32_t commandType,
    void* dataBlock
)
{
    switch (commandType)
    {
    case 3: // OR flags into current
        *(uint32_t*)(this + 0x3C) |= *(uint32_t*)((uint8_t*)dataBlock + 4);
        break;

    case 4: // AND NOT (clear bits)
        *(uint32_t*)(this + 0x3C) &= ~*(uint32_t*)((uint8_t*)dataBlock + 4);
        break;

    case 5: // Replace flags completely
        *(uint32_t*)(this + 0x3C) = *(uint32_t*)((uint8_t*)dataBlock + 4);
        break;

    case 6: // Execute special action with data
        executeAction(*(uint32_t*)((uint8_t*)dataBlock + 4)); // FUN_004abdd0
        return 1;

    default:
        // Delegate to base class handler
        return baseProcessMessage(arg1, arg2, arg3, commandType, dataBlock); // FUN_00624c20
    }

    // After modifying flags, if we have a valid owner and it is disabled, notify
    EARSObject* owner = *(EARSObject**)(this + 0x1C);
    if (owner != nullptr && *(char*)(owner + 0x44) == '\0')
    {
        notifyFlagsChanged(); // FUN_004abd20
        return 1;
    }

    return 1;
}