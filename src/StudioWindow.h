#ifndef STUDIOWINDOW_H
#define STUDIOWINDOW_H

#include <QtGui>

#include <QMainWindow>
#include <QMessageBox>

#include <vlc/vlc.h>

namespace Ui {
class StudioWindow;
}

class Project;

/**
 * Wikipage about SubRip .srt format: en.wikipedia.org/wiki/SubRip
 * Plain structure of .srt format:
 *
 * 1
 * 00:00:10,500 --> 00:00:13,000
 * Elephant's Dream
 * 2
 * 00:00:15,000 --> 00:00:18,000
 * At the left we can see...
 *
 *
 * TODO Implement sliders.
 * TODO TimeEdit widget could be good tool to track playback time.
 * @brief The StudioWindow class
 */
class StudioWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit StudioWindow(QWidget *parent = 0);
    ~StudioWindow();

private slots:
    void onPlay();
    void onStop();

    void on_actionQuit_triggered();

    void updateInterface();

    void on_volSlider_sliderMoved(int position);

    void on_timeSlider_valueChanged(int value);
    void on_secSlider_valueChanged(int value);
    void on_msSlider_valueChanged(int value);

    /*!
     * \brief on_boldstyle_btn_clicked
     * Apply bold style on subtitle.
     */
    void on_boldstyle_btn_clicked();
    /*!
     * \brief on_italicstyle_btn_clicked
     * Apply italic style on subtitle.
     */
    void on_italicstyle_btn_clicked();
    /*!
     * \brief on_underlinestyle_btn_clicked
     * Apply underline style on subtitle.
     */
    void on_underlinestyle_btn_clicked();

    /*!
     * \brief on_actionNew_project_triggered
     * Display New Project Wizard.
     */
    void on_actionNew_project_triggered();

private:
    Ui::StudioWindow *ui;
    QTimer *timer;

    Project *project;

    libvlc_instance_t *vlc;
    libvlc_media_player_t *vlcplr;

    bool playback;
    bool paused;
    uint64_t currtime;
    float fps = 0.0;

    QString makeURI(QString path) {
        return "file:///" + path;
    }

    void updateVolLabel(int);
    void updateTimeLabel(long);

    void startPlayer();
    void stopPlayer();

    void openMedia(QString);
};

#endif // STUDIOWINDOW_H
