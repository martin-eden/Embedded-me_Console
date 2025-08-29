// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_WorkMemory.h>
#include <me_ProgramMemory.h>
#include <me_MemorySegment.h>

#include <me_StreamTools.h>
#include <me_StreamsCollection.h>

using namespace me_Console;

/*
  Setup UART to typical speed
*/
TBool TRawConsole::Init()
{
  if (!OutputStream.Init())
    return false;

  return true;
}

/*
  Return pointer to output stream instance
*/
IOutputStream * TRawConsole::GetOutputStream()
{
  return &OutputStream;
}

/*
  Write byte to output stream
*/
TBool TRawConsole::SendByte(
  TUint_1 Byte
)
{
  return OutputStream.Write(Byte);
}

/*
  Send data segment from memory to output stream
*/
TBool TRawConsole::SendSegment(
  TAddressSegment Data
)
{
  me_StreamTools::TAddrsegInputStream MemoryInputStream;

  if (!MemoryInputStream.Init(Data, me_WorkMemory::Op_GetByte))
    return false;

  return me_StreamTools::CopyStreamTo(&MemoryInputStream, &OutputStream);
}

/*
  Send data from program memory segment to UART
*/
TBool TRawConsole::SendProgmemSegment(
  TAddressSegment Data
)
{
  me_StreamTools::TAddrsegInputStream MemoryInputStream;

  if (!MemoryInputStream.Init(Data, me_ProgramMemory::Op_GetByte))
    return false;

  return me_StreamTools::CopyStreamTo(&MemoryInputStream, &OutputStream);
}

/*
  2024 #
  2025-08-21
  2025-08-25
  2025-08-26
*/
