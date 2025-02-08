#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cstring>

#include <gtest/gtest.h>
#include "/home/durjoy/Desktop/programming_task40/lib/ArgParser.h"

using namespace ArgumentParser;

// std::vector<std::string> SplitString(const std::string& str) {
//     std::istringstream iss(str);
//     return {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
// }

// /*
//     Helper function to convert std::vector<std::string> to argc and argv.
// */
// void ConvertToArgcArgv(const std::vector<std::string>& args, int& argc, char**& argv) {
//     argc = static_cast<int>(args.size());
//     argv = new char*[argc];
//     for (int i = 0; i < argc; ++i) {
//         argv[i] = new char[args[i].size() + 1];
//         std::strcpy(argv[i], args[i].c_str());
//     }
// }

// /*
//     Helper function to clean up allocated argv memory.
// */
// void CleanupArgv(int argc, char** argv) {
//     for (int i = 0; i < argc; ++i) {
//         delete[] argv[i];
//     }
//     delete[] argv;
// }

// TEST(ArgParserTestSuite, EmptyTest) {
//     ArgParser parser("My Empty Parser");

//     int argc;
//     char** argv;
//     auto args = SplitString("app");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, StringTest) {
//     ArgParser parser("My Parser");
//     parser.AddStringArgument("param1");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --param1=value1");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetStringValue("param1"), "value1");

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, ShortNameTest) {
//     ArgParser parser("My Parser");
//     parser.AddStringArgument('p', "param1");

//     int argc;
//     char** argv;
//     auto args = SplitString("app -p=value1");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetStringValue("param1"), "value1");

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, DefaultTest) {
//     ArgParser parser("My Parser");
//     parser.AddStringArgument("param1").Default("value1");

//     int argc;
//     char** argv;
//     auto args = SplitString("app");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetStringValue("param1"), "value1");

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, NoDefaultTest) {
//     ArgParser parser("My Parser");
//     parser.AddStringArgument("param1");

//     int argc;
//     char** argv;
//     auto args = SplitString("app");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_FALSE(parser.Parse(argc, argv));

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, StoreValueTest) {
//     ArgParser parser("My Parser");
//     std::string value;
//     parser.AddStringArgument("param1").StoreValue(value);

//     int argc;
//     char** argv;
//     auto args = SplitString("app --param1=value1");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(value, "value1");

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, MultiStringTest) {
//     ArgParser parser("My Parser");
//     std::string value;
//     parser.AddStringArgument("param1").StoreValue(value);
//     parser.AddStringArgument('a', "param2");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --param1=value1 --param2=value2");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetStringValue("param2"), "value2");

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, IntTest) {
//     ArgParser parser("My Parser");
//     parser.AddIntArgument("param1");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --param1=100500");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetIntValue("param1"), 100500);

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, MultiValueTest) {
//     ArgParser parser("My Parser");
//     std::vector<int> int_values;
//     parser.AddIntArgument('p', "param1").MultiValue().StoreValues(int_values);

//     int argc;
//     char** argv;
//     auto args = SplitString("app --param1=1 --param1=2 --param1=3");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetIntValue("param1", 0), 1);
//     ASSERT_EQ(int_values[1], 2);
//     ASSERT_EQ(int_values[2], 3);

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, MinCountMultiValueTest) {
//     ArgParser parser("My Parser");
//     std::vector<int> int_values;
//     size_t MinArgsCount = 10;
//     parser.AddIntArgument('p', "param1").MultiValue(MinArgsCount).StoreValues(int_values);

//     int argc;
//     char** argv;
//     auto args = SplitString("app --param1=1 --param1=2 --param1=3");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_FALSE(parser.Parse(argc, argv));

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, FlagTest) {
//     ArgParser parser("My Parser");
//     parser.AddFlag('f', "flag1");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --flag1");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_TRUE(parser.GetFlag("flag1"));

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, FlagsTest) {
//     ArgParser parser("My Parser");
//     bool flag3 = false;
//     parser.AddFlag('a', "flag1");
//     parser.AddFlag('b', "flag2").Default(true);
//     parser.AddFlag('c', "flag3").StoreValue(flag3);

//     int argc;
//     char** argv;
//     auto args = SplitString("app -ac");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_TRUE(parser.GetFlag("flag1"));
//     ASSERT_TRUE(parser.GetFlag("flag2"));
//     ASSERT_TRUE(flag3);

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, PositionalArgTest) {
//     ArgParser parser("My Parser");
//     std::vector<int> values;
//     parser.AddIntArgument("Param1").MultiValue(1).Positional().StoreValues(values);

//     int argc;
//     char** argv;
//     auto args = SplitString("app 1 2 3 4 5");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(values[0], 1);
//     ASSERT_EQ(values[2], 3);
//     ASSERT_EQ(values.size(), 5);

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, PositionalAndNormalArgTest) {
//     ArgParser parser("My Parser");
//     std::vector<int> values;
//     parser.AddFlag('f', "flag", "Flag");
//     parser.AddIntArgument('n', "number", "Some Number");
//     parser.AddIntArgument("Param1").MultiValue(1).Positional().StoreValues(values);

//     int argc;
//     char** argv;
//     auto args = SplitString("app -n 0 1 2 3 4 5 -f");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_TRUE(parser.GetFlag("flag"));
//     ASSERT_EQ(parser.GetIntValue("number"), 0);
//     ASSERT_EQ(values[0], 1);
//     ASSERT_EQ(values[2], 3);
//     ASSERT_EQ(values.size(), 5);

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, RepeatedParsingTest) {
//     ArgParser parser("My Parser");
//     parser.AddHelp('h', "help", "Some Description about program");
//     parser.AddStringArgument('i', "input", "File path for input file");
//     parser.AddStringArgument('o', "output", "File path for output directory");
//     parser.AddFlag('s', "flag1", "Read first number");
//     parser.AddFlag('p', "flag2", "Read second number");
//     parser.AddIntArgument("number", "Some Number");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --number 2 -s -i test -o=test");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));

//     if (parser.GetFlag("flag1")) {
//         parser.AddIntArgument("first", "First Number");
//     } else if (parser.GetFlag("flag2")) {
//         parser.AddIntArgument("second", "Second Number");
//     }

//     CleanupArgv(argc, argv);

//     // Parse again with the new argument
//     args = SplitString("app --number 2 -s -i test -o=test --first=52");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_EQ(parser.GetIntValue("first"), 52);

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, HelpTest) {
//     ArgParser parser("My Parser");
//     parser.AddHelp('h', "help", "Some Description about program");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --help");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));
//     ASSERT_TRUE(parser.Help());

//     CleanupArgv(argc, argv);
// }

// TEST(ArgParserTestSuite, HelpStringTest) {
//     ArgParser parser("My Parser");
//     parser.AddHelp('h', "help", "Some Description about program");
//     parser.AddStringArgument('i', "input", "File path for input file").MultiValue(1);
//     parser.AddFlag('s', "flag1", "Use some logic").Default(true);
//     parser.AddFlag('p', "flag2", "Use some logic");
//     parser.AddIntArgument("number", "Some Number");

//     int argc;
//     char** argv;
//     auto args = SplitString("app --help");
//     ConvertToArgcArgv(args, argc, argv);

//     ASSERT_TRUE(parser.Parse(argc, argv));

//     // Optional: Verify the help description format
//     // Since the formatting might vary, we can print it out for manual inspection
//     // std::cout << parser.HelpDescription() << std::endl;

//     CleanupArgv(argc, argv);
// }


std::vector<std::string> SplitString(const std::string& str) {
}


TEST(ArgParserTestSuite, EmptyTest) {
}


TEST(ArgParserTestSuite, StringTest) {
}


TEST(ArgParserTestSuite, ShortNameTest) {
}


TEST(ArgParserTestSuite, DefaultTest) {
    ArgParser parser("My Parser");
    parser.AddStringArgument("param1").Default("value1");

    ASSERT_TRUE(parser.Parse(SplitString("app")));
    ASSERT_EQ(parser.GetStringValue("param1"), "value1");
}


TEST(ArgParserTestSuite, NoDefaultTest) {
    ArgParser parser("My Parser");
    parser.AddStringArgument("param1");

    int argc;
    char** argv;
    auto args = SplitString("app");
    ConvertToArgcArgv(args, argc, argv);

    ASSERT_FALSE(parser.Parse(argc, argv));

    CleanupArgv(argc, argv);
}


TEST(ArgParserTestSuite, StoreValueTest) {
}


TEST(ArgParserTestSuite, MultiStringTest) {
}


TEST(ArgParserTestSuite, IntTest) {
    ArgParser parser("My Parser");
    parser.AddIntArgument("param1");

    ASSERT_TRUE(parser.Parse(SplitString("app --param1=100500")));
    ASSERT_EQ(parser.GetIntValue("param1"), 100500);
}


TEST(ArgParserTestSuite, MultiValueTest) {
}


TEST(ArgParserTestSuite, MinCountMultiValueTest) {
}


TEST(ArgParserTestSuite, FlagTest) {
    ArgParser parser("My Parser");
    parser.AddFlag('f', "flag1");

    ASSERT_TRUE(parser.Parse(SplitString("app --flag1")));
    ASSERT_TRUE(parser.GetFlag("flag1"));
}


TEST(ArgParserTestSuite, FlagsTest) {
}


TEST(ArgParserTestSuite, PositionalArgTest) {
}


TEST(ArgParserTestSuite, PositionalAndNormalArgTest) {
    ArgParser parser("My Parser");
    std::vector<int> values;
    parser.AddFlag('f', "flag", "Flag");
    parser.AddIntArgument('n', "number", "Some Number");
    parser.AddIntArgument("Param1").MultiValue(1).Positional().StoreValues(values);

    ASSERT_TRUE(parser.Parse(SplitString("app -n 0 1 2 3 4 5 -f")));
    ASSERT_TRUE(parser.GetFlag("flag"));
    ASSERT_EQ(parser.GetIntValue("number"), 0);
    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[2], 3);
    ASSERT_EQ(values.size(), 5);
}


