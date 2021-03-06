#!/bin/bash
for i in main.cpp SampleInstrument.cpp SyncMaster.cpp SamplePool.cpp SampleVariable.cpp Observable.cpp Variable.cpp WatchedVariable.cpp TablePlayback.cpp VariableContainer.cpp Filters.cpp SRPUpdaters.cpp FileSystem.cpp Trace.cpp Config.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.cpp tinyxml.cpp wildcard.cpp Tiny2NosStub.cpp Status.cpp WavFile.cpp Groove.cpp Persistent.cpp TimeService.cpp ServiceRegistry.cpp HexBuffers.cpp char.cpp SubService.cpp UnixFileSystem.cpp Result.cpp DEBSystem.cpp Logger.cpp ; do
	g++ -ggdb -fpermissive  -c $i 
done

g++ -c main.cpp

g++  main.o SampleInstrument.o SyncMaster.o SamplePool.o SampleVariable.o Observable.o Variable.o WatchedVariable.o TablePlayback.o VariableContainer.o Filters.o SRPUpdaters.o FileSystem.o Trace.o Config.o  tinyxmlerror.o tinyxmlparser.o tinystr.o tinyxml.o wildcard.o Tiny2NosStub.o Status.o WavFile.o Groove.o Persistent.o TimeService.o ServiceRegistry.o HexBuffers.o char.o SubService.o UnixFileSystem.o Result.o DEBSystem.o Logger.o -lSDL
