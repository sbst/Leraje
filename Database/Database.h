#pragma once

#include <memory>

namespace Leraje
{
  namespace Database
  {
    class Database
    {
    public:
      static std::shared_ptr<Database> GetDatabase();

      Database(const Database& rsh) = delete;

      Database& operator=(const Database& rhs) = delete;

      virtual ~Database();

    private:
      Database();

    };
  }
}
