#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <string>

class DatabaseManager {
public:
    DatabaseManager(const std::string& db_name);
    bool isValid() const;

private:
    QSqlDatabase database;
    void createOrConnect(const std::string& db_name);
};

#endif // DATABASEMANAGER_H
