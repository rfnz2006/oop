#include "Commander.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

Commander::Commander()
{
}

Commander::~Commander()
{
}
int ChooseAbility() {
        std::cout << "Сhoose an ability:\n";
        std::cout << "1. Double Damage\n";
        std::cout << "2. Scanner\n";
        std::cout << "3. Bombing\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            default: return 0;
        }
    

 
}
bool Commander::AskPlayerboardType()
{
    std::cout << "Do you want to generate random board?(y,n)";
    char ans;
    std::cin >> ans;
     std::cout << "User pressed: '" << ans << "'" << std::endl;
    if (ans == 'y') {
     std::cout << "Random board generated!" << std::endl;
        // You can add more messages or perform additional actions here
        std::cout << "Starting to place ships..." << std::endl;
        std::cout << "yssssss" << std::endl;
    
	    return true;}
        else {
    std::cout << "no";
    return false;}
}

Commander::ShipPlacement Commander::AskShipPlacement(unsigned s)
{
    unsigned x, y;
    char o;
    std::cout   << s << "-segment ship; enter X Y O(h or v): ";
    std::cin >> x >> y >> o;
    return ShipPlacement{x,y,o == 'v' };
}Commander::NextAction Commander::AskNextAction(bool ab)
{
    NextAction na;
    na.x = na.y = 0;
    na.cmd = Cmd::Error;
    na.ab = false;

    std::cout << "Select an action:\n"
              << "1. Enter x and y\n"
              << "2. Use the command (Q/L/S)\n";

    // Ignore the newline character left in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read the command
    char command;
    std::cin >> command;

    // Process the command
    switch(command) {
        case '1':
            // Handle option 1
            std::cout << "Enter x and y: ";
            
            if (!(std::cin >> na.x >> na.y)) {
                std::cerr << "Error entering the x and y coordinates." << std::endl;
                return na;
            }
            
            // Display the entered values
            std::cout << "Entered values: x = " << na.x << ", y = " << na.y << std::endl;

            if (ab) {
                char ability;
                std::cout << "Ability? (y/n): ";
                std::cin >> ability;
                na.ab = (ability == 'y' || ability == 'Y');
                int selectedAbility = ChooseAbility();
                na.ab = selectedAbility;
                //na.cmd = Cmd::Move;
            }
            break;

        case 'Q':
        case 'q':
            na.cmd = Cmd::Quit;
            break;

        case 'L':
        case 'l':
            na.cmd = Cmd::Load;
            break;

        case 'S':
        case 's':
            na.cmd = Cmd::Save;
            break;

        default:
            std::cerr << "Wrong command." << std::endl;
            break;
    }

    return na;
}

