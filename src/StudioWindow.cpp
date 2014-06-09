#include "StudioWindow.h"
#include "ui_StudioWindow.h"

#include <QFileDialog>

#include <iostream>

StudioWindow::StudioWindow(QWidget *parent) :
    QMainWindow(parent), vlcplr(NULL), timer(new QTimer(this)), paused(false),
    ui(new Ui::StudioWindow)
{
    vlc = libvlc_new(0, NULL);

    if(vlc == NULL) {
        QMessageBox::critical(this, "SubtitleStudio", "Vlc instance not initialized.");
        QApplication::exit(1); // Return 1 as error code.
    }

    ui->setupUi(this);

    ui->volSlider->setSliderPosition(80);

    // Draw black screen to videoWidget.
    ui->videoWidget->setAutoFillBackground(true);
    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    ui->videoWidget->setPalette(plt);

    // Start the interface update timer.
    timer->start(100);

    QObject::connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(onPlay()));
    QObject::connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterface()));
}

StudioWindow::~StudioWindow() {
    // Release plr if not already stopped.
    if(vlcplr) {
        libvlc_media_player_stop(vlcplr);
        libvlc_media_player_release(vlcplr);
    }
    if(vlc)
        libvlc_release(vlc);

    // Release the allocated memory.
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
 *
 * TODO Even if media is not selected and this event is triggered,
 * play button's text get changed from play to pause. (BUG)
 * TODO Make better solution for upper problem. Current solution
 * is more like a hack..
 *
 * @brief StudioWindow::on_actionOpen_file_triggered
 */
void StudioWindow::on_actionOpen_file_triggered() {
    QString file = QFileDialog::getOpenFileName(this, tr("Open a file"));

    if(vlcplr && libvlc_media_player_is_playing(vlcplr))
        stopPlayer();

    // Create new media and give it file's path as utf8 const char*.
    QString furi = makeURI(file);
    libvlc_media_t *media = libvlc_media_new_location(vlc, furi.toUtf8().constData());

    if(!media) // Return on error.
        return;

    vlcplr = libvlc_media_player_new_from_media(media);

    libvlc_media_release(media);

    // FOLLOWING WORKS ONLY ON WINDOWS.
    // On linux do X11 integration, on mac do nsobject(??) or whatever is the winmgr.
    libvlc_media_player_set_hwnd(vlcplr, reinterpret_cast<void*>(ui->videoWidget->winId()));

    // Lets play it.
    libvlc_media_player_play(vlcplr);

    if(file.size() != 0) {
        ui->playBtn->setText("Pause");
        return;
    }
    stopPlayer();
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

    // Update Time label.
    long time = libvlc_media_player_get_time(vlcplr);
    updateTimeLabel(time);

    float pos = libvlc_media_player_get_position(vlcplr);
    ui->timeSlider->setSliderPosition((int)(pos * 1000));


    // Sum debug information.
    //std::cout << "Length: " << libvlc_media_player_get_length(vlcplr) << std::endl;
    //std::cout << "Current: " << libvlc_media_player_get_time(vlcplr) << std::endl;

    if(libvlc_media_player_get_state(vlcplr) == libvlc_Ended)
        libvlc_media_player_stop(vlcplr); //stopPlayer();
}

/**
 * Adjust playback timeline in minutes.
 * Ranges from first minute to the last minute of the video.
 *
 * TODO Add min and max values in constructor.
 * @brief StudioWindow::on_timeSlider_valueChanged
 * @param value
 */
void StudioWindow::on_timeSlider_valueChanged(int value) {
    std::cout << "timeSlider_valueChanged: " << value << std::endl;
    if(vlcplr)
        libvlc_media_player_set_position(vlcplr, (float)value / 1000);
}

/**
 * Adjust playback timeline in seconds.
 * Min and max values range from 0-60.
 * Can only be adjusted while media is on pause.
 *
 * @brief StudioWindow::on_secSlider_valueChanged
 * @param value
 */
void StudioWindow::on_secSlider_valueChanged(int value) {
    if(vlcplr && paused) {
        ui->sinfoLbl->setText(QString("Sec. ") + QString::number(value));

        uint64_t t = currtime + (value * 1000);

        std::cout << "currtime: " << currtime << std::endl;
        std::cout << "secSlider t: " << t << std::endl;

        libvlc_media_player_set_time(vlcplr, t);
    }
}

/**
 * Adjust playback timeline in milliseconds.
 * Min and max range 0-1000.
 * Can only be adjusted while media is on pause.
 *
 * @brief StudioWindow::on_msSlider_valueChanged
 * @param value
 */
void StudioWindow::on_msSlider_valueChanged(int value) {
    if(vlcplr && paused) {
        ui->msinfoLbl->setText(QString("Ms. ") + QString::number(value));

        uint64_t t = currtime + value;

        std::cout << "currtime: " << currtime << std::endl;
        std::cout << "msSlider t: " << t << std::endl;

        libvlc_media_player_set_time(vlcplr, t);
    }
}

/**
 * Adjust volume of playback video.
 * @brief StudioWindow::on_volSlider_sliderMoved
 * @param value
 */
void StudioWindow::on_volSlider_sliderMoved(int position) {
    if(vlcplr)
        if(libvlc_audio_set_volume(vlcplr, position) == 0)
            updateVolLabel(position);
}

void StudioWindow::updateVolLabel(int vol) {
    QString volume(QString::number(vol));
    ui->volLbl->setText("Volume: " + volume);
}

/**
 * Method to update Timeline label on Form.
 * Hmm.. So basically one day is the limit here.
 *
 * @brief StudioWindow::updateTimeLabel
 * @param s Seconds.
 * @param m Minutes.
 * @param h Hours.
 */
void StudioWindow::updateTimeLabel(long ms) {
    long s = ms / 1000;
    long m = s / 60;
    long h = m / 60;

    QString s_str(QString::number(s % 60));
    QString m_str(QString::number(m % 60));
    QString h_str(QString::number(h % 24));

    QString time("Time ");
    time.append(h_str + ":");
    time.append(m_str + ":");
    time.append(s_str);

    ui->timeLbl->setText(time);
}

/**
 * Plays the media.
 * @brief StudioWindow::playPlayer
 */
void StudioWindow::startPlayer() {
    if(!vlcplr)
        return;

    // Playback. Much clearer way.. Though i dont like it. Maybe elseif??
    if(ui->playbCBox->isChecked()) {
        playback = true;
        return;
    } else
        playback = false;

    if(libvlc_media_player_is_playing(vlcplr)) { // Is playing, do pause.
        libvlc_media_player_pause(vlcplr);
        ui->playBtn->setText("Play");

        paused = true;
        currtime = libvlc_media_player_get_time(vlcplr);

        std::cout << "currtime: " << currtime << std::endl;
    }
    else { // Is paused, do play.
        libvlc_media_player_play(vlcplr);
        ui->playBtn->setText("Pause");
        paused = false;
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
        ui->msSlider->setValue(0);
        ui->playBtn->setText("Play"); // Play button.
        ui->timeLbl->setText("Time"); // Time label.
    }
}
