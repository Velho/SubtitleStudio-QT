#include "NewProjectWizard.h"
#include <QtWidgets>

NewProjectWizard::NewProjectWizard(QWidget *parent)
    : QWizard{ parent }
{
    addPage(new ProjectInfoPage);
    setWindowTitle(tr("New Project"));
}

void NewProjectWizard::accept()
{
    QString file
        { QString::fromStdString(getProjectFilename(field("prjFile").toString())) };

    project = new Project(file);

    std::map<ProjectInfo, std::string> prjinfo
    {
        { ProjectInfo::NAME, field("prjName").toString().toStdString() },
        { ProjectInfo::AUTHOR, field("prjAuthor").toString().toStdString() },
        { ProjectInfo::FILE, field("prjFile").toString().toStdString() }
    };

    project->init(prjinfo);
    QDialog::accept();
}

Project *NewProjectWizard::getProject() {
    return project;
}

std::string NewProjectWizard::getProjectFilename(QString file)
{
    std::string filename { file.toStdString() };

    unsigned found = filename.rfind(".");
    if(found != std::string::npos)
        filename.replace(found, filename.size(), ".studio");

    return filename;
}

ProjectInfoPage::ProjectInfoPage(QWidget *parent)
    : QWizardPage{ parent },
      prjNameLabel{ new QLabel(tr("Project name")) },
      prjAuthorLabel{ new QLabel(tr("Project Author")) },
      prjFileLabel{ new QLabel(tr("File name (with extension)")) },
      prjNameTxt{ new QLineEdit },
      prjAuthorTxt{ new QLineEdit },
      prjFileTxt{ new QLineEdit }
{
    setTitle(tr("Provide Project information"));

    prjNameLabel->setBuddy(prjNameTxt);
    prjAuthorLabel->setBuddy(prjAuthorTxt);
    prjFileLabel->setBuddy(prjFileTxt);

    // Width of QLineEdit widgets.
    prjNameTxt->setFixedWidth(300);
    prjAuthorTxt->setFixedWidth(300);
    prjFileTxt->setFixedWidth(300);

    QVBoxLayout *layout = new QVBoxLayout;
    // Add labels to layout.
    layout->addWidget(prjNameLabel);
    layout->addWidget(prjNameTxt);
    layout->addWidget(prjAuthorLabel);
    layout->addWidget(prjAuthorTxt);
    layout->addWidget(prjFileLabel);
    layout->addWidget(prjFileTxt);

    setLayout(layout);

    registerField("prjAuthor", prjAuthorTxt);
    registerField("prjName", prjNameTxt);
    registerField("prjFile", prjFileTxt);
}
