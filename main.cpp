//
//  main.cpp
//  sonhal
//
//  Created by Selin İmren on 10.11.2023.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include "Stack.h"
#include "Stack.cpp"
using namespace std;
// This struct contains the information of the cell which constructs the maze, we will also use this struct in stacks and 2D matrices.
struct Cell{
    int x ,y; // the indices of cell in the matrix
    bool l=1,r=1,u=1,d=1; // they represents the walls around the cell: 0= no wall 1= wall;
    bool visited= false; // when the cell is visited, boolean expression will be true;store the data for backtracking.
    bool discovered=false; // when the cell is discovered while path finding, booelan expression will be true.
    // it is a initilazer for the cell while initilazing.
    Cell(int x_coord = 0, int y_coord = 0, bool left = true, bool right = true, bool up = true, bool down = true, bool isVisited = false,bool isDiscovered= false)
        : x(x_coord), y(y_coord), l(left), r(right), u(up), d(down), visited(isVisited), discovered(isDiscovered) {}
};
// This function construct a txt file which contains the maze generation data.
void mazePrint(ostream & mazeGenerataed_out,vector<vector<Cell>> maze, int rows, int cols){
    mazeGenerataed_out<< cols << ' '<< rows << endl;
    for(int i =0 ; i<rows ; i++){
        for(int j=0; j< cols; j++){
            mazeGenerataed_out<<"x="<< maze[i][j].x << " y="<< maze[i][j].y << " l="<<  maze[i][j].l <<" r="<< maze[i][j].r <<" u=" <<maze[i][j].u <<" d=" << maze[i][j].d << endl;
        }
    }
}
// This function construct a txt file which contains the path which is starting entryX and entryY coordinates and finishing with exitX and exitY coordinates.
void filePath(ostream & path_out, Stack<Cell> &path_discovered){
    while(!path_discovered.isEmpty()){
        Cell currentCell=path_discovered.top();
        path_out<< currentCell.y << ' '<< currentCell.x<< endl;
        path_discovered.pop();
        
    }
}

