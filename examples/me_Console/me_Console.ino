// [me_Console] Test/demo

/*
  Author: Martin Eden
  Status: sketched
  Last mod.: 2024-10-08
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

  Console.Print("[me_Console] demo.");
  Console.Line();

  Console.Indent();

  Console.Print("We'll show how values are represented for base types.");
  Console.Print("We'll use indentation too.");
  Console.Line();

  Console.Indent();

  {
    TUint_1 Value;

    Console.Write("TUint_1 ( ");

    Value = 0;
    Console.Print(Value);

    Value = 0x7F;
    Console.Print(Value);

    Value = 0xFF;
    Console.Print(Value);

    Console.Write(" )");
    Console.Newline();
  }

  {
    TSint_1 Value;

    Console.Write("TSint_1 ( ");

    Value = 0x80;
    Console.Print(Value);

    Value = 0;
    Console.Print(Value);

    Value = 0x7F;
    Console.Print(Value);

    Console.Write(" )");
    Console.Newline();
  }

  {
    TUint_2 Value;

    Console.Write("TUint_2 ( ");

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFF;
    Console.Print(Value);

    Value = 0xFFFF;
    Console.Print(Value);

    Console.Write(" )");
    Console.Newline();
  }

  {
    TSint_2 Value;

    Console.Write("TSint_2 ( ");

    Value = 0x8000;
    Console.Print(Value);

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFF;
    Console.Print(Value);

    Console.Write(" )");
    Console.Newline();
  }

  {
    TUint_4 Value;

    Console.Write("TUint_4 ( ");

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFFFFFF;
    Console.Print(Value);

    Value = 0xFFFFFFFF;
    Console.Print(Value);

    Console.Write(" )");
    Console.Newline();
  }

  {
    TSint_4 Value;

    Console.Write("TSint_4 ( ");

    Value = 0x80000000;
    Console.Print(Value);

    Value = 0;
    Console.Print(Value);

    Value = 0x7FFFFFFF;
    Console.Print(Value);

    Console.Write(" )");
    Console.Newline();
  }

  Console.Unindent();

  Console.Line();

  Console.Unindent();

  Console.Line();

  Console.Print("[me_Console] That's all folks!");
}

/*
  2024-10-03
  2024-10-06
  2024-10-08
*/
