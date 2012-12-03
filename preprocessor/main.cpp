#include <iostream>
#include <string>

#include "preprocessor.h"

static const std::string inputPathPrefix("/I");
static const std::string outputPathPrefix("/O");
static const std::string directivePrefix("/D");

static void readArg(int argc, char** argv, const std::string& argPrefix, std::string& argOut);
static void readArgList(int argc, char** argv, const std::string& argPrefix, stringVector& args);
static void showUsage();
static bool containsAll(const stringVector& vec, const stringVector& values);

int main(int argc, char** argv)
{
  stringVector directives;
  std::string inputPath, outputPath;

  readArg(argc, argv, inputPathPrefix, inputPath);
  readArg(argc, argv, outputPathPrefix, outputPath);
  readArgList(argc, argv, directivePrefix, directives);

  if (directives.size() == 0 || inputPath.length() == 0 || outputPath.length() == 0)
  {
    showUsage();
    return -1;
  }

  Preprocessor preprocessor(inputPath, outputPath, directives);
  try
  {
    preprocessor.preprocess();
  }
  catch (std::runtime_error& error)
  {
    std::cout << error.what() << std::endl;
    return -1;
  }

  return 0;
}

void readArg(int argc, char** argv, const std::string& argPrefix, std::string& argOut)
{
  for (int i = 1; i < argc; i++)
  {
    const char* arg = argv[i];
    std::size_t len = strlen(arg);
    std::string::size_type prefixLen = argPrefix.length();

    if (len <= prefixLen || strncmp(arg, argPrefix.c_str(), prefixLen) != 0)
    {
      continue;
    }

    arg = &arg[2];
    argOut = arg;
    break;
  }
}

void readArgList(int argc, char** argv, const std::string& argPrefix, stringVector& args)
{
  for (int i = 1; i < argc; i++)
  {
    const char* arg = argv[i];
    std::size_t len = strlen(arg);
    std::string::size_type prefixLen = argPrefix.length();

    if (len <= prefixLen || strncmp(arg, argPrefix.c_str(), prefixLen) != 0)
    {
      continue;
    }

    arg = &arg[2];
    args.push_back(arg);
  }
}

void showUsage()
{
  std::cout << "preprocessor /Ddirective1 /Ddirective2 .. /DdiretiveN /Iinput_path /Ooutput_path" << std::endl;
}

