#include "databasemanager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& db_name) {
    createOrConnect(db_name);
}

void DatabaseManager::createOrConnect(const std::string& db_name) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString::fromStdString(db_name));

    if (!database.open()) {
        std::cout << "Базу данных не получилось открыть; ошибка: " << database.lastError().text().toStdString() << std::endl;
        return;
    }

    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS Users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "username TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS Posts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "post_text TEXT,"
               "FOREIGN KEY(user_id) REFERENCES Users(id))");

    query.exec("CREATE TABLE IF NOT EXISTS Comments ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "post_id INTEGER,"
               "comment_text TEXT,"
               "FOREIGN KEY(user_id) REFERENCES Users(id),"
               "FOREIGN KEY(post_id) REFERENCES Posts(id))");

    query.exec("INSERT INTO Users (username) VALUES ('user1')");
    query.exec("INSERT INTO Users (username) VALUES ('user2')");

    query.exec("INSERT INTO Posts (user_id, post_text) VALUES (1, 'Post by user1')");
    query.exec("INSERT INTO Posts (user_id, post_text) VALUES (2, 'Post by user2')");

    query.exec("INSERT INTO Comments (user_id, post_id, comment_text) VALUES (1, 1, 'Comment on user1\'s post')");
    query.exec("INSERT INTO Comments (user_id, post_id, comment_text) VALUES (2, 2, 'Comment on user2\'s post')");

    std::cout << "Подключение выполнено" << std::endl;
}

bool DatabaseManager::isValid() const {
    return database.isValid();
}
