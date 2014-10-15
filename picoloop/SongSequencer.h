using namespace std;



#include <string>
#include <vector>
#include "Master.h"
#ifndef __SONGSEQUENCER__
#define __SONGSEQUENCER__

class SongSequencer
{

public:
  SongSequencer();
  ~SongSequencer();
  int  incStep();
  int  getStep();
  int  setStep(int step);
  int  setLoopPoint(int loopStep);
  int  getLoopA();
  int  getLoopB(); 
  int  getPatternNumber(int cp,int trackNumber);
  int  getPatternNumberAtCursorPosition(int trackNumber);
  void setPatternNumber(int cursorPosition,int trackNumber,int patternNumber);
  vector <vector <int> > getSongVector();

  vector <vector <int> > songVector;
  
private:
  int                  step;
  int                  loopStepA;
  int                  loopStepB;

};

#endif
