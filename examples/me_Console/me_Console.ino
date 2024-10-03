// [me_Console] Test/demo

/*
  Author: Martin Eden
  Status: sketching
  Last mod.: 2024-10-03
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>

void setup()
{
  RunTest();
}

void loop()
{
}

// --

void RunTest()
{
  me_Console::TConsole Console;

  Console.Init(me_UartSpeeds::Arduino_Normal_Bps);

  Console.Print("[me_Console] Okay, we are here.");

  {
    TUint_1 Value;

    Console.Write("TUint_1(");

    Value = 0;
    Console.Print(Value);

    Value = 0x7F;
    Console.Print(Value);

    Value = 0xFF;
    Console.Print(Value);

    Console.Write(")");
    Console.Newline();
  }

  {
    TSint_1 Value;

    Console.Write("TSint_1(");

    Value = 0x80;
    Console.Print(Value);

    Value = 0;
    Console.Print(Value);

    Value = 0x7F;
    Console.Print(Value);

    Console.Write(")");
    Console.Newline();
  }

  {
    TUint_2 Value;

    Console.Write("TUint_2(");

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFF;
    Console.Print(Value);

    Value = 0xFFFF;
    Console.Print(Value);

    Console.Write(")");
    Console.Newline();
  }

  {
    TSint_2 Value;

    Console.Write("TSint_2(");

    Value = 0x8000;
    Console.Print(Value);

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFF;
    Console.Print(Value);

    Console.Write(")");
    Console.Newline();
  }

  {
    TUint_4 Value;

    Console.Write("TUint_4(");

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFFFFFF;
    Console.Print(Value);

    Value = 0xFFFFFFFF;
    Console.Print(Value);

    Console.Write(")");
    Console.Newline();
  }

  {
    TSint_4 Value;

    Console.Write("TSint_4(");

    Value = 0x80000000;
    Console.Print(Value);

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFFFFFF;
    Console.Print(Value);

    Console.Write(")");
    Console.Newline();
  }

  {
    Console.Write("millis():");
    Console.Print(millis());
    Console.Write("ms.");
    Console.Newline();
  }

  Console.Print("[me_Console] Done.");
}

/*
  2024-10-03
*/