TEST(ArgParserTestSuite, RepeatedParsingTest) {
    ArgParser parser("My Parser");
    parser.AddHelp('h', "help", "Some Description about program");
    parser.AddStringArgument('i', "input", "File path for input file");
    parser.AddStringArgument('o', "output", "File path for output directory");
    parser.AddFlag('s', "flag1", "Read first number");
    parser.AddFlag('p', "flag2", "Read second number");
    parser.AddIntArgument("number", "Some Number");

    ASSERT_TRUE(parser.Parse(SplitString("app --number 2 -s -i test -o=test")));

    if (parser.GetFlag("flag1")) {
      parser.AddIntArgument("first", "First Number");
    } else if (parser.GetFlag("flag2")) {
      parser.AddIntArgument("second", "Second Number");
    }

    ASSERT_TRUE(parser.Parse(SplitString("app --number 2 -s -i test -o=test --first=52")));
    ASSERT_EQ(parser.GetIntValue("first"), 52);
}


TEST(ArgParserTestSuite, HelpTest) {
    ArgParser parser("My Parser");
    parser.AddHelp('h', "help", "Some Description about program");

    ASSERT_TRUE(parser.Parse(SplitString("app --help")));
    ASSERT_TRUE(parser.Help());
}


TEST(ArgParserTestSuite, HelpStringTest) {
    ArgParser parser("My Parser");
    parser.AddHelp('h', "help", "Some Description about program");
    parser.AddStringArgument('i', "input", "File path for input file").MultiValue(1);
    parser.AddFlag('s', "flag1", "Use some logic").Default(true);
    parser.AddFlag('p', "flag2", "Use some logic");
    parser.AddIntArgument("numer", "Some Number");


    ASSERT_TRUE(parser.Parse(SplitString("app --help")));
    // Проверка закоментирована намеренно. Ождиается, что результат вызова функции будет приблизительно такой же,
    // но не с точностью до символа

    // ASSERT_EQ(
    //     parser.HelpDescription(),
    //     "My Parser\n"
    //     "Some Description about program\n"
    //     "\n"
    //     "-i,  --input=<string>,  File path for input file [repeated, min args = 1]\n"
    //     "-s,  --flag1,  Use some logic [default = true]\n"
    //     "-p,  --flag2,  Use some logic\n"
    //     "     --number=<int>,  Some Number\n"
    //     "\n"
    //     "-h, --help Display this help and exit\n"
    // );
}