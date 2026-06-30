// FUNC_NAME: GamePlayLogging::logStringEvent
void __fastcall GamePlayLogging::logStringEvent(GamePlayLogging* this)
{
    // Temporary scoped string buffer (array of 3 pointers: data, size, destructor)
    byte* scopedString[3];  // +0x00: data, +0x04: size?, +0x08: destructor callback
    void (*stringDestructor)(byte*); // set by StringFormatConstructor

    // Format a string using the format pattern at DAT_00d5db54 and the member string at this+0x3e4
    StringFormatConstructor(scopedString, 1, &DAT_00d5db54, *(byte**)(this + 0x3e4));
    byte* stringPtr = scopedString[0];
    if (stringPtr == nullptr) {
        stringPtr = &DAT_0120546e; // Default fallback string
    }

    // Post a gameplay event with two category IDs and the string data
    // IDs: 0x53504750 ('P','G','S','P'), 0x5357474c ('L','G','W','S') – event classification
    PostGameplayEvent(0x53504750, 0x5357474c, stringPtr);

    // Possibly flush or finalize the event batch
    FlushEvents();

    // Clean up the temporary string if it was dynamically allocated
    if (scopedString[0] != nullptr) {
        stringDestructor(scopedString[0]);
    }
}