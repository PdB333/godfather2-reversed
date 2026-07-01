// FUNC_NAME: RunningAverage::addSample

struct RunningAverage {
    float latest;    // +0x00: Most recent sample value
    float sum;       // +0x04: Sum of all samples
    float count;     // +0x08: Number of samples (stored as float for conversion)
};

void __thiscall RunningAverage::addSample(float *this, float sample)
{
    // Increment the sample count (stored as float, but treated as int for increment)
    this[2] = (float)((int)this[2] + 1);
    // Set the latest sample
    *this = sample;
    // Accumulate the sum
    this[1] = this[1] + sample;
}