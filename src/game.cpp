#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::whoWon(Player* player, Croupier* croupier, Ui::MainWindow *ui)
{
    if (player->countPoints() < croupier->countPoints()){
        ui->label_result->setText(QString("The Croupier won"));
        gameOver(player->getCurrentlyMoney());
        ui->label_currently_money->setText((QString("You have ")+ QString::number(player->getCurrentlyMoney())) + QString(" $"));

        //Lost sound
        QMediaPlayer* player = new QMediaPlayer;
        QAudioOutput* audioOutput = new QAudioOutput;
         player->setAudioOutput(audioOutput);
         player->setSource(QUrl("qrc:/sound/Lost.mp3"));
         audioOutput->setVolume(50);
         player->play();

    }
    else if (player->countPoints() > croupier->countPoints()){
        ui->label_result->setText(QString("You won"));
        player->setCurrentlyMoney(player->getCurrentlyMoney() + 2 * player->getMoneyOnBet());
        ui->label_currently_money->setText((QString("You have ")+ QString::number(player->getCurrentlyMoney())) + QString(" $"));

        //Won sound
        QMediaPlayer* player = new QMediaPlayer;
        QAudioOutput* audioOutput = new QAudioOutput;
         player->setAudioOutput(audioOutput);
         player->setSource(QUrl("qrc:/sound/Won.mp3"));
         audioOutput->setVolume(50);
         player->play();
    }
    else{
        ui->label_result->setText(QString("DRAW"));
        player->setCurrentlyMoney(player->getCurrentlyMoney() + player->getMoneyOnBet());
        ui->label_currently_money->setText((QString("You have ")+ QString::number(player->getCurrentlyMoney())) + QString(" $"));

        //Draw sound
        QMediaPlayer* player = new QMediaPlayer;
        QAudioOutput* audioOutput = new QAudioOutput;
         player->setAudioOutput(audioOutput);
         player->setSource(QUrl("qrc:/sound/Draw.mp3"));
         audioOutput->setVolume(50);
         player->play();
    }
}

bool Game::burn(Croupier* croupier, Player* player, Ui::MainWindow *ui) {
    if (croupier->countPoints() > 21) {
        ui->label_result->setText(QString("You won, The croupier\n has too many points"));
        ui->label_points_croupier->setText(QString::number(croupier->countPoints()) + QString(" Points"));
        player->setCurrentlyMoney(player->getCurrentlyMoney() + 2 * player->getMoneyOnBet());
        ui->label_currently_money->setText((QString("You have ")+ QString::number(player->getCurrentlyMoney())) + QString(" $"));

        //Won sound
        QMediaPlayer* player = new QMediaPlayer;
        QAudioOutput* audioOutput = new QAudioOutput;
         player->setAudioOutput(audioOutput);
         player->setSource(QUrl("qrc:/sound/Won.mp3"));
         audioOutput->setVolume(50);
         player->play();

        return true;
    }
    else
        return false;
}

bool Game::burn(Player* player,Ui::MainWindow *ui) {
    if (player->countPoints() > 21) {
        ui->label_points_player->setText(QString::number(player->countPoints()) + QString(" Points"));
        ui->label_result->setText(QString("You lost\nyou have too many points"));
        gameOver(player->getCurrentlyMoney());
        ui->label_currently_money->setText((QString("You have ")+ QString::number(player->getCurrentlyMoney())) + QString(" $"));
        //Lost sound
        QMediaPlayer* player = new QMediaPlayer;
        QAudioOutput* audioOutput = new QAudioOutput;
         player->setAudioOutput(audioOutput);
         player->setSource(QUrl("qrc:/sound/Lost.mp3"));
         audioOutput->setVolume(50);
         player->play();
        return true;
    }
    else {
        ui->label_points_player->setText(QString::number(player->countPoints()) + QString(" Points"));
        return false;
    }
}

void Game::endResult(Player* player, Croupier* croupier, int hits, int adds, Ui::MainWindow *ui) {
    player->showHandDeck(2 + hits, ui);
    ui->label_points_player->setText(QString::number(player->countPoints()) + QString(" Points"));
    croupier->showHandDeck(2 + adds, ui);
    ui->label_points_croupier->setText(QString::number(croupier->countPoints()) + QString(" Points"));
    whoWon(player, croupier, ui);
}

