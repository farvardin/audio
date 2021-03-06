using namespace std;

#include "Machine.h"
#include "Machine/Picosynth/PicosynthMachine.h"
#include "Machine/Picodrum/PicodrumMachine.h"
#include "Machine/Dbopl/DboplMachine.h"
#include "Machine/PBSynth/PBSynthMachine.h"
#ifdef __FPU__
#include "Machine/Cursynth/CursynthMachine.h"
#include "Machine/Open303/Open303Machine.h"
#include "Machine/Twytch/TwytchsynthMachine.h"
#include "Machine/MDADrum/MDADrumMachine.h"
#endif 

#ifdef __RTMIDI__
#include "Machine/MidiOutSystem/MidiOutMachine.h"
#endif
//#include "Effect.h"
#include "EffectDelay.h"
#include "EffectDisabled.h"
#include <SDL/SDL_types.h>

#ifndef __MONOMIXER____
#define __MONOMIXER____

class MonoMixer
{
 public:
  MonoMixer();
  ~MonoMixer();
  void        init();
  void        setMachineType(int type);
  void        setAmplitude(int amp);
  //  void        setInput(Machine * M);
  Machine *   getInput();
  Effect  *   getEffect();
  Sint16      tick();

 private:

  Machine              *M;
  PicosynthMachine      PS;
  PicodrumMachine       PD;
  dboplMachine          OPLM;
  PBSynthMachine        PBS;

#ifdef __FPU__
  CursynthMachine       CS;
  Open303Machine        O303;
  TwytchsynthMachine    TW;
  MDADrumMachine        MD;
#endif

#ifdef __RTMIDI__
  MidiOutMachine        MIDIOUTM;
#endif

  Effect                *FX;
  EffectDelay           FXDelay;
  EffectDisabled        FXDisabled;

  Sint16                amplitude;
  int                   machine_type;

  int                   fx_depth;
  int                   fx_speed;

  int                   index;
  Sint16                * buffer16;
  Sint32                * buffer32;
};


#endif
