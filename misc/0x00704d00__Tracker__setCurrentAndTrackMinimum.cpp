// FUNC_NAME: Tracker::setCurrentAndTrackMinimum
void __thiscall Tracker::setCurrentAndTrackMinimum(uint newValue)
{
  // +0x9c: current value
  this->currentValue = newValue;
  // +0x98: tracked minimum value (lower-is-better stat like time/score)
  if (newValue < this->minimumValue) {
    this->minimumValue = newValue;
  }
}