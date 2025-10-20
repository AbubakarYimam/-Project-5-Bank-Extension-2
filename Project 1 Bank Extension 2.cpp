#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string ClientFile = "Clients.txt";
const string UserFile = "User.txt";

struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0.0;
	bool CheckForDelete = false;
};

struct sUser {
	string Name;
	short Password = 0;
	short Permission = 0;
	bool CheckForDelete = false;
};
sUser  TargetUser;
// Put this near top (after TargetUser declaration)
bool HasPermission(short bit) {
	// -1 used as full access in your code
	if (TargetUser.Permission == -1) return true;
	return (TargetUser.Permission & bit) == bit;
}



// User

vector<string>SplittingString(string Line, string Delim = "/") {
	vector<string>vUser;
	short pos = 0;
	string sWord = "";
	while ((pos = Line.find(Delim)) != std::string::npos) {
		sWord = Line.substr(0, pos);
		if (sWord != "") {
			vUser.push_back(sWord);
			Line.erase(0, pos + Delim.length());
		}
	}
	if (Line != "") {
		vUser.push_back(Line);
	}
	return vUser;
}

sUser UpLoadToStructor(string Line) {
	sUser User;
	vector<string> vUser = SplittingString(Line);
	User.Name = vUser[0];
	User.Password = stoi(vUser[1]);
	User.Permission = stoi(vUser[2]);
	return User;

}

vector<sUser> UploadUaerFromFile() {
	vector<sUser> vsUser;
	fstream MyFile(UserFile, ios::in);
	if (MyFile.is_open()) {
		sUser User;
		string Line;
		while (getline(MyFile, Line)) {
			User = UpLoadToStructor(Line);
			vsUser.push_back(User);
		}
	}MyFile.close();
	return vsUser;
}


bool CkeckUser(sUser User , sUser & U ) {
	vector<sUser>vsUser = UploadUaerFromFile();
	for (int i = 0;i < vsUser.size();i++) {
		if (User.Name == vsUser[i].Name && User.Password == vsUser[i].Password) {
			U = vsUser[i];
			return true;
		}
	}
	return false;
}

// show Client

sClient UploadClientTostructure(string Line) {
	sClient Client;
	vector<string>vClient = SplittingString(Line);
	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);
	return Client;

}

vector <sClient> UpLoadFromFile() {
	vector<sClient>vsClient;
	fstream MyFile(ClientFile, ios::in);
	if (MyFile.is_open()) {
		sClient Client;
		string Line;
		while (getline(MyFile, Line)) {
			Client = UploadClientTostructure(Line);
			vsClient.push_back(Client);
		}
		MyFile.close();
	}
	return vsClient;
}

void DisplayEachClient(sClient Client) {
	cout << "|" << setw(15) << left << Client.AccountNumber;
	cout << "|" << setw(15) << left << Client.PinCode;
	cout << "|" << setw(15) << left << Client.Name;
	cout << "|" << setw(15) << left << Client.Phone;
	cout << "|" << setw(15) << left << Client.AccountBalance;
}

void ShowAllClient() {
	if (!HasPermission(1)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
	}
	vector<sClient>Client = UpLoadFromFile();
	cout << "\n\t\t\t\t\t\tClients(" << Client.size() << ").\n ";
	cout << "\n=============================================================================================================\n";
	cout << "|" << setw(15) << left << "Account Number";
	cout << "|" << setw(15) << left << "Pin Code";
	cout << "|" << setw(15) << left << "Name";
	cout << "|" << setw(15) << left << "Phone";
	cout << "|" << setw(15) << left << "Account Balance\n";
	cout << "=============================================================================================================\n";
	for (sClient s : Client) {
		DisplayEachClient(s);
		cout << "\n";
	}
	cout << "=============================================================================================================\n";
	system("pause>0");
}

//Delete Client 

void ShowClient(sClient Client) {
	cout << "\nAccount Number : " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance : " << Client.AccountBalance;
}


string ReadAcc() {
	string Acc;
	cout << "\nEnter Account Number : ";
	cin >> Acc;
	return Acc;
}

void DeleteTheClient(string& Client, vector<sClient>& vsClient) {
	for (sClient& s : vsClient) {
		if (Client == s.AccountNumber)
			s.CheckForDelete = true;
	}
}

bool IsExisted(string Client, vector<sClient>vsClient, sClient& C) {
	for (sClient s : vsClient) {
		if (Client == s.AccountNumber) {
			C = s;
			return true;
		}
	}
	return false;
}

