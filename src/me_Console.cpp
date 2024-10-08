// Serial console interface

/*
  Author: Martin Eden
  Status: sketching
  Last mod.: 2024-10-08
*/

#include "me_Console.h"

#include <me_BaseTypes.h>
#include <me_InstallStandardStreams.h> // make printf() work
#include <me_MemorySegment.h> // TMemorySegment
#include <me_String.h> // formatting to TMemorySegment

#include <HardwareSerial.h> // "Serial" for Init()
#include <stdio.h> // printf()

using namespace me_Console;

using
  me_MemorySegment::TMemorySegment;

/*
  Setup console with serial speed
*/
TBool TConsole::Init(
  TUint_4 SerialSpeed
)
{
  Serial.begin(SerialSpeed);
  InstallStandardStreams();

  NeedDelimiter = false;
  LineIsEmpty = true;
  IndentLev = 0;

  return true;
}

// Max byte value. I need to move such lame constants somewhere
const TUint_1 Max_Uint_1 = 0xFF;

/*
  Increase indent

  Indent is increased up to certain hardcoded limit.
*/
void TConsole::Indent()
{
  if (IndentLev == Max_Uint_1)
    return;

  ++IndentLev;
}

/*
  Decrease indent

  Zero indent is not decreasing.
*/
void TConsole::Unindent()
{
  if (IndentLev == 0)
    return;

  --IndentLev;
}

/*
  Print newline
*/
void TConsole::Newline()
{
  printf("\n");

  NeedDelimiter = false;
  LineIsEmpty = true;
}

/*
  Print space
*/
void TConsole::Space()
{
  printf(" ");

  NeedDelimiter = false;
  LineIsEmpty = false;
}

/*
  [Internal] If needed, print newline and indentation
*/
void TConsole::ApplyStringNeeds()
{
  if (LineIsEmpty)
  {
    Freetown::PrintIndent(IndentLev);
    LineIsEmpty = false;
    NeedDelimiter = false;
  }

  if (!NeedDelimiter)
    return;

  Newline();
  Freetown::PrintIndent(IndentLev);
}

/*
  [Internal] Print space if needed.
*/
void TConsole::ApplyNumberNeeds()
{
  if (LineIsEmpty)
  {
    Freetown::PrintIndent(IndentLev);
    LineIsEmpty = false;
    NeedDelimiter = false;
  }

  if (!NeedDelimiter)
    return;

  Space();
}

/*
  Write memory segment contents
*/
void TConsole::Write(
  TMemorySegment MemSeg
)
{
  // Binary chunk may start from space
  ApplyNumberNeeds();

  me_MemorySegment::Freetown::Print(MemSeg);

  // Pend delimiter for next item
  NeedDelimiter = true;
}

/*
  Write string binary contents
*/
void TConsole::Write(
  const TChar * String
)
{
  ApplyNumberNeeds();

  printf("%s", String);

  NeedDelimiter = true;
}

/*
  Print memory segment
*/
void TConsole::Print(
  TMemorySegment MemSeg
)
{
  ApplyStringNeeds();

  me_MemorySegment::Freetown::Print(MemSeg);

  Newline();
}

/*
  Print string on new line and newline
*/
void TConsole::Print(
  const TChar * String
)
{
  ApplyStringNeeds();

  printf("%s", String);

  // Print() of string always produces newline
  Newline();
}

/*
  Print separation line

  Current implementation prints "--".
*/
void TConsole::Line()
{
  Print("--");
}

/*
  Print TUint_1
*/
void TConsole::Print(
  TUint_1 Value
)
{
  ApplyNumberNeeds();

  me_String::TString Str;

  Str.Format("%03u", Value);

  Write(Str.GetData());

  NeedDelimiter = true;
}

/*
  Print TUint_2
*/
void TConsole::Print(
  TUint_2 Value
)
{
  ApplyNumberNeeds();

  me_String::TString Str;

  Str.Format("%05u", Value);

  Write(Str.GetData());

  NeedDelimiter = true;
}

/*
  Print TUint_4
*/
void TConsole::Print(
  TUint_4 Value
)
{
  ApplyNumberNeeds();

  me_String::TString Str;

  Str.Format("%010lu", Value);

  Write(Str.GetData());

  NeedDelimiter = true;
}

/*
  Print TSint_1
*/
void TConsole::Print(
  TSint_1 Value
)
{
  ApplyNumberNeeds();

  me_String::TString Str;

  if (Value < 0)
    Str.Format("%04d", Value);
  else
    Str.Format("+%03d", Value);

  Write(Str.GetData());

  NeedDelimiter = true;
}

/*
  Print TSint_2
*/
void TConsole::Print(
  TSint_2 Value
)
{
  ApplyNumberNeeds();

  me_String::TString Str;

  if (Value < 0)
    Str.Format("%06d", Value);
  else
    Str.Format("+%05d", Value);

  Write(Str.GetData());

  NeedDelimiter = true;
}

/*
  Print TSint_4
*/
void TConsole::Print(
  TSint_4 Value
)
{
  ApplyNumberNeeds();

  me_String::TString Str;

  // "%011ld" - format strings are so readable!! I'm getting %011ld
  if (Value < 0)
    Str.Format("%011ld", Value);
  else
    Str.Format("+%010ld", Value);

  Write(Str.GetData());

  NeedDelimiter = true;
}

// ( Freetown

/*
  Print indentation
*/
void me_Console::Freetown::PrintIndent(
  TUint_1 IndentLev
)
{
  for (TUint_1 CurIndent = 0; CurIndent < IndentLev; ++CurIndent)
    printf("  ");
}

// ) Freetown

/*
  Assign instance to shared "extern" global
*/
me_Console::TConsole Console;

/*
  2024-10-03
  2024-10-06
  2024-10-08
*/
