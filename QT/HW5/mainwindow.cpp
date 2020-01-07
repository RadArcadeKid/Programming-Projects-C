#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QThread>

#include <vector> //needed to use vectors
#include <string> //needed for strings
#include <math.h> //needed for rounding


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardcell.h"
#include "pieceicon.h"
#include "gameloop.h"
#include "selector.h"
#include "bar.h"
#include "winnerdialog.h"
//JAKE HENSON - HW5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    scene = new QGraphicsScene; //main scene
    icon_scene = new QGraphicsScene;
    graph_scene = new QGraphicsScene;


    QGraphicsView * view = ui->board_graphicsview;
    view->setScene(scene);

    //turn all the scroll bars off!!
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSceneRect(0, 0,view->frameSize().width(),view->frameSize().height());




    QGraphicsView * powerup_view = ui->pwrup_graphicsview;
    powerup_view->setScene(icon_scene);
    powerup_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    powerup_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    powerup_view->setSceneRect(0, 0,powerup_view->frameSize().width(),powerup_view->frameSize().height());


    //graph_graphicview

    QGraphicsView * graphic_view = ui->graph_graphicview;
    graphic_view->setScene(graph_scene);
    graphic_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphic_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphic_view->setSceneRect(0, 0, graphic_view->frameSize().width(), graphic_view->frameSize().height());



    //START THE GAME
    //0 - normal gamemode
    //1 - player v CPU
    //2 - CPU v CPU

    if(gamemode_ == 0){
        StartGame(); //start a normal game
    }
    else if(gamemode_ == 1){
        //start a Player V CPU game
    }
    else if(gamemode_ == 2){
        //start a CPU V CPU game
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SetGameType(int gm){
    gamemode_ = gm;
}


/**
 * @brief MainWindow::DrawBoard - Draws the board in the scene (empty)
 */
void MainWindow::DrawBoard(){
    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 6; col++){
            scene->addItem(game_.get_board_vec()[row][col]);
        }
    }
}


void MainWindow::DrawPowerups(){
    //draw netural piece
    PieceIcon * neutral_icon = new PieceIcon(4, 2, "neutral");
    icon_scene->addItem(neutral_icon);
    connect(neutral_icon, &PieceIcon::PieceSelected, this, &MainWindow::NeutralPiece_clicked);

    //draw converter piece
    PieceIcon * converter_icon = new PieceIcon(4, 59, "converter");
    icon_scene->addItem(converter_icon);
    connect(converter_icon, &PieceIcon::PieceSelected, this, &MainWindow::ConverterPiece_clicked);
}

/**
 * @brief MainWindow::RowDropScene - Drops all the rows in the scene because scene-Update wasn't working when I re-colored the cells
 */
void MainWindow::RowDropScene(){
    for(int i = 0; i < 7; i++){ //remove all the pieces on the board in the scene...
       for(int j =0; j < 6; j++){
              scene->removeItem(game_.get_board_vec()[i][j]->getPiece());
       }
    }

    game_.MovePiecesDown(); //...shift them down (in the game)

    for(int i = 0; i < 7; i++){
       for(int j =0; j < 6; j++){
              scene->addItem(game_.get_board_vec()[i][j]->getPiece()); //...and put them back in the scene!
        }
    }

    //Now, remove the top row from the scene
    for(int i = 0; i < 7; i++){
        scene->removeItem(game_.get_board_vec()[i][0]->getPiece());
    }
    game_.DropRow(); //and then remove the top row permanently from the game!!

    //You might be thinking - this seems like an awful lot of work for this when you could just scene->update, after changing the pieces, right?
    //I kept having wierd issues where the pieces were inconsistantly changing during scene->update and wouldn't properly overwrite each other
    //so the bruteforce way was my only option that consistantly worked...

    scene->update();
}



void MainWindow::on_drop_button_clicked()
{
    if(game_.CanMoveHere() == true){ //if this move is a valid one...

        //check for netural + other pieces here!!

        //if we're dropping a powerup...
        if(select_obj_->getPieceColor() == "neutral"){
            scene->addItem(game_.AddPiece("neutral")); //add the neutral piece to the scene
            scene->update();

            //reset the selector back to how it was before the player dropped this piece
            if(game_.get_player() == 1){
                select_obj_->setPieceColor("blue"); //set back to pink!
            }
            else if(game_.get_player() == 2){
                select_obj_->setPieceColor("pink"); //set back to blue!
            }

            game_.decrementPowerUpQty("neutral"); //decrement the number of power ups that the player has
            game_.ToggleTurn(); //toggle which player goes next (since a neutral piece doesn't as a turn

        }
        else if(select_obj_->getPieceColor() == "converter"){
            if(game_.GetCurrentRow() < 5){
                qDebug() << "removing piece at [" << game_.get_current_column() << "][" << game_.GetCurrentRow()+1 << "] ";
                scene->removeItem(game_.get_board_vec()[game_.get_current_column()][game_.GetCurrentRow()+1]->getPiece()); //...and put them back in the scene!
                scene->addItem(game_.AddPowerup("converter")); //add the converter piece to the scene
                qDebug() << "converting piece at [" << game_.get_current_column() << "][" << game_.GetCurrentRow()+2 << "] ";
                scene->addItem(game_.get_board_vec()[game_.get_current_column()][game_.GetCurrentRow()+2]->getPiece()); //...and put them back in the scene!
            }

            scene->update();

            //reset the selector back to how it was before the player dropped this piece
            if(game_.get_player() == 1){
                select_obj_->setPieceColor("blue"); //set back to pink!
            }
            else if(game_.get_player() == 2){
                select_obj_->setPieceColor("pink"); //set back to blue!
            }

            game_.decrementPowerUpQty("converter"); //decrement the number of power ups that the player has
            game_.ToggleTurn(); //toggle which player goes next (since a neutral piece doesn't as a turn
        }
        else{ //othewise, players are dropping normal pieces

            if(game_.get_player() == 1){
                scene->addItem(game_.AddPiece("blue"));
                select_obj_->setPieceColor("pink"); //set back to pink!
             }
             else if(game_.get_player() == 2){
                scene->addItem(game_.AddPiece("pink"));
                select_obj_->setPieceColor("blue"); //set back to blue!
             }
        }

            int winner = game_.CheckIfWinner();
            if(winner != 0){
                UpdateGraph();
                update();
                scene->update();
                graph_scene->update();
                qDebug() << "Game has been won by player " << winner << "!";
                SpawnWinnerPopup(winner);
            }


            game_.ToggleTurn(); //toggle which player goes next

            UpdateLabels(); //update the labels after the fact!

            ////ROW DROP
            if(game_.IsBoardFull() == true){ //if our board has totally filled up, time to drop the row
                RowDropScene();
            }
    }
    update();
    scene->update();
}

