#ifndef PROJECT_H
#define PROJECT_H

#include <QtSql>

/*!
 * \brief The ProjectInfo enum
 * Project information is what Project
 * table contains.
 */
enum class ProjectInfo {
    NAME,
    AUTHOR,
    FILE
};

/*!
 * \brief The Project class
 * Represents the project.
 * Handles the Sqlite database,
 * creates new projects, loads old projects,
 * queries current  database, etc.
 *
 * TODO Split the database handling into new class.
 */
class Project {
public:
    Project(QString);
    /*!
     * \brief Project
     * Copy constructor (C++11 only)
     */
    Project(const Project&);

    ~Project();

    /*!
     * \brief init
     * Initializes the project file and tables.
     * When project is created this must be called first.
     * \param prj
     * Project information.
     * \sa enum class ProjectInfo
     * \return
     * True if queries don't fail.
     */
    void init(std::map<std::string, std::string> prj);

    QString getFile() const;

private:
    QSqlDatabase database;
    QString dbfile;
    bool fileopen;
};

#endif // PROJECT_H
