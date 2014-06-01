#include "StudioWindow.h"
#include "ui_StudioWindow.h"

#include <iostream>

StudioWindow::StudioWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudioWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(onPlay()));
    QObject::connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(onStop()));
}

StudioWindow::~StudioWindow() {
    delete ui;
}

void StudioWindow::onPlay() {
    std::cout << "onPlay();" << std::endl;
}

void StudioWindow::onStop() {
    std::cout << "onStop();" << std::endl;
}
void StudioWindow::on_actionOpen_file_triggered() {
    std::cout << "Open file()" << std::endl;
}

void StudioWindow::on_actionQuit_triggered() {
    stopPlayer();
    QCoreApplication::exit(0);
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