// This function randomly generates mazes with given rules.
vector<vector<Cell>> generate_maze(int rows, int cols){
    // It is two-dimensional vector which is composed with Cell; the maze data will hold in this 2D vector.
    vector<vector<Cell>> maze(rows,vector<Cell>(cols));
    // To generate a number randomly.
    random_device rd;
    mt19937 gen(rd());
    // It is a stack which is composed with Cell; this stack will use in maze-generating process, when the backtracking is needed, stack will be also usen.
    Stack<Cell> pathMaze;
    // Initializing the matrix with Cell.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maze[i][j] = Cell(i, j, true, true, true, true, false,false);
        }
    }
    // maze generation will start with a cell whichs coordinates are (0,0); that's why its visited boolean become true.
    maze[0][0].visited=true;
    // Initial point is created and the values is set.
    Cell initialPoint(0, 0, true, true, true, true,true,false);
    // pathMaze's first element is initial point, since maze generation will start with initial point.
    pathMaze.push(initialPoint);
    Cell currentCell= pathMaze.top();
    // num_wall_break represents the number of the walls which is destructed.
    int num_wall_break=0;
    // choices vector stores the possible directions that the maze generation can process according the rules.
    vector<int> choices;
    // This while loop will continue until reaching the maximum number of the wall which can be destructed while maze generation processing.
    while(num_wall_break < (rows*cols)-1){
        // choices vector is cleared at the beginning because every single cell have different possible directions and walls to destruct.
        choices.clear();
        // It controls whether the right wall of the Cell is suitable to knockdown.There are three rules to check: is there a right wall of the cell, secondly while destructing the right wall it checks whether the boundaries are exceeded or not, lastly it checks if the right-neighbour cell  is visited.If the rules are ensured 0 will push the choices.0 represents the right direction.
        if(currentCell.r && (currentCell.x+1) <= rows-1 ){
            if(!maze[currentCell.x+1][currentCell.y].visited){
                choices.push_back(0);}
        }
        // It controls whether the left wall of the Cell is suitable to knockdown.There are three rules to check: is there a left wall of the cell, secondly while destructing the left wall it checks whether the boundaries are exceeded or not, lastly it checks if the left-neighbour cell  is visited.If the rules are ensured 1 will push into the choices.1 represents the left direction.
        if(currentCell.l && (currentCell.x-1 ) >=0){
            if(!maze[currentCell.x-1][currentCell.y].visited){
                choices.push_back(1);}
        }
        // It controls whether the down wall of the Cell is suitable to knockdown.There are three rules to check: is there a down wall of the cell, secondly while destructing the down wall it checks whether the boundaries are exceeded or not, lastly it checks if the down-neighbour cell is visited.If the rules are ensured 2 will push into the choices.2 represents the down direction.
        if(currentCell.d && (currentCell.y-1) >= 0){
            if(!maze[currentCell.x][currentCell.y-1].visited){
                choices.push_back(2);}
        }
        // It controls whether the up wall of the Cell is suitable to knockdown.There are three rules to check: is there a up wall of the cell, secondly while destructing the up wall it checks whether the boundaries are exceeded or not, lastly it checks if the up-neighbour cell is visited.If the rules are ensured 3 will push into the choices.3 represents the up direction.
        if(currentCell.u &&(currentCell.y+1) <= cols-1 ){
            if(!maze[currentCell.x][currentCell.y+1].visited){
                choices.push_back(3);}
        }
        // To start the random generation, choices cannot be empty. Since if it is empty it means there are no possible wall to deconstruct.
        if(!choices.empty()){
            // it generates a random number in the range 0 and the size of the choices minus 1.
            uniform_int_distribution<int> dis(0, choices.size()-1);
            //  random index will be usen for chosing from the choices vector.
            int random_index = dis(gen);
            // by using random_index, a possible direction will be chosen randomly its name is wallToKnockdown.
            int wallToKnockdown=choices[random_index];
            // The chosen direction is right. Firstly the booelan expression which represent the right wall of the cell become false, since it is destructed. It becomes false also in the maze matrix. Secondly, the right-neighbour cell become visited.The right-neighbour cell's left wall is destructed, so the booelan expression which represent the left wall of the cell become false. The right-neighbour cell is pushed into the pathMaze. And the num_wall_break is incremented, because we destruct a wall. Then, the currentCell is updated as the top of the pathMaze.
            if(wallToKnockdown==0){
                currentCell.r=false;
                maze[currentCell.x][currentCell.y].r=false;
                maze[currentCell.x+1][currentCell.y].visited=true;
                maze[currentCell.x+1][currentCell.y].l=false;
                pathMaze.push(maze[currentCell.x+1][currentCell.y]);
                num_wall_break++;
                currentCell=pathMaze.top();
                
            }
            // The chosen direction is left. Firstly the booelan expression which represent the left wall of the cell become false, since it is destructed. It becomes false also in the maze matrix. Secondly, the left-neighbour cell become visited.The left-neighbour cell's right wall is destructed, so the booelan expression which represent the right wall of the cell become false. The left-neighbour cell is pushed into the pathMaze. And the num_wall_break is incremented, because we destruct a wall. Then, the currentCell is updated as the top of the pathMaze.
            else if(wallToKnockdown==1){
                currentCell.l=false;
                maze[currentCell.x][currentCell.y].l=false;
                maze[currentCell.x-1][currentCell.y].visited=true;
                maze[currentCell.x-1][currentCell.y].r=false;
                pathMaze.push(maze[currentCell.x-1][currentCell.y]);
                num_wall_break++;
                currentCell=pathMaze.top();
                
            }
            // The chosen direction is down. Firstly the booelan expression which represent the down wall of the cell become false, since it is destructed. It becomes false also in the maze matrix. Secondly, the down-neighbour cell become visited.The down-neighbour cell's up wall is destructed, so the booelan expression which represent the up wall of the cell become false. The down-neighbour cell is pushed into the pathMaze. And the num_wall_break is incremented, because we destruct a wall. Then, the currentCell is updated as the top of the pathMaze.
            else if(wallToKnockdown==2){
                currentCell.d=false;
                maze[currentCell.x][currentCell.y].d=false;
                maze[currentCell.x][currentCell.y-1].visited=true;
                maze[currentCell.x][currentCell.y-1].u=false;
                pathMaze.push(maze[currentCell.x][currentCell.y-1]);
                num_wall_break++;
                currentCell=pathMaze.top();
                
            }
            // The chosen direction is up. Firstly the booelan expression which represent the up wall of the cell become false, since it is destructed. It becomes false also in the maze matrix. Secondly, the up-neighbour cell become visited.The up-neighbour cell's down wall is destructed, so the booelan expression which represent the down wall of the cell become false. The up-neighbour cell is pushed into the pathMaze. And the num_wall_break is incremented, because we destruct a wall. Then, the currentCell is updated as the top of the pathMaze.
            else if (wallToKnockdown==3){
                currentCell.u=false;
                maze[currentCell.x][currentCell.y].u=false;
                maze[currentCell.x][currentCell.y+1].visited=true;
                maze[currentCell.x][currentCell.y+1].d=false;
                pathMaze.push(maze[currentCell.x][currentCell.y+1]);
                num_wall_break++;
                currentCell=pathMaze.top();
                
            }
        }
        // If the choices is empty, the backtracking must be started because there are no possible wall to destruct for currentCell. So currentCell will pop and we will continue to maze generation process.
        else{
         pathMaze.pop();
         currentCell=pathMaze.top();
        }
        
        
    }
        return maze;}
