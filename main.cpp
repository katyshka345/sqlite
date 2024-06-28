#include <QCoreApplication>
#include "databasemanager.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cctype>

using namespace std;

void sql_commands(QSqlDatabase database) {
    database.open();

    while (true) {
        std::string command;
        std::cout << "Введите SQL-запрос (close - для завершения): ";
        std::getline(std::cin, command);

        std::transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "CLOSE") {
            std::cout << "Завершение программы." << std::endl;
            break;
        }

        QSqlQuery query(database);

        if (!query.exec(QString::fromStdString(command))) {
            std::cerr << "Ошибка выполнения запроса: " << query.lastError().text().toStdString() << std::endl;
        } else {
            std::cout << "Запрос выполнен успешно" << std::endl;

            if (command.find("SELECT") == 0) {
                QSqlRecord rec = query.record();
                int columnCount = rec.count();

                for (int i = 0; i < columnCount; ++i) {
                    std::cout << rec.fieldName(i).toStdString() << "\t";
                }
                std::cout << std::endl;

                while (query.next()) {
                    for (int i = 0; i < columnCount; ++i) {
                        std::cout << query.value(i).toString().toStdString() << "\t";
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    SetConsoleOutputCP(CP_UTF8);

    string name_database;
    std::cout << "Введите название БД для подключения/создания: " << std::endl;
    std::getline(std::cin, name_database);

    DatabaseManager dbManager(name_database);

    if (!dbManager.isValid()) {
        std::cout << "Перезапустите программу" << std::endl;
        return 1;
    }

    sql_commands(QSqlDatabase::database());

    return a.exec();
}
