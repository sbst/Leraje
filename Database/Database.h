#pragma once

#include <memory>
#include <string.h>
#include <fstream>

#include "Database/Tables/UsersTable.h"

namespace Leraje
{
  namespace Database
  {
    class Database
    {
    public:
      static const char* FileDataPath;

      static std::shared_ptr<Database> GetDatabase();

      Database(const Database& rsh) = delete;

      Database& operator=(const Database& rhs) = delete;

      virtual ~Database();

      void LoadDatabase(std::string field);

      bool WriteToTable(std::string tableName, std::string json);

      bool ReadFromTable(std::string tableName, uint32_t id, std::string& json);

    private:
      Database();

      Tables::UsersTable* table;

      void LoadFromFile(std::string fileName, std::string tableName);

    };
  }
}
