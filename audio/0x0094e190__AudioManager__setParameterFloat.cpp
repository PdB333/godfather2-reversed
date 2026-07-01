// FUNC_NAME: AudioManager::setParameterFloat
// Address: 0x0094e190
// Role: Sets an audio parameter (type 4) using both an integer and float representation.
//       Retrieves a channel/object identifier from a global manager singleton.
//       The integer value is obtained by rounding the input float.

#include <cmath> // for round

// Forward declarations for internal EARS audio functions
void EARS_BeginParameterSet();
void EARS_SetParameterType(int type);
void EARS_SetIntParameter(int value);
void EARS_SetIdentifier(int id);
void EARS_SetFloatParameter(float value);

// Global audio manager singleton pointer (from DAT_012233a0)
// The actual structure contains a list of objects; the +4 offset points to a pointer
// to a member at offset 0x38 within an object, from which an identifier (first field) is extracted.
extern void* gAudioManager;

void AudioManager::setParameterFloat(float value)
{
    // Start parameter configuration sequence
    EARS_BeginParameterSet();
    
    // Set the parameter type to 4 (e.g., pitch, volume, or similar)
    EARS_SetParameterType(4);
    
    // Convert float to integer for the integer component of the parameter
    int intValue = static_cast<int>(std::round(value));
    EARS_SetIntParameter(intValue);
    
    // Retrieve the identifier from the global manager's current object
    // The object's member pointer is stored at gAudioManager + 4
    int* memberPtr = *(int**)((char*)gAudioManager + 4);
    int identifier;
    if (memberPtr == nullptr || *memberPtr == 0x1F30) {
        identifier = -1; // Invalid or uninitialized object
    } else {
        // The member pointer points to offset 0x38 within the object structure.
        // By subtracting 0x38 we reach the object's base, whose first field is the identifier.
        identifier = *(int*)((char*)memberPtr - 0x38);
    }
    EARS_SetIdentifier(identifier);
    
    // Set the float component of the parameter directly
    EARS_SetFloatParameter(value);
}