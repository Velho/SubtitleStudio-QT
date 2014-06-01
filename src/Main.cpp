/**
 * Main point for SubtitleStudio.
 * Joel Anttila 2014
 */

#include "StudioWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    StudioWindow sw;
    sw.show();

    return a.exec();
}