string ConvertDataToLine(sClient Client, string Sepa = "/") {
	string Line;
	Line += Client.AccountNumber + Sepa;
	Line += Client.PinCode + Sepa;
	Line += Client.Name + Sepa;
	Line += Client.Phone + Sepa;
	Line += to_string(Client.AccountBalance);
	return Line;
}

void SaveToFile(vector<sClient> vsClient) {
	fstream MyFile(ClientFile, ios::out);
	for (sClient s : vsClient) {
		if (s.CheckForDelete == false) {
			MyFile << ConvertDataToLine(s) << endl;
		}
	}

}

void Delete() {

	char is = 'y';
	sClient Client;
	do {
		system("cls");
		cout << "\n============================================";
		cout << "\n               Delete Option                ";
		cout << "\n============================================";
		vector<sClient>vsClient = UpLoadFromFile();
		char s = 'y';
		string Acc = ReadAcc();
		if (IsExisted(Acc, vsClient, Client)) {
			ShowClient(Client);
			cout << "\nDo You want To Delete This Account (y/n)? ";
			cin >> s;
			if (s == 'y') {
				DeleteTheClient(Acc, vsClient);
				SaveToFile(vsClient);
			}
		}
		else {
			cout << "\n(" << Acc << ") Is Not Found !\n";

		}
		cout << "\nDo You Want To Delete Account ! (y/n) ?  ";
		cin >> is;
	} while (is == 'y');
}

void DeleteOption() {
	if (!HasPermission(4)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
	}
	cout << "\n============================================";
	cout << "\n               Delete Option                ";
	cout << "\n============================================";
	Delete();
}

//Update Client
sClient Update(sClient Client) {
	cout << "\nEnter Account Number : ";
	cin >> Client.AccountNumber;
	cout << "\nEnter Pin Code : ";
	cin >> Client.PinCode;
	cout << "\nEnter Name : ";
	cin >> Client.Name;
	cout << "Enter Phone : ";
	cin >> Client.Phone;
	cout << "\nEnter Account Balance : ";
	cin >> Client.AccountBalance;
	return Client;
}

void UpdateClient() {

	sClient Client;
	char is = 'y';

	while (is == 'y') {
		char s = 'y';
		vector<sClient>vsClient = UpLoadFromFile();
		string Acc = ReadAcc();
		if (IsExisted(Acc, vsClient, Client)) {
			ShowClient(Client);
			cout << "\nDo You Want To Update ? (y/n)? ";
			cin >> s;
			if (s == 'y') {
				for (sClient& s : vsClient)
					if (Acc == s.AccountNumber) {
						s = Update(s);
						break;
					}
				SaveToFile(vsClient);
				cout << "\nUpdate it Succesfully !";
			}
		}
		else {
			cout << "\n(" << Acc << ") is Not Found ! \n";
		}
		cout << "Do You Want To Update Again  (y/n)? ";
		cin >> is;

	}
}

void UpdateOtion() {
	if (!HasPermission(8)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
}
	cout << "\n======================================";
	cout << "\n           Update Option              ";
	cout << "\n======================================";
	UpdateClient();
}

// Add Client

sClient AddCLient(string Acc) {
	sClient Client;
	cout << "\nADD New Client .\n";
	Client.AccountNumber = Acc;
	cout << "\nEnter Pin Code : ";
	cin >> Client.PinCode;
	cout << "\nEnter Name : ";
	cin >> Client.Name;
	cout << "\nEnter Phone : ";
	cin >> Client.Phone;
	cout << "\nEnter Account Balance : ";
	cin >> Client.AccountBalance;
	return Client;
}

void AddToFile(sClient Client) {
	fstream MyFile(ClientFile, ios::app);
	if (MyFile.is_open()) {
		MyFile << ConvertDataToLine(Client) << endl;
	}
}

void AddNewClient() {
	char is = 'y';

	sClient Client;
	while (is == 'y') {
		char s = 'y';
		system("cls");
		cout << "\n======================================";
		cout << "\n        Add New Client Option         ";
		cout << "\n======================================";
		vector<sClient>vsClient = UpLoadFromFile();
		string Acc = ReadAcc();
		while (IsExisted(Acc, vsClient, Client)) {
			cout << "\n(" << Acc << ") Is already Exisrted Enter another Account Number : ";
			cin >> Acc;

		}
		Client = AddCLient(Acc);
		cout << "\nDo You want To Add The Client (y/n)? ";
		cin >> s;
		if (s == 'y') {
			AddToFile(Client);
			cout << "\nAdd Secssefully ! ";
		}
		cout << "\nDo Want To Add Another New Client (y/n)? ";
		cin >> is;
	}
}

