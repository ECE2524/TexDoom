Room::Room(int number, int psize, int wsize, int csize) {
	roomNumber = number;
	pickupList = new Pickup[psize];
	weaponList = new Weapon[wsize];
	characterList = new Character[csize];
}

Room::~Room() {
	delete pickupList;
	delete weaponList;
	delete characterList;
}

Pickup* Room::getPickupList() {
	return pickupList;
}

Weapon* Room::getWeaponList() {
	return weaponList;
}

Character* Room::getCharacterList() {
	return characterList;
}

void addPickup(Pickup add, int index) {
	pickupList[index] = add;
}

void addWeapon(Weapon add, int index) {
	weaponList[index] = add;
}

void addCharacter(Character add, int index) {
	characterList[index] = add;;
}

void removePickup(int index) {
	pickupList[index].pickupItem();
}

void removeWeapon(int index) {
	weaponList[index].pickupWeapon();
}

void removeCharacter(int index) {
	weaponlist[index].dead();
}

