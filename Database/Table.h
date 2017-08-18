#pragma once

#include <string.h>

namespace Leraje
{
  namespace Database
  {
    class Table
    {
    protected:

      Table();

      virtual ~Table();

      //void WriteToTable(std::string json) = 0;

      //void ReadFromTable(std::string& json) = 0;
    };
  }
}
