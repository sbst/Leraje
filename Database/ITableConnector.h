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
      class ITableConnector
      {
      public:
        ITableConnector() {};

        virtual ~ITableConnector() {};

        struct TableRow {};

        virtual void OutcomeData(uint32_t id, TableRow* data, boost::property_tree::ptree& tree) = 0;

        virtual std::shared_ptr<TableRow> IncomeData(boost::property_tree::ptree* tree) = 0;
      };
    }
  }
}
