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
    QDialog::accept();
}

Project *NewProjectWizard::getProject() {
    //return new Project(project);
    return nullptr;
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

    QVBoxLayout *layout = new QVBoxLayout;
    // Add labels to layout.
    layout->addWidget(prjNameLabel);
    layout->addWidget(prjNameTxt);
    layout->addWidget(prjAuthorLabel);
    layout->addWidget(prjAuthorTxt);
    layout->addWidget(prjFileLabel);
    layout->addWidget(prjFileTxt);

    setLayout(layout);
}
