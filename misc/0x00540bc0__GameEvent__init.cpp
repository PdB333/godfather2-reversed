// FUNC_NAME: GameEvent::init
// Address: 0x00540bc0
// Initializes a 20-byte event structure with a fixed event type (0x3e0) and four data parameters.
// Likely used to create a specific game event that carries four additional integer payloads.
void __thiscall GameEvent::init(uint data1, uint data2, uint data3, uint data4)
{
    this->eventType = 0x3e0;   // +0x00: event type identifier (hardcoded, likely a specific event)
    this->param0 = data1;      // +0x04: first parameter
    this->param1 = data2;      // +0x08: second parameter
    this->param2 = data3;      // +0x0C: third parameter
    this->param3 = data4;      // +0x10: fourth parameter
}