void AddClientOptions() {
	if (!HasPermission(2)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
	}
	cout << "\n======================================";
	cout << "\n        Add New Client Option         ";
	cout << "\n======================================";
	AddNewClient();
}

// Show Client

void ShowEach() {
	char is = 'y';
	vector <sClient>vsClient = UpLoadFromFile();
	sClient Client;
	while (is == 'y') {
		system("cls");
		cout << "\n======================================";
		cout << "\n            Find Option               ";
		cout << "\n======================================";
		vector <sClient>vsClient = UpLoadFromFile();
		sClient Client;
		string Acc = ReadAcc();
		if (IsExisted(Acc, vsClient, Client)) {
			ShowClient(Client);
		}
		else {
			cout << "\n(" << Acc << ") is Not Found ! \n";

		}
		cout << "\nDo You Want To See Anther Client (y/n)? ";
		cin >> is;
	}
}

void FindClientOption() {
	if (!HasPermission(16)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
	}
	cout << "\n======================================";
	cout << "\n             Find Option              ";
	cout << "\n======================================";
	ShowEach();
}

// Deposite

sClient DeposuiteMoney(sClient Client) {
	int num = 0;
	cout << "Enter Ammount Of Money You Want To Deposite : ";
	cin >> num;
	Client.AccountBalance += num;
	return Client;

}

void Deposite() {

	char is = 'y';

	while (is == 'y') {
		system("cls");
		vector<sClient>vsClient = UpLoadFromFile();
		sClient Client;
		cout << "\n======================================";
		cout << "\n             Deposite Option          ";
		cout << "\n======================================";
		string Acc = ReadAcc();
		if (IsExisted(Acc, vsClient, Client)) {

			ShowClient(Client);
			char s = 'y';
			cout << "\nDo You Want To Deposite  To This Account (y/n)? ";
			cin >> s;
			if (s == 'y') {
				for (sClient& s : vsClient) {
					if (s.AccountNumber == Acc) {
						s = DeposuiteMoney(s);
						SaveToFile(vsClient);
						cout << "\nDeposite Susscefully !";
						break;
					}
				}
			}
		}
		else {
			cout << "\n(" << Acc << ") is Not Found !\n";
		}
		cout << "\nDo Want To Deposite Again (y/n)? ";
		cin >> is;
	}
}


void DepositeOption() {
	cout << "\n======================================";
	cout << "\n             Deposite Option          ";
	cout << "\n======================================";
	Deposite();
}

// WithDraw

sClient WithDrawMoney(sClient Client) {
	long  num = 0;
	cout << "Enter Ammount Of Money You Want To Deposite : ";
	cin >> num;
	if (num <= Client.AccountBalance)
		Client.AccountBalance -= num;
	else {
		cout << "ERROR  You Can Withdraw Upto " << Client.AccountBalance;
	}

	return Client;

}


void WithDraw() {
	vector<sClient>vsClient = UpLoadFromFile();
	sClient Client;
	char is = 'y';

	while (is == 'y') {
		system("cls");
		cout << "\n======================================";
		cout << "\n             WithDraw Option          ";
		cout << "\n======================================";
		string Acc = ReadAcc();
		if (IsExisted(Acc, vsClient, Client)) {
			ShowClient(Client);
			char s = 'y';
			cout << "\nDo You Want To Witdraw  To This Account (y/n)? ";
			cin >> s;
			if (s == 'y') {
				for (sClient& s : vsClient) {
					if (s.AccountNumber == Acc) {
						s = WithDrawMoney(s);
						SaveToFile(vsClient);
						cout << "\nWithdraw Susscefully !";
						break;
					}
				}
			}
		}
		else {
			cout << "\n(" << Acc << ") is Not Found !\n";
		}
		cout << "\nDo Want To WithDraw Again (y/n)? ";
		cin >> is;
	}
}

void WithDrawOption() {
	cout << "\n======================================";
	cout << "\n             WithDraw Option          ";
	cout << "\n======================================";
	WithDraw();
}

// Show Balance 

void ShowEachBalance(sClient Client) {
	cout << "|" << setw(15) << left << Client.AccountNumber;
	cout << "|" << setw(15) << left << Client.Name;
	cout << "|" << setw(15) << left << Client.AccountBalance;
}

