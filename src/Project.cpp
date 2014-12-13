#include "Project.h"

/*!
 * \brief String equivalent to ProjectInfo enum class(ProjectToStr).
 */
std::map<ProjectInfo, std::string> prjtostr {
    { ProjectInfo::NAME, "prjname" },
    { ProjectInfo::AUTHOR, "prjauthor" },
    { ProjectInfo::FILE, "prjfile" }
};

Project::Project(QString file) :
    dbfile{ file }
{
    database = QSqlDatabase::addDatabase("QSQLITE");
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

void Project::init(std::map<ProjectInfo, std::string> prj)
{
    // TESTING MULTIPLE QUERIES WITH ONE OBJECT.
    QSqlQuery query(database);

    // Create Project table which holds general information about the project.
    if(!query.exec("CREATE TABLE Project(idx INT AUTO INCREMENT PRIMARY KEY, key TEXT, value TEXT);")) {
        qDebug("Error while creating Project.");
        return;
    }

    // Create Subtitle table which keeps subtitle information.
    if(!query.exec("CREATE TABLE Subtitle("
                   "idx INT PRIMARY KEY, "
                   "start_frame INT, "
                   "end_frame INT, "
                   "text TEXT);")) {
        qDebug("Error while creating Subtitle.");
        return;
    }

    /**/

    // Retrieve project information from prj map.
    for(auto p : prj) {

        QString sql("INSERT INTO Project(key, value) VALUES('" +
                    QString::fromStdString(prjtostr[p.first]) + "', '" +
                    QString::fromStdString(p.second) + "');");


        query.exec(sql);
    }
}

void Project::load()
{
    //QSqlQuery query("SELECT key, value FROM Project")


}
