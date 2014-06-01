#ifndef STUDIOWINDOW_H
#define STUDIOWINDOW_H

#include <QMainWindow>
#include <vlc/vlc.h>

namespace Ui {
class StudioWindow;
}

class StudioWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit StudioWindow(QWidget *parent = 0);
    ~StudioWindow();

private slots:
    void onPlay();
    void onStop();

    void on_actionOpen_file_triggered();

    void on_actionQuit_triggered();

private:
    Ui::StudioWindow *ui;

    libvlc_instance_t *vlc;
    libvlc_media_player_t *vlcplr;

    void stopPlayer();
};

#endif // STUDIOWINDOW_H
