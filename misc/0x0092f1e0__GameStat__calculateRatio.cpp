// FUNC_NAME: GameStat::calculateRatio
float10 GameStat::calculateRatio(void)
{
  int numerator, denominator;
  float10 numeratorFloat, denominatorFloat;
  
  numerator = GameStat::getNumerator();
  denominator = GameStat::getDenominator();
  
  denominatorFloat = (float10)denominator;
  if (denominator < 0) {
    denominatorFloat = denominatorFloat + (float10)0x100000000; // + 2^32 for unsigned conversion
  }
  
  if (numerator == 0) {
    return (float10)(float)denominatorFloat;
  }
  
  numeratorFloat = (float10)numerator;
  if (numerator < 0) {
    numeratorFloat = numeratorFloat + (float10)0x100000000;
  }
  
  return denominatorFloat / numeratorFloat;
}