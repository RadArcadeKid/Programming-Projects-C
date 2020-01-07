#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <vector> //needed to use vectors
#include <string> //needed for strings
#include <math.h> //needed for rounding

#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "cell.h"
#include "bar.h"
//JAKE HENSON - HW4
//PlotWindow.cpp
//Acts as a grid + main window + graph organizer
//Run using main.cpp + the UI


/**
 * Constructor for the whole window
 * @param - none
 * @return - none
 */
PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    // we need to set up the ui before we draw on our scene
    ui->setupUi(this);

    // scene is a pointer field of plot window
    scene = new QGraphicsScene;


    // QGraphicsView is a container for a QGraphicsScene
    QGraphicsView * view = ui->plotGraphicsView;
    view->setScene(scene);

    view->setSceneRect(-10,-10,view->frameSize().width(),view->frameSize().height()); //should be slightly down and to the right to center the board

    //need to make sure those dumb scroll bars go away!
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //turn scroll bars off!
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //turn scroll bars off!

    //a random time value, useful for determining whether a cell should start dead or alive
    srand(time(0));

    //initialize the grid once the window gets created
    InitializeGrid();

    //initilaize the graph once the window gets created
    InitializeGraph();

    //set all the default private variables up!
    color_index_ = 0; //starts at Pink
    turn_ = 0;
    bar_placement_val_= 0;
    slider_tracker_ = 1; //starts at slowest time

    //create a basic timer object to use with slider/buttons
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(timer_slot()));
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

/**
 * on_stepButton_clicked - Moves the game forward by 1 turn when "Step" is clicked
 * @param - none
 * @return - none
 */
void PlotWindow::on_stepButton_clicked()
{
    StepAllForward(); //just step forward once, once the button is clicked
    scene->update(); //don't forget to update the scene!!
}

/**
 * CellClickedSlot - Originally out here to change the cells
 * but it's a little easier to do this in the cell object. This isn't used for much...
 * @param - none
 * @return - none
 */
void PlotWindow::CellClickedSlot(Cell * c){
    //qDebug() << "clicked cell";
    //qDebug() << "x: " << c->get_x() << "y: " << c->get_y();
}


/**
 * Initializes the Grid, creates Cell objects to be populated, displays them
 * @param - none
 * @return - none
 */
void PlotWindow::InitializeGrid(){

    for(int row = 0; row <= 20; row++){
        for(int col = 0; col <= 10; col++){
            Cell * colcell = new Cell((row * 25), (col * 25));
            connect(colcell, &Cell::CellSelected, this, &PlotWindow::CellClickedSlot); //connect every cell to the CellClickedSlot
            col_vec_.push_back(colcell);
            scene->addItem(colcell); //Add each cell
        }
        grid_vec_.push_back(col_vec_); //populate grid vec with vector of columns!
        col_vec_ = {}; //reset col_vec back to 0, to be populated again!
    }

}


/**
 * Checks whether the cell passed in is valid using CheckNeigbors function
 * Accounts for the logic of the rules based on the edges/corners of the grid
 * @param - Cell - pointer to a cell object to be passed in
 * @return - returns true or false depending on if this cell should be alive or dead next turn
 */
void PlotWindow::CheckCell(Cell * cell){
   //CheckNeighbors will have 9 parameters,
    //each accounting for a direction - need to make the logic
    //here support that: CheckNeighbors(original, upleft, up, upright, right, downright, down, downleft, left)

    //get the current cell's coordinates
    int x = cell->get_x();
    int y = cell->get_y();

    //used for determining the neighbors' values
    int x_minus_1 = x-1;
    int y_minus_1 = y-1;
    int x_plus_1 = x+1;
    int y_plus_1 = y+1;

    //to account for the fact that the grid is only so large,
    //and that edges will roll-over on neighbors, I need to make sure none of the
    //boundaries are outside of the bounds of the grid, and correct them if they are
    if(x_minus_1 < 0) x_minus_1 = 20;
    if(y_minus_1 < 0) y_minus_1 = 10;
    if(x_plus_1 > 20) x_plus_1 = 0;
    if(y_plus_1 > 10) y_plus_1 = 0;
    //originally, I had this as some crazy series of nested if-statements to account for
    //edges + corners, only to realize just changing the boundaries was *way* easier!

    //set the neighbors based on our newly calculated values
    Cell * upleft = grid_vec_[x_minus_1][y_minus_1];
    Cell * up = grid_vec_[x][y_minus_1];
    Cell * upright = grid_vec_[x_plus_1][y_minus_1];
    Cell * right = grid_vec_[x_plus_1][y];
    Cell * downright = grid_vec_[x_plus_1][y_plus_1];
    Cell * down = grid_vec_[x][y_plus_1];
    Cell * downleft = grid_vec_[x_minus_1][y_plus_1];
    Cell * left = grid_vec_[x_minus_1][y];
    //could I store this in a vector/array/fields? sure...
    //but, I used it this way in testing and it's more tedious to change it for now...
    //would update if I had more time


    //Now, finally, check the neighbors after defining where they are on the grid
    CheckNeighbors(cell, upleft, up, upright, right, downright, down, downleft, left);
}

