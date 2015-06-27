#include "MidiOutSystem.h"
MidiOutSystem::MidiOutSystem()
{
  lock_a=PTHREAD_MUTEX_INITIALIZER;
}


MidiOutSystem::~MidiOutSystem()
{
  int note;
  int i;
  for (i=0;i<88;i++)
    this->noteOff(0,i);

}


MidiOutSystem & MidiOutSystem::getInstance()
{
  static MidiOutSystem instance;
  return instance;
}

bool MidiOutSystem::init()
{
  //RtMidiOut *midiout = 0;
  try {
    rtmidiout = new RtMidiOut();
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }
  //midiChannel=0;
}

bool MidiOutSystem::checkChannel(int channel)
{
  if (channel<0 |
      channel>15)
    {
      printf("MidiOutSystem::noteOn wrong channel=%d\n",channel);
      return false;
    }
  return true;
}

void MidiOutSystem::noteOn( int midiChan,int note,int velocity )
{
  if (this->checkChannel(midiChan))
    {
      //printf("MIDI_NOTEON %d \n",note);
      //std::lock(lock_a);
      pthread_mutex_lock( &lock_a );

      message.push_back(0x90+midiChan);
      message.push_back(note);
      message.push_back(0x7c);
      // pthread_mutex_lock( &lock_a );
      // pthread_mutex_unlock( &lock_a );
      pthread_mutex_unlock( &lock_a );
      //std::unlock(lock_a);
      // rtmidiout->sendMessage(&message);
      // message.clear();
    }
}

void MidiOutSystem::noteOff( int midiChan,int note)
{
  if (this->checkChannel(midiChan))
    {
      //printf("MIDI_NOTEOFF %d \n",note);
      pthread_mutex_lock( &lock_a );

      message.push_back(0x80+midiChan);
      message.push_back(note);
      message.push_back(0x0);
      pthread_mutex_unlock( &lock_a );
    }
}


void MidiOutSystem::cc( int midiChan,int cc,int value )
{
  if (this->checkChannel(midiChan))
    {
      //printf("MIDI_NOTEON %d \n",note);
      pthread_mutex_lock( &lock_a );
      message.push_back(0xB0+midiChan);
      message.push_back(cc);
      message.push_back(value);
      pthread_mutex_unlock( &lock_a );
      // rtmidiout->sendMessage(&message);
      // message.clear();
    }
}


int MidiOutSystem::msgSize()
{
  return message.size(); 
}

void MidiOutSystem::flushMsg()
{
  printf("*****************FLUSH:%d\n",message.size());
  pthread_mutex_lock( &lock_a );
  rtmidiout->sendMessage(&message);
  message.clear();
  pthread_mutex_unlock( &lock_a );
}


bool MidiOutSystem::chooseMidiPort( std::string portName )
{
  std::string tmpPortName;
  int portNumber=-1;

  std::cout << "MidiOutSystem::chooseMidiPort(\""<< portName <<"\")\n";

  unsigned int i = 0, nPorts = rtmidiout->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  std::cout << "Displaying All Midi Port\n";
  for ( i=0; i<nPorts; i++ ) {
    tmpPortName = rtmidiout->getPortName(i);
    std::cout << "  Output port #" << i << ": [" << tmpPortName << "]\n";
  }
  std::cout << "\n";

    for ( i=0; i<nPorts; i++ ) {
      tmpPortName = rtmidiout->getPortName(i);
      if (tmpPortName==portName)
	{
	  std::cout << "The midi port was found : [" << portName << "]\n";
	  portNumber=i;
	}
    }

    if (portNumber!=-1)
      {
	std::cout << "Opening port : " << portNumber << " [" << portName << "]\n";
	rtmidiout->openPort( portNumber );
      }

  return true;
}