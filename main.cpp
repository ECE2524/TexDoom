#include "Room.cpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<Room*> parser(char* filename) {
	string line;
	vector<Room*> roomList;
	ifstream myfile(filename);
	int roomIndex = 0;

	if(myfile.is_open()){
		while(getline(myfile, line)){
			roomIndex++;
			roomList.push_back(new Room(roomIndex));
			for(int i = 0; i < line.size(); i = i+4){
				string currentitem = line.substr(i,3);
				int currentitemquantity = line[i+3]-'0';

				if(currentitem == "FHP"){
					for(int j = 0; j < currentitemquantity; j++)
						roomList.back()->addCharacter(new Character(currentitem, 5,5,5,5));
				}
				else if (currentitem == "FHS"){
					for(int j = 0; j < currentitemquantity; j++)
                                                roomList.back()->addCharacter(new Character(currentitem,5,5,5,5));
                                }
				else if (currentitem ==  "IMP"){
					 for(int j = 0; j < currentitemquantity; j++)
                                                roomList.back()->addCharacter(new Character(currentitem,5,5,5,5));
                                }
				else if (currentitem == "BER"){
					 for(int j = 0; j < currentitemquantity; j++)
						roomList.back()->addPickup(new Pickup(currentitem));
				}
				else if (currentitem == "VIS"){
					 for(int j = 0; j < currentitemquantity; j++)
						roomList.back()->addPickup(new Pickup(currentitem));
				}
				else if (currentitem =="SHO"){
					 for(int j = 0; j < currentitemquantity; j++)
						roomList.back()->addWeapon(new Weapon(currentitem, 5));
				}
				else if (currentitem == "SSH"){
					 for(int j = 0; j < currentitemquantity; j++)
						roomList.back()->addWeapon(new Weapon(currentitem, 10));
				}
				else  cout << "something in the wad is undefined";
			}
		}
	}
	return roomList;
}

int main(int argc, char* argv[]) {
	string line;
	int lineNum;
	int numRooms;
	char* filename;
	vector<Room*> roomList;

	// WAD Parsing Code
	filename = argv[1];
	roomList = parser(filename);

	cout << "Finished parsing" << endl;

	roomList[0]->printCharacters();
	roomList[0]->printPickups();
	roomList[0]->printWeapons();

	string playerName;

	// Game start
	cout << "Welcome to Tex Doom! blah blah blah" << endl;
	cout << "Please enter your character's name!" << endl;
	cin >> playerName;

	Player* player = new Player(playerName, 5, 5, 100, 5, 5);


	cout << "Description of all player stats and current values blah blah" << endl;
	player->rerollStats();
	player->printStats();


	int reroll = 1;
	int check;

	// Query user for reroll
	while (reroll) {
		cout << "Type '0' to reroll or '1' to start the game." << endl;
		cin >> check;
		if (check == 0) {
			player->rerollStats();
			player->printStats();
		}
		else if (check == 1)
			reroll = 0;
		else
			cout << "Please enter either '0' to reroll or '1' to start the game." << endl;
	}



	int playerLocation = 0;
	int target = 0;
	bool advance = false;

	// Interaction
	//while(playerLocation < roomList.size()) {
		//while(!advance) {
			// Show visible items and monsters
			cout << "Choose a weapon to pick up" << endl;
			roomList[playerLocation]->printWeapons();
			cin >> target;

			Weapon* currentWeapon = roomList[playerLocation]->getWeapon(target - 1);
			player->addWeapon(new Weapon(currentWeapon->getWeaponName(), currentWeapon->getWeaponPower()));
			roomList[playerLocation]->removeWeapon(target - 1);

			player->setCurrentWeapon(0);

			cout << player->getCurrentWeapon()->getWeaponName() << endl;

			cout << "Choose a pickup to pick up" << endl;
			roomList[playerLocation]->printPickups();
			cin >> target;

			roomList[playerLocation]->removePickup(target - 1);
			roomList[playerLocation]->printPickups();

			// Allow player to grab item or select target
			cout << "Choose a target (1-n)" << endl;
			roomList[playerLocation]->printCharacters();
			cin >> target;

			if ((target > 0) && (target <= roomList[playerLocation]->getNumCharacters())) {}
				roomList[playerLocation]->attack(1, player, target - 1);

			roomList[playerLocation]->printCharacters();

			// Monster attacks
			roomList[playerLocation]->attack(0, player, 0);
			cout << player->getCurrentHitpoints() << endl;
		//}
	//}
}
