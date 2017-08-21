#pragma once

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
      class Table
      {
      public:
        Table();

        ~Table();

        typedef struct
        {
          std::string email;
          std::string firstName;
          std::string lastName;
          char gender;
          int64_t birthDate;
        } UsersData;

        bool WriteToTable(std::string json);

        bool ReadFromTable(uint32_t id, std::string& json);

      private:
        uint32_t lastId;

        //typedef std::vector<UsersData*> UsersRows;
        typedef std::map<uint32_t, UsersData*> UsersRows;

        UsersRows* table;

        bool FromJson(std::string json, UsersData& row);

        bool ToJson(uint32_t id, UsersData* row, std::string& json);

        void OutcomeData(uint32_t id, UsersData* data, boost::property_tree::ptree& tree); // to be defined in UserComponent

        void IncomeData(boost::property_tree::ptree* tree, UsersData& data); // to be defined in UserComponent
      };
    }
  }
}
