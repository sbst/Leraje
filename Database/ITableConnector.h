#pragma once

#include <boost/property_tree/json_parser.hpp>
#include <memory>
#include <string>
#include <algorithm>
#include <map>

namespace Leraje
{
  namespace Database
  {
    namespace Tables
    {
      class JsonTree : public boost::property_tree::ptree
      {
      public:
        template <typename T>
        T get(const char* field)
        {
          return boost::property_tree::ptree::get<T>(field);
        }
      };

      template <>
      inline std::string JsonTree::get<std::string>(const char* field)
      {
        std::string result = boost::property_tree::ptree::get<std::string>(field);
        std::string data(result);
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        if (data == "null") throw std::invalid_argument("String can not be null");
        return result;
      }

      class ITableConnector
      {
      public:
        ITableConnector() {};

        virtual ~ITableConnector() {};

        struct TableRow {};

        virtual void OutcomeData(TableRow* data, JsonTree& tree) = 0;

        virtual std::shared_ptr<TableRow> IncomeData(JsonTree* tree) = 0;

        virtual void UpdateData(TableRow* row, JsonTree* tree) = 0;
      };
    }
  }
}