void MainWindow::on_left_button_clicked()
{
    game_.MoveLeft();
    select_obj_->MoveSelector(game_.get_current_column());
    scene->update();
}

void MainWindow::on_right_button_clicked()
{
    game_.MoveRight();
    select_obj_->MoveSelector(game_.get_current_column());
    scene->update();
}


void MainWindow::NeutralPiece_clicked(){
    if(game_.GetPowerUpQty("neutral") > 0){
        select_obj_->setPieceColor("neutral"); //set this selector to neutral!
        scene->update();
    }
}

void MainWindow::ConverterPiece_clicked(){
    if(game_.GetPowerUpQty("converter") > 0){
        select_obj_->setPieceColor("converter"); //set this selector to a converter piece!
        scene->update();
    }
}


void MainWindow::UpdateLabels(){

    //update current player label
    int current_player = game_.get_player();
    std::string player_string = "Player " + std::to_string(current_player) + "'s turn!";
    QString trnlsbl(player_string.c_str());
    ui->turn_label->setText(trnlsbl);

    //update powerup string label
    std::string player_string_pwrup = "Player " + std::to_string(current_player) + "'s Powerups:";
    QString powerup_string(player_string_pwrup.c_str());
    ui->powerups_ForPlayerLabel->setText(powerup_string);


    //update neutral piece qty label
    int n_qty = game_.GetPowerUpQty("neutral");
    std::string n_qty_string_label = "x" + std::to_string(n_qty);
    QString n_qty_label(n_qty_string_label.c_str());
    ui->nullpiece_qty_label->setText(n_qty_label);

    //update converter piece qty label
    int p_qty = game_.GetPowerUpQty("converter");
    std::string p_qty_string_label = "x" + std::to_string(p_qty);
    QString p_qty_label(p_qty_string_label.c_str());
    ui->cnvrt_below_qty_label->setText(p_qty_label);


    //update winner labels:
    int p1_win_qty_int = game_.get_num_games_won(1);
    std::string p1_win_label = std::to_string(p1_win_qty_int);
    QString p1_final_label(p1_win_label.c_str());
    ui->p1_num_wins_label->setText(p1_final_label);

    int p2_win_qty_int = game_.get_num_games_won(2);
    std::string p2_win_label = std::to_string(p2_win_qty_int);
    QString p2_final_label(p2_win_label.c_str());
    ui->p2_num_wins_label->setText(p2_final_label);
}


void MainWindow::UpdateGraph(){
    //update the bar with the current number of wins
    int p1_wins = game_.get_num_games_won(1);
    int p2_wins = game_.get_num_games_won(2);


    //update both bar graph objects
    p1_bar->setHeight(p1_wins);
    p2_bar->setHeight(p2_wins);

    graph_scene->removeItem(p1_bar); //reset bars
    graph_scene->addItem(p1_bar);

    graph_scene->removeItem(p2_bar);
    graph_scene->addItem(p2_bar);

    graph_scene->update();
}

void MainWindow::StartGame(){
    DrawBoard();

    DrawPowerups();


    select_obj_ = new Selector(3);
    scene->addItem(select_obj_);

    UpdateLabels(); //update all the labels!

    //create new graph
    p1_bar = new Bar(9, 1);
    p2_bar = new Bar(75, 2);

    graph_scene->addItem(p1_bar);
    graph_scene->addItem(p2_bar);

    select_obj_->setPieceColor("blue"); //REMOVE ME LATER
}

void MainWindow::SpawnWinnerPopup(int winner){
    WinnerDialog win_box;

    connect(&win_box, &WinnerDialog::ReadyToResetSig, this, &MainWindow::ReadyToReset);


    //set up dialogue here
    win_box.SetWinner(winner, game_.get_num_games_won(1), game_.get_num_games_won(2));

    win_box.setModal(true);
    win_box.exec();
}

void MainWindow::ReadyToReset(){

    //gotta remove all of the leftover crap from the previous game (because APPARENTLY scene->update doesn't do its job)
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 6; j++){
            scene->removeItem(game_.get_board_vec()[i][j]->getPiece());
            scene->removeItem(game_.get_board_vec()[i][j]->getPowerup());
        }
    }

//    //reset the game here after we've won
      game_.ResetGame();
      scene->update();

//    //update labels for da winner
      UpdateLabels();

//    //Start the game:
//   // StartGame(); -- now controlled by external dialogue window
      qDebug() << "Game has been reset.";
}



