#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QWizard>

#include "Project.h"

class QLabel;
class QLineEdit;


// TODO Jäit tänne. Luo uusi projekti!

/*!
 * \brief The NewProjectWizard class
 * New Project Wizard helps user to generate
 * fresh project. Wizard is simple, only
 * Intro, Video selection,
 */
class NewProjectWizard : public QWizard {

    Q_OBJECT

public:
    NewProjectWizard(QWidget *parent = nullptr);

    void accept();

    Project *getProject();

private:
    Project *project;

    /*!
     * \brief getProjectFilename
     * Forms a filename for Project file.
     * \return
     * New filename from projects file name.
     * E.g. File.name.mp4 -> File.name.studio
     */
    std::string getProjectFilename(QString);
};

/*!
 * \brief The ProjectInfoPage class
 * Provides information of the Project.
 * Project name, author, vids file name.
 */
class ProjectInfoPage : public QWizardPage {
    Q_OBJECT

public:
    ProjectInfoPage(QWidget *parent = nullptr);
private:
    QLabel *prjNameLabel;
    QLabel *prjAuthorLabel;
    QLabel *prjFileLabel;

    QLineEdit *prjNameTxt;
    QLineEdit *prjAuthorTxt;
    QLineEdit *prjFileTxt;
};


#endif // NEWPROJECTWIZARD_H
