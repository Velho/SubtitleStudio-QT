#include "Project.h"
#include <iostream>

Project::Project(QString file) :
    database{ QSqlDatabase::addDatabase("QSQLITE") },
    dbfile{ file }
{
    database.setDatabaseName(dbfile);
    database.open();
}

Project::Project(const Project &p) : Project(p.getFile())
{ }

Project::~Project()
{
    if(database.isOpen() == true)
        database.close(); // Close the database.
}

QString Project::getFile() const
{
    return dbfile;
}

void Project::init(std::map<std::string, std::string> prj)
{
    // TESTING MULTIPLE QUERIES WITH ONE OBJECT.
    QSqlQuery query(database);

    // Create Project table which holds general information about the project.
    if(!query.exec("CREATE TABLE Project(idx INT AUTO INCREMENT PRIMARY KEY, key TEXT, value TEXT);")) {
        std::cout << "Error while creating Project." << std::endl;
        return;
    }

    // Create Subtitle table which keeps subtitle information.
    if(!query.exec("CREATE TABLE Subtitle("
                   "idx INT PRIMARY KEY, "
                   "start_frame INT, "
                   "end_frame INT, "
                   "text TEXT);")) {
        std::cout << "Error while creating Subtitle." << std::endl;
        return;
    }

    // Retrieve project information from prj map.
    for(auto p : prj) {
        QString sql("INSERT INTO Project(key, value) VALUES('" +
                    QString::fromStdString(p.first) + "', '" + QString::fromStdString(p.second) + "');");
        std::cout << sql.toStdString() << std::endl;
        query.exec(sql);
    }
}