/**
 * Checks the neighbors of this cell based on the 8 neighbors passed in
 * Uses the logic rules in the write-up to determine the next status of the cell
 * @param - original (target cell), upleft (up-left neighbor), up (top neighbor), upright (up-right neighbor)
 *        - right (right neighbor), downright (down-right neighbor), down (bottom neighbor), downleft(down-left neighbor)
 *        - left (left neighbor)
 * @return - none, BUT it will set the target Cell's next status to alive/dead
 */
void PlotWindow::CheckNeighbors(Cell * original, Cell * upleft, Cell * up, Cell * upright, Cell * right, Cell * downright, Cell * down, Cell * downleft, Cell * left){
    int num_neighbors_alive = 0;

    //check the status of all neighbors
    if(upleft->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(up->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(upright->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(right->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(downright->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(down->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(downleft->get_Cell_Current_Status() == true) num_neighbors_alive++;
    if(left->get_Cell_Current_Status() == true) num_neighbors_alive++;
    //(yeah, i know this is a SUPER ugly and inefficient way of doing this, but
    //I needed to make sure all of the values were actually changing
    //and kept having weird issues when using vectors


    if(original->get_Cell_Current_Status() == true){ //if target cell is alive....
        if(num_neighbors_alive < 2){ //1. Any live cell with fewer than two neighbors dies (underpopulation)
            //cell dies (set next status to dead)
            original->SetNextCellStatus(false);
        }
        if(num_neighbors_alive == 2 || num_neighbors_alive == 3){ //2. Any live cell with two or three live neighbors remains alive (stable)
            //cell stays alive (set next status to alive)
            original->SetNextCellStatus(true);
        }
        if(num_neighbors_alive > 3){ //3. Any live cell with more than three live neighbors dies (overpopulation)
            //cell dies (set next status to dead)
            original->SetNextCellStatus(false);
        }
    }
    else{ //if target cell is dead...
        if(num_neighbors_alive == 3){ //4. Any dead cell with exactly three live neighbors becomes a live cell (reproduction)
            //cell comes alive (set next status to alive)
            original->SetNextCellStatus(true);
        }
        else{
            //cell stays dead
            original->SetNextCellStatus(false); //might be redundant, but just in case...
        }
    }

}

/**
 * The main turn-taking function.
 * When called, it will:
 *  -  Update the cell's color for the turn
 *  -  STEP all the cells in the grid forward, effectively taking a turn for all cells
 *  -  Add a bar for the graph using AddBar();
 *  -  call for display the labels of the various UI objects
 * @param - none
 * @return - none
 */
void PlotWindow::StepAllForward(){    
    DisplayLabels(); //display the labels each time so the turn updates

    if(color_index_ >= 10){ //ensure color index isn't getting set past the size of the vector
        color_index_ = 0;
    }

    if(bar_placement_val_ > 500){ //ensure bars won't be drawn outside the boundaries of the graph
        bar_placement_val_ = 500;
    }

    AddBar(); //add the bar for this step

    for(int row = 0; row <= 20; row++){
        for(int col = 0; col <= 10; col++){
            CheckCell(grid_vec_[row][col]); //check the cell, determine what the step is
            grid_vec_[row][col]->step_cell(); //switch the cell
            grid_vec_[row][col]->SetColor(colors_vec_[color_index_]); //update Color with Qcolors vector
        }
    }
    color_index_++; //increment, changing the color for each turn
    turn_++;
}

/**
 * Displays and updates the turn and Population values in the UI!
 * @param - none
 * @return - none
 */
void PlotWindow::DisplayLabels(){

    //Display turn
    std::string turn_string = "Turn: " + std::to_string(turn_ + 1); //+1 to fix starting at 0 so it doesn't say that twice
    QString qs(turn_string.c_str());
    ui->turnLabel->setText(qs);

    //Display Population
    int num_cells_alive = GetNumCellsAlive();
    int percentage_val = GetPopulationPercentage();

    std::string pop_string = "Population: " + std::to_string(num_cells_alive) + "  (" + std::to_string(percentage_val) + "%) "; //+1 to fix starting at 0 so it doesn't say that twice
    QString ps(pop_string.c_str());
    ui->popLabel->setText(ps);

    update();
}

/**
 * Checks to see how many cells are alive when called
 * @param - none
 * @return - returns an integer of the number of cells alive on the board at any given time
 */
int PlotWindow::GetNumCellsAlive(){
    int num_cells_alive = 0;

    for(int row = 0; row <= 20; row++){
        for(int col = 0; col <= 10; col++){
            if(grid_vec_[row][col]->get_Cell_Current_Status() == true){ //if we've found an alive cell...
                num_cells_alive++;
            }
        }
    }

    return num_cells_alive;
}

/**
 * Gets a rounded-version of the population value, rounded to an integer value
 * Usefull for the UI and Bar height for the graph
 * @param - none
 * @return - returns an integer of the percentage of cells on the board that are alive
 */
int PlotWindow::GetPopulationPercentage(){
    int num_cells_alive = GetNumCellsAlive(); //retrieve how many cells are alive right now
    double num_cells_percentage = (num_cells_alive / 231.0) * 100.0;
    int rounded_num_cells_percentage = int(round(num_cells_percentage)); //round and convert to a single integer value

    return rounded_num_cells_percentage;
}

/**
 * Draws the graph object outline in the window
 * @param - none
 * @return - none
 */
void PlotWindow::InitializeGraph(){
    Graph * big_graph = new Graph();
    scene->addItem(big_graph); //Add da graph
}

/**
 * Adds a bar to the graph!
 * Uses the ReDraw bars function to make sure new bars are generated correctlyl
 * @param - none
 * @return - none
 */
void PlotWindow::AddBar(){
    //qDebug() << "Adding bar at: "<< bar_placement_val_;

    //create a new bar to add
    Bar * bar = new Bar(bar_placement_val_, GetPopulationPercentage(), colors_vec_[color_index_]);
    bars_vec_.push_back(bar); //add this bar to the bars vector
    scene->addItem(bar); //add this bar to the scene

    bar_placement_val_ += 25; //update where this bar will be placed in the future
    //qDebug() << "vectorSize (from addbar) = " << bars_vec_.size();

    if(bars_vec_.size() == 22){ //once the bars vector is 22 items big (big enough to re-draw)
        RedrawBars(); //redraw all the bars
        scene->update(); //update
    }
}

/**
 * Shifts and re-draws all the graph objects using the bars_vec_
 * @param - none
 * @return - none
 */
void PlotWindow::RedrawBars(){

    delete bars_vec_[0]; //delete the first bar
    scene->removeItem(bars_vec_[0]); //remove the first bar from the scene
    bars_vec_.erase (bars_vec_.begin()); //remove the first element (bar) from the vector
    //note - there's a weird memory/segfault issue here, where if I make the delete call after, the program dies...
    //so I made it before, but sometimes it can cause the bars to draw weirdly...

    //move all the bars back using their moveback function!
    for(unsigned int i = 0; i < bars_vec_.size()-1; i++){
        bars_vec_[i]->moveback();
    }
    //bar_placement_val_ -= 25;
}







void PlotWindow::on_playButton_clicked()
{
    timer->start(1000 * slider_tracker_);
}

void PlotWindow::timer_slot(){
    StepAllForward();
}

void PlotWindow::on_pauseButton_clicked()
{
    timer->stop(); //pauses
}

void PlotWindow::on_horizontalSlider_valueChanged(int value)
{
    slider_tracker_ = 1 - (value * 0.01); //convert value to the slider_tracker_ easier to see and use with timer
    std::string slider_string = "Speed: " + std::to_string(slider_tracker_);
    QString sls(slider_string.c_str());
    ui->sliderlabel->setText(sls); //update string

    timer->start(1000 * slider_tracker_); //change timer
}
