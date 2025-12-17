#ifndef NEONCOIN_DB_H
#define NEONCOIN_DB_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <cstdint>

class CDatabase
{
public:
    explicit CDatabase(const std::string& path);
    ~CDatabase();

    void Write(const std::vector<uint8_t>& key,
               const std::vector<uint8_t>& value);

    bool Read(const std::vector<uint8_t>& key,
              std::vector<uint8_t>& out);

    void Delete(const std::vector<uint8_t>& key);

private:
    void CreateTable();

    sqlite3* mDB = nullptr;
};

#endif

