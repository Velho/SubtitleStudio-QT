#include "StudioWindow.h"
#include "ui_StudioWindow.h"

#include <QFileDialog>

// For printing debug stuff on output.
#include <iostream>

StudioWindow::StudioWindow(QWidget *parent) :
    QMainWindow(parent), vlcplr(NULL), timer(new QTimer(this)),
    ui(new Ui::StudioWindow)
{
    vlc = libvlc_new(0, NULL);

    if(vlc == NULL) {
        QMessageBox::critical(this, "SubtitleStudio", "Vlc instance not initialized.");
        QApplication::exit(1); // Return 1 as error code.
    }

    ui->setupUi(this);

    // Draw black screen to videoWidget.
    ui->videoWidget->setAutoFillBackground(true);
    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    ui->videoWidget->setPalette(plt);

    QObject::connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(onPlay()));
    QObject::connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterface()));
}

StudioWindow::~StudioWindow() {
    if(vlcplr) {
        libvlc_media_player_stop(vlcplr);
        libvlc_media_player_release(vlcplr);
    }
    if(vlc)
        libvlc_release(vlc);

    delete timer;
    delete ui;
}

void StudioWindow::onPlay() {
    startPlayer();
}

void StudioWindow::onStop() {
    stopPlayer();
}

/**
 * Triggers when menu "Open file" is triggered.
 * Loads file from hard drive.
 *
 * TODO Add support for opening multpile files into a playlist.
 * TODO Add multi platform.
 * TODO Even if media is not selected and this event is triggered,
 * play button's text get changed from play to pause. (BUG)
 *
 * @brief StudioWindow::on_actionOpen_file_triggered
 */
void StudioWindow::on_actionOpen_file_triggered() {
    QString file = QFileDialog::getOpenFileName(this, tr("Open a file"));

    if(vlcplr && libvlc_media_player_is_playing(vlcplr))
        stopPlayer();

    // Create new media and give it file's path as utf8 const char*.
    //PNT(test_func(file).toStdString());
    QString furi = makeURI(file);
    libvlc_media_t *media = libvlc_media_new_location(vlc, furi.toUtf8().constData());

    if(!media) // Return on error.
        return;

    vlcplr = libvlc_media_player_new_from_media(media);

    libvlc_media_release(media);

    // FOLLOWING WORKS ONLY ON WINDOWS.
    // On linux do X11 integration, on mac do nsobject(??).
    libvlc_media_player_set_hwnd(vlcplr, reinterpret_cast<void*>(ui->videoWidget->winId()));

    // Lets play it.
    libvlc_media_player_play(vlcplr);
    ui->playBtn->setText("Pause");
}

void StudioWindow::on_actionQuit_triggered() {
    stopPlayer();
    QCoreApplication::exit(0);
}

/**
 * Handle the state of UI with other elements of StudioWindow
 * Timers, Sliders, etc.
 * @brief StudioWindow::updateInterface
 */
void StudioWindow::updateInterface() {
    if(!vlcplr)
        return;

    // TODO Update timeline.

    if(libvlc_media_player_get_state(vlcplr) == libvlc_Ended)
        stopPlayer();
}

/**
 * Adjust volume of playback video.
 * @brief StudioWindow::on_volSlider_valueChanged
 * @param value
 */
void StudioWindow::on_volSlider_valueChanged(int value)
{

}

/**
 * Adjust playback timeline in milliseconds.
 * Min and max range 0-1000. (0-999?)
 * @brief StudioWindow::on_msSlider_valueChanged
 * @param value
 */
void StudioWindow::on_msSlider_valueChanged(int value)
{

}

/**
 * Adjust playback timeline in seconds.
 * Min and max values range from 0-60. (Should it be 0-59)
 *
 * @brief StudioWindow::on_secSlider_valueChanged
 * @param value
 */
void StudioWindow::on_secSlider_valueChanged(int value)
{

}

/**
 * Adjust playback timeline in minutes.
 * Ranges from first minute to the last minute of the video.
 *
 * TODO Add min and max values in constructor.
 * @brief StudioWindow::on_timeSlider_valueChanged
 * @param value
 */
void StudioWindow::on_timeSlider_valueChanged(int value)
{

}

/**
 * Starts the playback.
 * @brief StudioWindow::playPlayer
 */
void StudioWindow::startPlayer() {
    if(!vlcplr)
        return;

    if(libvlc_media_player_is_playing(vlcplr)) { // Is playing, do pause.
        libvlc_media_player_pause(vlcplr);
        ui->playBtn->setText("Play");
    }
    else { // Is paused, do play.
        libvlc_media_player_play(vlcplr);
        ui->playBtn->setText("Pause");
    }
}

/**
 * Stops and resets the player.
 * @brief StudioWindow::stopPlayer
 */
void StudioWindow::stopPlayer() {
    if(vlcplr) {
        // Stops the media player.
        libvlc_media_player_stop(vlcplr);

        // Release resources.
        libvlc_media_player_release(vlcplr);
        vlcplr = NULL;// NULL

        // Reset the UI values.

        // Time sliders.
        ui->timeSlider->setValue(0);
        ui->secSlider->setValue(0);
        ui->playBtn->setText("Play"); // Play button.
        ui->timeLbl->setText("Time"); // Time label.
    }
}
