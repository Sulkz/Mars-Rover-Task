#include <iostream>
#include <string>
#include <vector>
#include <limits>


using namespace std;
class Rover {

    int positionX, positionY, upperBoundX, upperBoundY;
    char orientation;


public:
    Rover(int x, int y, char orientation, int maxX, int maxY) {
        this->positionX = x;
        this->positionY = y;
        this->orientation = orientation;
        this->upperBoundX = maxX;
        this->upperBoundY = maxY;
    }

    // Deals with orientation of rover for moving, and turning
    void movement() {
        switch (orientation) {
            case 'N':
                if (positionY < upperBoundY)
                    positionY++;
            break;
            case 'E':
                if (positionX < upperBoundX)
                    positionX++;
            break;
            case 'S':
                if (positionY > 0)
                    positionY--;
            break;
            case 'W':
                if (positionX > 0)
                    positionX--;
            break;
        }
    }

    void turnRight() {
        switch (orientation) {
            case 'N':
                orientation = 'E';
            break;
            case 'E':
                orientation = 'S';
            break;
            case 'S':
                orientation = 'W';
            break;
            case 'W': orientation = 'N';
            break;
        }
    }

    void turnLeft() {
        switch (orientation) {
            case 'N':
                orientation = 'W';
            break;
            case 'E':
                orientation = 'N';
            break;
            case 'S':
                orientation = 'E';
            break;
            case 'W':
                orientation = 'S';
            break;
        }
    }

    void deployCommands(const string &commands) {
        for (char command : commands) {
            if (command == 'L') {
                turnLeft();
            } else if (command == 'R') {
                turnRight();
            } else if (command == 'M') {
                movement();
            } else {
                cout << "Invalid command detected: " << command << endl;
            }
        }
    }

    // Outputs for each rovers ending positions
    void endPos() {
        cout <<  positionX <<" "<< positionY << " " << orientation << '\n';
    }
};


void validPos(int upperX, int upperY, int &x, int &y, char &orient) {
  while (true) {
    cout << "Enter rover's position (x-coordinate, y-coordinate, and orientation): ";
    cin >> x >> y >> orient;


    // Input sanitisation to prevent infinite loop when int not typed ;/

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input please enter valid numbers." << endl;
      continue;
    }

    if (x >= 0 && x <= upperX && y >= 0 && y <= upperY &&
        (orient == 'N' || orient == 'E' || orient == 'S' || orient == 'W')) {
      break;
    }
    cout << "Invalid input position out of bounds or incorrect orientation." << endl;
  }
}

// validates if the Characters used are allowed
bool validCommand(string &commands) {
    for (char command : commands) {
        if (command != 'L' && command != 'R' && command != 'M') {
            return false;
        }
    }
    return true;
}

void getValidCommands(string &commands) {
    while (true) {
        cout << "Input commands for the rovers only L/M/R: ";
        getline(cin, commands);

        if (validCommand(commands)) {
            break;
        }

        cout << "Invalid input please enter only L/M/R .\n";
    }
}

int main() {

  // Plateau upper bounds
  int upperBoundX, upperBoundY;
  int s, t, s2, t2;
  char orientation, orientation2;
  string dir, dir2;

  // User input for plateau size
  cout << "Provide the upper coordinates of the plateau: ";
  cin >> upperBoundX >> upperBoundY;

  // Rover 1 Querys
  validPos(upperBoundX, upperBoundY, s, t, orientation);
  Rover rover1(s, t, orientation, upperBoundX, upperBoundY);
  cin.ignore();
  validCommand(dir);
  getValidCommands(dir);




  // Rover 2 Query
  validPos(upperBoundX, upperBoundY, s2, t2, orientation2);
  Rover rover2(s2, t2, orientation2, upperBoundX, upperBoundY);
  cin.ignore(); // works to
  validCommand(dir2);
  getValidCommands(dir2);


  // Results OF end Coords with head Orientation
  rover1.deployCommands(dir);
  rover1.endPos();

  rover2.deployCommands(dir2);
  rover2.endPos();

  return 0;
}