void DisplayBalance() {
	vector<sClient>vsClient = UpLoadFromFile();
	cout << "\n\t\t\tClient(" << vsClient.size() << ").\n";
	cout << "\n===============================================================\n";
	cout << "|" << setw(15) << left << "Account Number";
	cout << "|" << setw(15) << left << "Name";
	cout << "|" << setw(15) << left << "Account Balance";
	cout << "\n===============================================================\n";
	for (sClient s : vsClient) {
		ShowEachBalance(s);
		cout << "\n";
	}
	cout << "===============================================================\n";
}

void DisplayBaanceOption() {
	cout << "\n======================================";
	cout << "\n         Diplay Balance Option        ";
	cout << "\n======================================";
	DisplayBalance();
}

short MainMenueScreen();
// Transaction

void DiaplayTrancsactionMenue();

void returnToTransactionMenue() {
	cout << "\n\nClick Any Button To Return To Transcation Menue.....";
	system("pause>0");
	DiaplayTrancsactionMenue();
}

void selectTranscation(short num) {
	switch (num) {
	case 1: {
		system("cls");
		DepositeOption();
		returnToTransactionMenue();
		break;
	}
	case 2: {
		system("cls");
		WithDrawOption();
		returnToTransactionMenue();
		break;
	}
	case 3: {
		system("cls");
		DisplayBaanceOption();
		returnToTransactionMenue();
		break;
	}
	case 4: {
		MainMenueScreen();
	}
	}
}

void DiaplayTrancsactionMenue() {
	if (!HasPermission(32)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
	}
	system("cls");
	cout << "\n======================================";
	cout << "\n        Transaction Option Option     ";
	cout << "\n======================================\n";
	short num;
	cout << "[1] Deposite \n";
	cout << "[2] Withdraw \n";
	cout << "[3] Show Balance \n";
	cout << "[4] return To Menue \n";
	cout << "Enter Choose : ";
	cin >> num;
	selectTranscation(num);
}


void SelectOptions(int Num);
//list user
void ListEachUser(sUser User) {
	cout << "|" << setw(15) << left << User.Name;
	cout << "|" << setw(15) << left << User.Password;
	cout << "|" << setw(15) << left << User.Permission;

}

void ListUser() {
	vector<sUser>vsUser = UploadUaerFromFile();
	cout << "\n\t\t\tUser List (" << vsUser.size() << ") User(s).\n";
	cout << "|" << setw(15) << left << "Name";
	cout << "|" << setw(15) << left << "Password";
	cout << "|" << setw(15) << left << "Permission";
	cout << "\n==================================================================================================\n";
	for (sUser s : vsUser) {
		ListEachUser(s);
		cout << "\n";
	}
	cout << "==================================================================================================\n";
}
// Add user
string ConvertUserToLine(sUser User) {
	string Line;
	Line += User.Name + "/";
	Line += to_string(User.Password) + "/";
	Line += to_string(User.Permission);
	return Line;
}

void saveUserToFile(sUser User) {
	fstream MyFile(UserFile, ios::app);
	MyFile << ConvertUserToLine(User) <<endl;
}

void GiveAcces(sUser& User, char is) {
	if (is == 'y') {
		User.Permission = -1;
	}
	else {
		short pos = 0;
		cout << "Do You Want To Give Access To \n\n";
		cout << "Show Client List ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=1;
		cout << "\nAdd New Client  ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=2;
		cout << "\nDeletw Client ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=4;
		cout << "\nUpdate Client  ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=8;
		cout << "\nFind Client ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=16;
		cout << "\nTranscation ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=32;
		cout << "\nManage User ? (y/n) ? ";
		cin >> is;
		if (is == 'y')pos +=64;
		User.Permission = pos;
	}
}

sUser readUser() {
	sUser name;
	cout << "Enter UserName : ";
	cin >> name.Name;
	cout << "Enter Password : ";
	cin >> name.Password;
	return name;
}

bool isUserExisted(sUser name, vector<sUser> vsUser, sUser User) {
	for (sUser s : vsUser) {
		if (s.Name == name.Name)return true;
	}
	return false;
}


void AddNewUser() {
	vector<sUser>vsUser = UploadUaerFromFile();
	sUser User;
	char is = 'y';
	while (is == 'y') {
		system("cls");

		cout << "=================================\n";
		cout << "       Add New User Screen       \n";
		cout << "=================================\n";
		cout << "\nAdd New User : \n";
		sUser name = readUser();
		while (isUserExisted(name, vsUser, User)) {
			cout << "ERROR (" << name.Name << ") is alredy existed Enter Another User Name ?";
			name = readUser();
		}
		char s = 'y';
		cout << "Do You Want To Give Full Acces (y/n) ? ";
		cin >> s;
		GiveAcces(name, s);
		saveUserToFile(name);
		cout << "\n\nAdd Succefully , Do Want To Add More (y/n)?  ";
		cin >> is;
	}
}

