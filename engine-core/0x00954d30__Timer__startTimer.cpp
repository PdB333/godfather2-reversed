// FUNC_NAME: Timer::startTimer

struct Timer {
    int state;                 // +0x00: 0=stopped, 1=running, 2=idle
    int startValues[4];        // +0x04 (indices 4-7)
    int deadline;              // +0x08 (index 8)
    int sourceValues[4];       // +0x0C (indices 12-15)
    int duration;              // +0x10 (index 16)
    int callbackId;            // +0x11 (index 17)
    int callbackContext;       // +0x13 (index 19)
};

int __fastcall Timer::startTimer(int *this)
{
    int currentTime;
    
    if (this[0] == 2)  // state idle
    {
        this[0] = 1;   // transition to running
        
        // copy source values into start values (e.g., initial parameters)
        this[4] = this[0xc];
        this[5] = this[0xd];
        this[6] = this[0xe];
        this[7] = this[0xf];
        
        currentTime = __read_time();  // FUN_00494d10 – returns current tick count
        
        // store the callback context for later use
        this[0x13] = this[0x11];
        
        // compute deadline = currentTime + duration
        this[8] = currentTime + this[0x10];
        
        return 1;
    }
    
    // invalid state: reset to stopped
    this[0] = 0;
    return 0;
}