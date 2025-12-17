#include "db.h"
#include <stdexcept>

CDatabase::CDatabase(const std::string& path)
{
    if (sqlite3_open(path.c_str(), &mDB) != SQLITE_OK)
        throw std::runtime_error("sqlite open failed");

    sqlite3_exec(mDB, "PRAGMA journal_mode=WAL;", nullptr, nullptr, nullptr);
    sqlite3_exec(mDB, "PRAGMA synchronous=NORMAL;", nullptr, nullptr, nullptr);

    CreateTable();
}

CDatabase::~CDatabase()
{
    if (mDB)
        sqlite3_close(mDB);
}

void CDatabase::CreateTable()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS kvdb ("
        "key BLOB PRIMARY KEY,"
        "value BLOB NOT NULL"
        ");";

    char* err = nullptr;
    if (sqlite3_exec(mDB, sql, nullptr, nullptr, &err) != SQLITE_OK)
    {
        std::string msg = err ? err : "";
        sqlite3_free(err);
        throw std::runtime_error(msg);
    }
}

void CDatabase::Write(const std::vector<uint8_t>& key,
                      const std::vector<uint8_t>& value)
{
    const char* sql =
        "INSERT INTO kvdb(key,value) VALUES(?,?) "
        "ON CONFLICT(key) DO UPDATE SET value=excluded.value;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(mDB, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("write prepare failed");

    sqlite3_bind_blob(stmt, 1, key.data(), (int)key.size(), SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 2, value.data(), (int)value.size(), SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("write step failed");
    }

    sqlite3_finalize(stmt);
}

bool CDatabase::Read(const std::vector<uint8_t>& key,
                     std::vector<uint8_t>& out)
{
    const char* sql = "SELECT value FROM kvdb WHERE key=?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(mDB, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("read prepare failed");

    sqlite3_bind_blob(stmt, 1, key.data(), (int)key.size(), SQLITE_TRANSIENT);

    bool found = false;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const uint8_t* data =
            static_cast<const uint8_t*>(sqlite3_column_blob(stmt, 0));
        int size = sqlite3_column_bytes(stmt, 0);

        out.assign(data, data + size);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

void CDatabase::Delete(const std::vector<uint8_t>& key)
{
    const char* sql = "DELETE FROM kvdb WHERE key=?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(mDB, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("delete prepare failed");

    sqlite3_bind_blob(stmt, 1, key.data(), (int)key.size(), SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("delete step failed");
    }

    sqlite3_finalize(stmt);
}

