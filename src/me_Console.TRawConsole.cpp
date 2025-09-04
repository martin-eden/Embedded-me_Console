// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2025-09-01
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_StreamTools.h>
#include <me_StreamsCollection.h>

using namespace me_Console;

/*
  Setup UART to typical speed
*/
TBool TRawConsole::Init()
{
  if (!InputStream.Init())
    return false;

  if (!OutputStream.Init())
    return false;

  return true;
}

/*
  Return pointer to input stream instance
*/
IInputStream * TRawConsole::GetInputStream()
{
  return &InputStream;
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
  TAddressSegment MemSeg
)
{
  me_StreamsCollection::TWorkmemInputStream InputStream;

  if (!InputStream.Init(MemSeg))
    return false;

  return me_StreamTools::CopyStreamTo(&InputStream, &OutputStream);
}

/*
  Send data from program memory segment to UART
*/
TBool TRawConsole::SendProgmemSegment(
  TAddressSegment ProgmemSeg
)
{
  me_StreamsCollection::TProgmemInputStream InputStream;

  if (!InputStream.Init(ProgmemSeg))
    return false;

  return me_StreamTools::CopyStreamTo(&InputStream, &OutputStream);
}

/*
  2024 #
  2025-08-21
  2025-08-25
  2025-08-26
  2025-09-01
*/
