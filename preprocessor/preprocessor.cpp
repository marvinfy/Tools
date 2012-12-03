#include "preprocessor.h"

static const std::string tokenIfDef("#ifdef");
static const std::string tokenEndIf("#endif");

Preprocessor::Preprocessor(const std::string& inputPath, const std::string& outputPath, const stringVector& directives):
m_inputFile(inputPath),  m_outputFile(outputPath), m_directives(directives)
{
}

Preprocessor::~Preprocessor()
{
  m_inputFile.close();
  m_outputFile.flush();
  m_outputFile.close();
}

void Preprocessor::preprocess()
{
  //std::size_t lineNumber = 0;

  while (!m_inputFile.eof())
  {
    //lineNumber++;

    std::string line;
    std::getline(m_inputFile, line);

    std::size_t posIfDef = line.find(tokenIfDef);
    std::size_t posEndIf = line.find(tokenEndIf);

    if (posIfDef != std::string::npos)
    {
      // [marcusviniciusns] Only one blank space allowed after #ifdef
      std::size_t directiveStart = posIfDef + tokenIfDef.length() + 1;

      if (line.length() > directiveStart)
      {
        std::string directive(line.substr(directiveStart));
        m_defineStack.push_back(directive);      
      }
      else
      {
        std::string error("fatal error: #ifdef expected an identifier");
        m_outputFile << error << std::endl;
        throw std::runtime_error(error);
      }
    }
    else if (posEndIf != std::string::npos)
    {
      if (m_defineStack.empty())
      {
        std::string error("fatal error: unexpected #endif");
        m_outputFile << error << std::endl;
        throw std::runtime_error(error);
      }
      m_defineStack.pop_back();
    }
    else if (m_defineStack.empty() || containsAll(m_directives, m_defineStack))
    {
      m_outputFile << line << std::endl;
    }
  }
}

bool Preprocessor::containsAll(const stringVector& vec, const stringVector& values)
{
  for (stringVector::const_iterator it1 = values.begin(); it1 != values.end(); ++it1)
  {
    const std::string& value1 = *it1;
    bool found = false;

    for (stringVector::const_iterator it2 = vec.begin(); it2 != vec.end(); ++it2)
    {
      const std::string& value2 = *it2;

      if (value1 == value2)
      {
        found = true;
        break;
      }
    }

    if (!found)
    {
      return false;
    }
  }

  return true;
}
