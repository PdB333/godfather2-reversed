// FUNC_NAME: Presentation::updateEventTriggers

// Reconstructed C++ for Presentation::updateEventTriggers
// Function address: 0x008c63b0
// Processes entries in the presentation's action list, setting/clearing flags on targets.

// Known offsets:
// Presentation class:
//   +0x130 : pointer to array of ActionEntry (0x1c bytes each)
//   +0x134 : number of entries in array
// ActionEntry:
//   +0x04 : type (1 = action with target, 2 = effect)
//   +0x08 : pointer to an action object
// ActionObject (for type 1):
//   +0xfc : pointer to a target object
// TargetObject (for bitfield):
//   +0x34 : flags (bit 3 = enable/disable flag)

void __thiscall Presentation::updateEventTriggers( bool enable )
{
    int count = *(int *)(this + 0x134);            // Number of entries
    char *entryBase = *(char **)(this + 0x130);    // Base of entry array

    if ( count > 0 )
    {
        // Process entries in reverse order (from last to first)
        for ( int i = count - 1; i >= 0; i-- )
        {
            ActionEntry *entry = (ActionEntry *)(entryBase + i * 0x1C);
            
            if ( entry->object != 0 )
            {
                if ( entry->type == 1 )
                {
                    // Action with a target object
                    char *object = (char *)entry->object;
                    char *target = *(char **)(object + 0xFC);  // +0xFC: target pointer in action object
                    
                    if ( target != 0 )
                    {
                        if ( !enable )
                        {
                            // Disable: set bit 3 of target's flags
                            uint *flags = (uint *)(target + 0x34);
                            *flags |= 8;
                        }
                        else
                        {
                            // Enable: call external helper (likely activates the target)
                            FUN_006b1990();
                        }
                    }
                }
                else if ( entry->type == 2 )
                {
                    // Effect entry - delegate to handler
                    FUN_008c5130( entry );
                }
            }
        }
    }
}