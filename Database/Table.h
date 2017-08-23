#pragma once

#include "Database/ITableConnector.h"

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
        Table(ITableConnector* connector);

        ~Table();

        bool WriteToTable(std::string json);

        bool LoadToTable(std::string json);

        bool ReadFromTable(uint32_t id, std::string& json);

      private:
        uint32_t lastId;

        std::map<uint32_t, std::shared_ptr<ITableConnector::TableRow>> table;

        ITableConnector* connector;

        std::shared_ptr<ITableConnector::TableRow> FromJson(std::string json, int32_t* foundId = nullptr);

        bool ToJson(uint32_t id, std::shared_ptr<ITableConnector::TableRow> row, std::string& json);

        bool IsIdExist(int32_t id);
      };
    }
  }
}
