// Serial console interface

/*
  Author: Martin Eden
  Status: sketching
  Last mod.: 2024-10-03
*/

#include "me_Console.h"

#include <HardwareSerial.h>
#include <me_BaseTypes.h>
#include <me_InstallStandardStreams.h>

using namespace me_Console;

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

  return true;
}

/*
  Print newline
*/
void TConsole::Newline()
{
  printf("\n");

  NeedDelimiter = false;
}

/*
  Print space
*/
void TConsole::Space()
{
  printf(" ");

  NeedDelimiter = false;
}

/*
  [Internal] Print newline if needed.
*/
void TConsole::ApplyStringNeeds()
{
  if (NeedDelimiter)
    Newline();
}

/*
  [Internal] Print space if needed.
*/
void TConsole::ApplyNumberNeeds()
{
  if (NeedDelimiter)
    Space();
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
  Write string binary contents
*/
void TConsole::Write(
  const TChar * String
)
{
  // Binary chunk may start from space
  ApplyNumberNeeds();

  // We're not writing length. Parser must know size of chunk.
  printf("%s", String);

  /*
    I had temptation to adjust need according to last char in chunk.
    Bad idea. Parser will have to track last byte of chunk in that case.
  */
  NeedDelimiter = true;
}

/*
  Print TUint_1
*/
void TConsole::Print(
  TUint_1 Value
)
{
  ApplyNumberNeeds();

  printf("%03u", Value);

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

  printf("%05u", Value);

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

  printf("%010lu", Value);

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

  if (Value < 0)
    printf("%03d", Value);
  if (Value >= 0)
    printf("+%03d", Value);

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

  if (Value < 0)
    printf("%06d", Value);
  if (Value >= 0)
    printf("+%05d", Value);

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

  if (Value < 0)
    printf("%011ld", Value);
  if (Value >= 0)
    printf("+%010ld", Value);

  NeedDelimiter = true;
}

/*
  2024-10-03
*/
