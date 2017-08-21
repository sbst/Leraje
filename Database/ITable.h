#pragma once

//#include "Database/ITable.h"

#include <boost/property_tree/json_parser.hpp>

#include <memory>
#include <string.h>
#include <map>

namespace Leraje
{
  namespace Database
  {
    namespace Tables
    {
      class ITable
      {
      public:
        ITable() explicit;

        ~ITable() {};

        struct Data;

        void OutcomeData(uint32_t id, Data* data, boost::property_tree::ptree& tree);

        void IncomeData(boost::property_tree::ptree* tree, Data& data);
      };
    }
  }
}
