#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::string> stringVector;

class Preprocessor
{
private:
  std::ifstream m_inputFile;
  std::ofstream m_outputFile;
  stringVector m_directives;

  // [marcusviniciusns] Using a vector instead of a stack because we must iterate over this container
  stringVector m_defineStack;

  static bool containsAll(const stringVector& vec, const stringVector& values);
public:
  explicit Preprocessor(const std::string& inputPath, const std::string& outputPath, const stringVector& directives);
  virtual ~Preprocessor();
  void preprocess();
};

#endif