// This function randomly finds a path which starts with a cell which coordinates are entryX,entryY and finishes with cell which coordinates are exitX ,exitY.
Stack<Cell> findingPath(vector<vector<vector<Cell>>> & allMazes,int & mazeID, int & entryX,int & entryY,int &exitX,int & exitY){
    // to generate a random number
    random_device rd;
    mt19937 gen(rd());
    // path_discovered is a stack which is composed by the Cells. It stores to data of cells which is discovered while path finding.
    Stack<Cell> path_discovered;
    // A maze which is generated randomly before will be chosen by mazeID user input.Then the chosen maze will be used for path finding.
    vector<vector<Cell>> mazeChosen= allMazes[mazeID-1];
    //Firstly initial cell with the coordinates entryX and entryY is pushed to the path_discovered stack.
    path_discovered.push(mazeChosen[entryY][entryX]);
    // currentCell is set as the top of pat_discovered.
    Cell currentCell= path_discovered.top();
    // The boolean expression which represnt whether the cell is discovered while path finding or not become true.
    currentCell.discovered=true;
    // choices vector stores the possible directions that the path finding can process according the rules.
    vector<int> choices;
    // This while loop will continue until reaching the cell with the coordinates exitY and exitX in path finding processing.
    while((currentCell.x !=exitY) || (currentCell.y != exitX)){
    // choices vector is cleared at the beginning because every single cell have different possible directions for the path finding.
        choices.clear();
     // It controls the boundraies whether them are exceed or not.Secondly, it checks if there is a right wall and the right-neighbour whether is discovered or not. To choose right direction; the boundraies must be not exceeded, there there must be no right wall because we have to reach the right-neighbour cell and the right-neighbour cell must be undiscovered. 0 represents the right direction. If all rules are ensured, 0 will push into the choices.
        if((currentCell.x+1) <= mazeChosen.size()-1 ){
            if(!currentCell.r && !mazeChosen[currentCell.x+1][currentCell.y].discovered){
                choices.push_back(0);}
        }
      // It controls the boundraies whether them are exceed or not.Secondly, it checks if there is a left wall and the left-neighbour whether is discovered or not. To choose left direction; the boundraies must be not exceeded, there there must be no left wall because we have to reach the left-neighbour cell and the left-neighbour cell must be undiscovered. 1 represents the left direction. If all rules are ensured, 1 will push into the choices.
        if((currentCell.x-1 ) >=0){
            if(!currentCell.l && !mazeChosen[currentCell.x-1][currentCell.y].discovered){
                choices.push_back(1);}
        }
       // It controls the boundraies whether them are exceed or not.Secondly, it checks if there is a down wall and the down-neighbour whether is discovered or not. To choose down direction; the boundraies must be not exceeded, there there must be no down wall because we have to reach the down-neighbour cell and the down-neighbour cell must be undiscovered. 2 represents the down direction. If all rules are ensured, 2 will push into the choices.
        if((currentCell.y-1) >= 0){
            if(!currentCell.d && !mazeChosen[currentCell.x][currentCell.y-1].discovered){
                choices.push_back(2);}
        }
      // It controls the boundraies whether them are exceed or not.Secondly, it checks if there is a up wall and the up-neighbour whether is discovered or not. To choose up direction; the boundraies must be not exceeded, there must be no up wall because we have to reach the up-neighbour cell and the up-neighbour cell must be undiscovered. 3 represents the up direction. If all rules are ensured, 3 will push into the choices.
        if((currentCell.y+1) <= mazeChosen[0].size()-1 ){
            if(!currentCell.u && !mazeChosen[currentCell.x][currentCell.y+1].discovered){
                choices.push_back(3);}
        }
        // To start the path finding, choices cannot be empty. Since if it is empty it means there are no possible direction to continue to path finding processing
        if(!choices.empty()){
            // it generates a random number in the range 0 and the size of the choices minus 1.
            uniform_int_distribution<int> dis(0, choices.size()-1);
            // random index will be usen for chosing from the choices vector.
            int random_index = dis(gen);
            // by using random_index, a possible direction will be chosen randomly its name is nextCell.
            int nextCell=choices[random_index];
            // The chosen direction is rigt.Firstly,the boolean expression which represents whether the right-neighbour cell is dicovered become true.Then, the right-neighbour cell is pushed into path_discovered. Then, the currentCell is updated as the top of the path_discovered.
            if(nextCell==0){
                mazeChosen[currentCell.x+1][currentCell.y].discovered=true;
                path_discovered.push(mazeChosen[currentCell.x+1][currentCell.y]);
                currentCell=path_discovered.top();
            }
            // The chosen direction is left.Firstly,the boolean expression which represents whether the left-neighbour cell is dicovered become true.Then, the left-neighbour cell is pushed into path_discovered. Then, the currentCell is updated as the top of the path_discovered.
            else if(nextCell==1){
                mazeChosen[currentCell.x-1][currentCell.y].discovered=true;
                path_discovered.push(mazeChosen[currentCell.x-1][currentCell.y]);
                currentCell=path_discovered.top();
            }
            // The chosen direction is down.Firstly,the boolean expression which represents whether the down-neighbour cell is dicovered become true.Then, the down-neighbour cell is pushed into path_discovered. Then, the currentCell is updated as the top of the path_discovered.
            else if(nextCell==2){
                mazeChosen[currentCell.x][currentCell.y-1].discovered=true;
                path_discovered.push(mazeChosen[currentCell.x][currentCell.y-1]);
                currentCell=path_discovered.top();
                
            }
            // The chosen direction is up.Firstly,the boolean expression which represents whether the up-neighbour cell is dicovered become true.Then, the up-neighbour cell is pushed into path_discovered. Then, the currentCell is updated as the top of the path_discovered.
            else if (nextCell==3){
                mazeChosen[currentCell.x][currentCell.y+1].discovered=true;
                path_discovered.push(mazeChosen[currentCell.x][currentCell.y+1]);
                currentCell=path_discovered.top();
            }
            
        }
    // If the choices is empty, the backtracking must be started because there are no possible direction. So currentCell will pop and we will continue to path finding processing.
        else{
            path_discovered.pop();
            currentCell=path_discovered.top();
        }
        
        
    }
    return path_discovered;}

    int main(){
        // num_Mazes is an user input which represents the number of mazes that will generated.
        int num_Mazes;
        cout << "Enter the number of mazes: "; cin >> num_Mazes;
        // num_Rows is an user input which represents the rows of mazes that will generated. num_Cols is an user input which represents the columns of mazes that will generated.
        int num_Rows, num_Cols;
        cout <<"Enter the number of rows and columns (M and N): " ; cin >> num_Rows >> num_Cols;
        // It is an three dimensional vector to store all mazes that are generated.
        vector<vector<vector<Cell>> > allMazes;
        // It is used to create as many matrices as the num_Mazes.
        for (int i = 0; i < num_Mazes; i++) {
            vector<vector<Cell>> maze = generate_maze(num_Rows, num_Cols);
            allMazes.push_back(maze);
            // It creates the txt file which store the maze which is generated.
            ofstream mazeGenerated("maze_" + to_string(i+1) + ".txt");
                    if (mazeGenerated.is_open()) {
                        mazePrint(mazeGenerated, maze, num_Rows, num_Cols);
                        mazeGenerated.close();
                    }
        }
        //mazeID is an user input which represents the ID of mazes that will generated.
        //entryX,entryY are user inputs which represent the coordinates of the cell that path finding starts.
        //exitX,exitY are user inputs which represent the coordinates of the cell that path finding finishes.
        int mazeID,entryX,entryY,exitX,exitY;
        cout <<"All mazes are generated."<< endl;
        cout<<"Enter a maze ID between 1 to 5 inclusive to find a path: ";
        cin >>mazeID;
        cout<<"Enter x and y coordinates of the entry points (x,y) or (column,row): ";
        cin>>entryX>> entryY;
        cout<< "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
        cin>> exitX >>exitY;
        // path_discovered is a stack which stores the data of path finding.
        Stack<Cell> path_discovered= findingPath(allMazes, mazeID, entryX,entryY,exitX,exitY);
        //path_discovered_reversed is a reversed version of the path_discovered.
        Stack<Cell> path_discovered_reversed;
        // It reversed the path_discovered stack.
        while(!path_discovered.isEmpty()){
            Cell temp=path_discovered.top();
            path_discovered.pop();
            path_discovered_reversed.push(temp);
            }
        // It creates the txt file which store the data of path finding.
        ofstream pathGenerated("maze_" + to_string(mazeID) + "_"+to_string(entryX)+ "_"+ to_string(entryY)+ "_"+ to_string(exitX)+ "_"+ to_string(exitY)+".txt");
                if (pathGenerated.is_open()) {
                    filePath(pathGenerated, path_discovered_reversed);
                    pathGenerated.close();
                }
    }