void AddUserOption() {
	cout << "=================================\n";
	cout << "       Add New User Screen       \n";
	cout << "=================================\n";
	AddNewUser();

}

// Delete User


void showUser(sUser User) {
	cout << "\n=====================\n";
	cout << "Nme : " << User.Name;
	cout << "\nPassword : " << User.Password;
	cout << "\nPermssion  : " << User.Permission;
}

string ReadUser() {
	string Name;
	cout << "\nEnter User Name : ";
	cin >> Name;
	return Name;
}
bool isUserExisted(string Name, vector <sUser>& vsUser, sUser& User) {
	for (sUser s : vsUser) {
		if (s.Name == Name) {
			User = s;
			return true;
		}
	}
	return false;
}
void PrintUserToFile(vector<sUser>vsUser) {

	fstream MyFile(UserFile, ios::out);
	for (sUser s : vsUser) {
		if (s.CheckForDelete == false) {
			MyFile << ConvertUserToLine(s) << endl;
		}
	}


}

void MarkToDelete(vector<sUser>& vsUser, string Name) {
	for (sUser& s : vsUser) {
		if (Name == s.Name)s.CheckForDelete = true;
	}
}
void DeleteUser() {

	sUser User;
	char is = 'y';
	while (is == 'y') {
		system("cls");
		cout << "\n======================================\n";
		cout << "            Delete User Options";
		cout << "\n======================================\n";
		vector<sUser> vsUser = UploadUaerFromFile();
		string Name = ReadUser();
		if (isUserExisted(Name, vsUser, User)) {
			showUser(User);
			if (User.Name == "Admin") {
				cout << "\n\n----------------------------------------\nYou Can't Delete The Admin\n------------------------------------";
				system("pause>0");
				return;
			}
			char s = 'y';
			cout << "\nDp You Want To Delete  User (y/n)? ";
			cin >> s;
			if (s == 'y') {
				MarkToDelete(vsUser, Name);
				PrintUserToFile(vsUser);
				cout << "\nDelete Sussesflly ! ";
			}
		}
		cout << "\nDo Want To Delete Another User (y/n)? ";
		cin >> is;

	}
}

void DeleteUserOPtion() {
	cout << "\n======================================\n";
	cout << "            Delete User Options";
	cout << "\n======================================\n";
	DeleteUser();
}
// Update 
sUser Update(sUser User) {
	cout << "\nEnter Name : ";
	cin >> User.Name;
	cout << "Enter Password : ";
	cin >> User.Password;
	return User;
}

void UpdateUser() {
	char is = 'y';
	while (is == 'y') {
		system("cls");
		cout << "\n=============================\n";
		cout << "        Update User Option";
		cout << "\n=============================\n";
		vector<sUser>vsUser = UploadUaerFromFile();
		sUser User;
		string Name = ReadUser();
		if (isUserExisted(Name, vsUser, User)) {
			showUser(User);
			if (User.Name == "Admin") {
				cout << "\n\n----------------------------------------\nYou Can't Update The Admin\n------------------------------------";
				system("pause>0");
				return;
			}
			char s = 'y';
			cout << "\nDo You Want To Update (y/n)? ";
			cin >> s;
			if (s == 'y') {
				for (sUser& s : vsUser) {
					if (s.Name == Name) {
						s = Update(s);
						break;
					}
				}
				PrintUserToFile(vsUser);
			}
		}
		cout << "\nDo You Want To Upadate Again (y/n)? ";
		cin >> is;
	}
}
void UpdateUserOption() {
	cout << "\n=============================\n";
	cout << "        Update User Option";
	cout << "\n=============================\n";
	UpdateUser();
}
// find User

void Find() {
	char is = 'y';
	while (is == 'y') {
		system("cls");
		cout << "\n=============================\n";
		cout << "        Find User Option";
		cout << "\n=============================\n";
		vector<sUser>vsUser = UploadUaerFromFile();
		sUser User;
		string Name = ReadUser();
		if (isUserExisted(Name, vsUser, User)) {
			showUser(User);
		}
		cout << "\nDo You Want To See Another User (y/n)? ";
		cin >> is;
	}
}
void FindUserOption() {
	cout << "\n=============================\n";
	cout << "        Find User Option";
	cout << "\n=============================\n";
	Find();
}

