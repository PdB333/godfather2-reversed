// FUNC_NAME: ActionCondition::processTrigger
uint __thiscall ActionCondition::processTrigger( int target, int value, uint previousState )
{
    uint result = previousState & 0xFFFFFF00;
    
    if ( target == m_targetObject )
    {
        uint flags = m_stateFlags;                         // +0x28: state condition flags (bit0=less, bit1=equal, bit2=greater)
        bool conditionMet = false;
        
        if ( ( flags & 2 ) && ( value == m_threshold ) )   // +0x2c: threshold value
            conditionMet = true;
        else if ( ( flags & 1 ) && ( value < m_threshold ) )
            conditionMet = true;
        else if ( ( flags & 4 ) && ( m_threshold < value ) )
            conditionMet = true;
        
        if ( conditionMet )
        {
            // Check if we should trigger a callback (bit2 of extraFlags)
            if ( !( m_extraFlags & 4 ) && m_callbackObject )   // +0x30: extra flags, +0x4: callback pointer
            {
                // Notify parent system at this - 0x14 about the callback object
                FUN_00407e60( reinterpret_cast<ActionCondition*>( reinterpret_cast<char*>( this ) - 0x14 ), 
                              m_callbackObject );
            }
            
            if ( m_timer > 0.0f )            // +0x1c: timer in seconds
            {
                // Allocate a new action object (size 0xC)
                int newAction = FUN_009c8e50( 12 );
                uint actionParam = 0;
                if ( newAction != 0 )
                {
                    actionParam = FUN_0045ca00( reinterpret_cast<char*>( this ) - 0x50 );
                }
                // Start a timed action
                FUN_00440590( this + 0x14, 0, m_timer, actionParam, 0 );
            }
            else
            {
                // Immediate action: prepare and execute
                FUN_0045ca00( reinterpret_cast<char*>( this ) - 0x50 );
                
                // Pack local data and trigger execution
                void* packedData = reinterpret_cast<void*>( *(int*)( this + 0x14 ) );
                FUN_00408a00( &packedData, 0 );
                FUN_0045cac0();
            }
            
            // Update result flags based on extraFlags (bit2-related)
            result = ( result & 0xFFFFFF01 ) | 
                     ( ( ~( m_extraFlags >> 2 ) << 1 ) & 0xFE );  // Construct return value from extraFlags byte
            
            m_processCount++;                 // +0x34: number of times condition triggered
        }
    }
    return result;
}