void SelectOptions(int Num);
// Manage user
void SelectUserOption(short Num);
short ManageMenueScreen();

void returnToUser() {
	cout << "Click Anty Thing To return to user................";
	system("pause>0");
	SelectUserOption(ManageMenueScreen());

}
short ManageMenueScreen() {
	system("cls");
	cout << "=================================\n";
	cout << "       Manage Users  Menue Screen    \n";
	cout << "=================================\n";
	cout << "[1] List User \n";
	cout << "[2] Add New User \n";
	cout << "[3] Delete User \n";
	cout << "[4] Update User \n";
	cout << "[5] Find User \n";
	cout << "[6] Main Menue \n";
	cout << "=================================\n";
	short choose;
	cout << "Choose What You want To Do [1 to 6]? ";
	cin >> choose;
	return choose;
}
void SelectUserOption(short Num) {
	if (!HasPermission(64)) {
		cout << "----------------------------------------------------\nAccess Denied You Sont Have Permission \n Contact The Admin For Permission\n----------------------------------------------------\n ";
		return;
	}
	switch (Num) {
	case 1: {
		system("cls");
		ListUser();
		returnToUser();
		break;
	}
	case 2: {
		system("cls");
		AddUserOption();
		SelectUserOption(ManageMenueScreen());
		break;
	}
	case 3: {
		system("cls");
		DeleteUserOPtion();
		SelectUserOption(ManageMenueScreen());
		break;
	}
	case 4: {
		system("cls");
		UpdateUserOption();
		SelectUserOption(ManageMenueScreen());
		break;

	}
	case 5: {
		system("cls");
		FindUserOption();
		SelectUserOption(ManageMenueScreen());
		break;

	}
	case 6: {
		system("cls");
		MainMenueScreen();
		break;
	}
	}
}

short MainMenueScreen() {
	system("cls");
	cout << "=================================\n";
	cout << "        Main Menue Screen    \n";
	cout << "=================================\n";
	cout << "[1] Show Client List \n";
	cout << "[2] Add New Client  \n";
	cout << "[3] Delete Client  \n";
	cout << "[4] Update Client Info \n";
	cout << "[5] Find Client  \n";
	cout << "[6] transaction \n";
	cout << "[7] Manage User\n";
	cout << "[8] Logout \n";
	cout << "=================================\n";
	short choose;
	cout << "Choose What You want To Do [1 to 8]? ";
	cin >> choose;
	return choose;
}

void ReturnToMenue() {

	cout << "\nPress Any Thing To Return Back To Back .......";
	system("pause>0");
	SelectOptions(MainMenueScreen());

}

void AskLogin(sUser User) {


	while (true) {
		cout << "Enter UserName ? ";
		cin >> User.Name;
		cout << "Enter Password ? ";
		cin >> User.Password;
		sUser User1;
		if (CkeckUser(User,User1)) {
			TargetUser = User1;
			SelectOptions(MainMenueScreen());
			

		}
		else {
			system("cls");
			cout << "\n------------------------------------\n";
			cout << "             Login Screen               ";
			cout << "\n------------------------------------\n";
			cout << "Invalid UserName/PassWord!\n";
			

			
		}
	}
}

void LoginScreen() {
	cout << "\n------------------------------------\n";
	cout << "             Login Screen               ";
	cout << "\n------------------------------------\n";
	sUser User;
	AskLogin(User);


}

void SelectOptions(int Num) {
	
		switch (Num) {
		case 1: {
			system("cls");
			ShowAllClient();
			ReturnToMenue();
			break;
		}
		case 2: {
			system("cls");
			AddClientOptions();
			ReturnToMenue();
			break;
		}
		case 3: {
			system("cls");
			DeleteOption();
			ReturnToMenue();
			break;
		}
		case 4: {
			system("cls");
			UpdateOtion();
			ReturnToMenue();
			break;
		}
		case 5: {
			system("cls");
			FindClientOption();
			ReturnToMenue();
			break;
		}
		case 6: {
			system("cls");
			DiaplayTrancsactionMenue();
			SelectOptions(MainMenueScreen());
			break;
		}
		case 7: {
			system("cls");
			SelectUserOption(ManageMenueScreen());
			SelectOptions(MainMenueScreen());
			break;
		}
		case 8: {
			system("cls");
			LoginScreen();
			break;
		}
		}
		}
	

	


int main() {
	LoginScreen();

}
