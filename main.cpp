#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
const int MAX = 100;
enum status{
	Prieta = 0,
	Otkazana = 1,
	Remontiran = 2
};
string status_str[3] = {"Prieta", "Otkazana", "Remontiran"};
string device_types[5] = {"Telefon", "Tablet", "Laptop", "Monitor", "Televizor"};
struct Date{
	int day, month, year;
};
struct Order{
	int order_id;
	Date date_accepted;
	string client_name;
	int device_type;
	string serial_number;
	char device_problem[50];

	// Sled remont
	string tehnician_name;
	char repair[50];
	double price;
	int days_in_shop;
	int current_status = Prieta;
};
struct ComputerShop{
	Order orders[MAX];
	int order_counter = 0;
};
void vuvedi_data(Date&);

bool menu(ComputerShop&);
void add_device(ComputerShop&);
void add_multiple(ComputerShop&);

void print_one(Order&);
void print_all(ComputerShop&);

void menu_correction(ComputerShop&);
void correct_order(ComputerShop&);
void stop_order(ComputerShop&);
void service_order(ComputerShop&);

void odit_menu(ComputerShop&);
void sort_by_serial_number(ComputerShop&);
void filter_by_type(ComputerShop&);
void filter_by_name(ComputerShop&);

void read_from_text_file(ComputerShop&);
void append_to_text_file(Order&);
void save_all_text_file(ComputerShop&);


bool izhod();
int main(){
	ComputerShop ardes;
	read_from_text_file(ardes);
	while(menu(ardes));
	cout << "Fakluteten nomer, ime, grupa";
	return 0;
}
void vuvedi_data(Date& nova_data){
	cout << "\tVuvedi den: ";
	cin >> nova_data.day;
	cout << "\tVuvedi mesec: ";
	cin >> nova_data.month;
	cout << "\tVuvedi godina: ";
	cin >> nova_data.year;
}
bool menu(ComputerShop& ardes){
	system("cls");
	int choice;
	cout << "Glavno menu" << endl;
	cout << "1. Dobavqne na edno ustroistvo" << endl;
	cout << "2. Dobavqne na spisuk s ustroistva" << endl;
	cout << "3. Izvejdane na vsichki ustroistva" << endl;
	cout << "4. Korekciq" << endl;
	cout << "5. Servizno obslujvane na ustroistvo" << endl;
	cout << "6. Odit na poruchkite v podmenu" << endl;
	cout << "7. Izhod" << endl;
	do{
		cout << "Vuvedi izbor: ";
		cin >> choice;
	}while(choice < 1 || choice > 7);
	switch(choice){
		case 1:
			add_device(ardes);
			break;
		case 2:
			add_multiple(ardes);
			break;
		case 3:
			print_all(ardes);
			break;
		case 4:
			menu_correction(ardes);
			break;
		case 5:
			service_order(ardes);
			break;
		case 6:
			odit_menu(ardes);
			break;
		case 7:
			if(izhod()) return false;
			return true;
	}
	return true;
}
void add_device(ComputerShop& ardes){
	system("cls");
	if(ardes.order_counter == MAX){
		cout << "Dostignat e maksimalniqt broi ustroistva" << endl;
		system("pause");
		return;
	}
	bool temp_bool;
	string temp_string;
	int temp_int;
	Order& new_order = ardes.orders[ardes.order_counter];
	cout << "Dobavqne na ustroistvo: " << endl;
	do{
		temp_bool = false;
		cout << "\tNomer poruchka: ";
		cin >> temp_int;
		for(int i = 0; i <ardes.order_counter; i++){
			if(temp_int == ardes.orders[i].order_id) temp_bool = true;
		}
		if(temp_bool)
			cout << "\tNomera na poruchkata e veche izpolzvan, molq vuvedete drug" << endl;
	}while(temp_bool);
	new_order.order_id = temp_int;
	cout << "\tIme na Klient: ";
	cin.ignore();
	getline(cin, new_order.client_name);
	vuvedi_data(new_order.date_accepted);
	do{
		temp_bool = true;
		cout << "\tUstroistvo: ";
		cin >> temp_string;
		for(int i = 0; i < 5; i++)
			if(temp_string == device_types[i]){
				new_order.device_type = i;
				temp_bool = false;
			}
	}while(temp_bool);
	cout << "\tSerien nomer na ustroistvoto: ";
	cin >> new_order.serial_number;
	cout << "\tProblem spored klienta ( do 50 simvola ): ";
	cin.ignore(); // Ignore \n from last input
	cin.getline(new_order.device_problem, 50, '\n');
	append_to_text_file(new_order);
	ardes.order_counter++;
}
void add_multiple(ComputerShop& ardes){
	system("cls");
	if(ardes.order_counter == MAX){
		cout << "Dostignat e maksimalniqt broi ustroistva" << endl;
		system("pause");
		return;
	}
	int number_of_devices, max_devices = MAX - ardes.order_counter;
	do{
		cout << "Golemina na spisuka s ustroistva ( 1 - " << max_devices << " ): ";
		cin >> number_of_devices;
	}while(number_of_devices < 1 || number_of_devices > max_devices);
	for(int i = 0; i < number_of_devices; i++){
		int prekusvane;
		add_device(ardes);
		if(i == number_of_devices - 1) break;
		do{
			cout << "Iskate li da prekusnete vuvejdaneto ( 1 za da, 0 za ne ): ";
			cin >> prekusvane;
		}while(prekusvane < 0 || prekusvane > 1);
		if(prekusvane == 1) break;
	}
}
void print_one(Order& current_order){
	Date& data = current_order.date_accepted;
	cout << "Order " << current_order.order_id << endl;
	cout << "\tIme na Klient: " << current_order.client_name << endl;
	cout << "\tData: " << data.day << "/" << data.month << "/" << data.year << endl;
	cout << "\tUstroistvo: " << device_types[current_order.device_type] << endl;
	cout << "\tSerien nomer na ustroistvoto: " << current_order.serial_number << endl;
	cout << "\tProblem spored klienta ( do 50 simvola ): " << current_order.device_problem << endl;
	cout << "\tStatus na poruchkata: " << status_str[current_order.current_status] << endl;
	if(current_order.current_status == Remontiran){
		cout << "\tIme na tehnik izvurshil remonta: " << current_order.tehnician_name << endl;
		cout << "\tIzvurshen remont: " << current_order.repair << endl;
		cout << "\tCena: " << current_order.price << endl;
		cout << "\tDni prestoy v serviza: " << current_order.days_in_shop << endl;
	}
}
void print_all(ComputerShop& ardes){
	system("cls");
	if(ardes.order_counter == 0)
		cout << "Nqma ustroistva za pokazvane" << endl;
	for(int i = 0; i < ardes.order_counter; i++){
		print_one(ardes.orders[i]);
	}
	system("pause");
}
void menu_correction(ComputerShop& ardes){
	int choice;
	do{
		system("cls");
		cout << "Menu korekciq" << endl;
		cout << "1. Korekciq na poruchka" << endl;
		cout << "2. Otkaz na poruchka" << endl;
		cout << "3. Obratno kum glavnoto menu" << endl;
		do{
			cout << "Vuvedi izbor: ";
			cin >> choice;
		}while(choice < 1 || choice > 3);
		switch(choice){
			case 1:
				correct_order(ardes);
				break;
			case 2:
				stop_order(ardes);
				break;
		}
	}while(choice != 3);
}
void correct_order(ComputerShop& ardes){
	system("cls");
	if(ardes.order_counter == 0){
		cout << "Nqma poruchki za redaktirane" << endl;
		system("pause");
		return;
	}
	bool temp_bool = false;
	int temp_int;
	string temp_string;
	char temp_cstring[50];
	cout << "Vuvedi nomer na poruchka za korekciq: ";
	cin >> temp_int;
	for(int i = 0; i < ardes.order_counter; i++) 
		if(ardes.orders[i].order_id == temp_int){
			temp_bool = true;
			temp_int = i;
			break;
		}
	if(temp_bool == false){
		cout << "Order s nomer \"" << temp_int << "\" ne beshe namerena" << endl;
		system("pause");
		return;
	}
	Order& chosen_order = ardes.orders[temp_int];
	cout << "Redakciq ( Za da propusnete promqna na suotveten zapis vuvedete -1 ): " << endl;
	
	cout << left << setw(25) << "Staro ime na klient: " << chosen_order.client_name << endl;
	cout << left << setw(25) << "Novo ime na klient: ";
	cin >> ws;
	getline(cin, temp_string);
	if(temp_string != "-1") chosen_order.client_name = temp_string;
	
	cout << left << setw(22) << "Staro ustroistvo: " << device_types[chosen_order.device_type] << endl;
	do{
		temp_bool = true;
		cout << left << setw(22) << "Novo ustroistvo: ";
		cin >> ws;
		cin >> temp_string;
		if(temp_string == "-1") temp_bool = false;
		for(int i = 0; i < 5; ++i)
			if(device_types[i] == temp_string){
				chosen_order.device_type = i;
				temp_bool = false;
			}
	}while(temp_bool == true);
	
	cout << left << setw(39) <<  "Star serien nomer na ustroistvoto: " << chosen_order.serial_number << endl;
	cout << left << setw(39) << "Nov serien nomer na ustroistvoto: ";
	cin >> ws;
	getline(cin, temp_string);
	if(temp_string != "-1") chosen_order.serial_number = temp_string;
	
	cout << left << setw(34) << "Star problem na ustroistvoto: " << chosen_order.device_problem << endl;
	cout << left << setw(34) << "Nov problem na ustroistvoto: ";
	cin >> ws;
	cin.getline(temp_cstring, 50, '\n');
	if(strcmp(temp_cstring, "-1")) strcpy(chosen_order.device_problem, temp_cstring);
	save_all_text_file(ardes); // Pri redakciq zapazi vsichko nanovo
	system("pause");
}
void stop_order(ComputerShop& ardes){
	system("cls");
	if(ardes.order_counter == 0){
		cout << "Nqma poruchki za otkazvane" << endl;
		system("pause");
		return;
	}
	bool temp_bool = false;
	int temp_int;
	cout << "Vuvedi nomer na poruchka za otkaz: ";
	cin >> temp_int;
	for(int i = 0; i < ardes.order_counter; i++) 
		if(ardes.orders[i].order_id == temp_int){
			temp_bool = true;
			temp_int = i;
			break;
		}
	if(temp_bool == false){
		cout << "Order s nomer \"" << temp_int << "\" ne beshe namerena" << endl;
		system("pause");
		return;
	}
	Order& chosen_order = ardes.orders[temp_int];
	if(chosen_order.current_status == Prieta){
		chosen_order.current_status = Otkazana;
		cout << "Order " << chosen_order.order_id << " beshe otkazana uspeshno." << endl;
		cout << chosen_order.client_name << " e taksuvan s 10 leva." << endl;
		save_all_text_file(ardes); // Pri otkaz zapazi vsichko nanovo
	}
	else if(chosen_order.current_status == Otkazana){
		cout << "Orderta veche e bila otkazana." << endl;
	}
	else{
		cout << "Ne moje da se otkaje veche izvurshena poruchka. Ustroistvoto e remontirano!" << endl;
	}
	system("pause");
}
void service_order(ComputerShop& ardes){
	system("cls");
	if(ardes.order_counter == 0){
		cout << "Nqma poruchki za obslujvane" << endl;
		system("pause");
		return;
	}
	int found_index = -1;
	bool temp_bool;
	string temp_string;
	cout << "Obslujvane na poruchka: " << endl;
	cout << "Serien nomer na ustroistvoto: ";
	cin >> temp_string;
	for(int i = 0; i < ardes.order_counter; i++){
		if(temp_string == ardes.orders[i].serial_number){
			found_index = i;
			break;
		}
	}
	if(found_index == -1){
		cout << "Ustrostvo sus serien nomer \"" << temp_string << "\" ne beshe namereno." << endl;
		system("pause");
		return;
	}
	Order& service_order_poruchka = ardes.orders[found_index];
	print_one(service_order_poruchka);
	cout << endl;
	cout << "Ime na tehnik obslujvasht ustroistvoto: ";
	cin >> ws;
	getline(cin, service_order_poruchka.tehnician_name);
	cout << "Izvurshen remont: ";
	cin >> ws;
	cin.getline(service_order_poruchka.repair, 50);
	cout << "Cena: ";
	cin >> service_order_poruchka.price;
	do{
		temp_bool = true;
		cout << "Status(Odobrena, Otkazana ili Remontiran): ";
		cin >> temp_string;
		for(int i = 0; i < 3; i++){
			if(temp_string == status_str[i]){
				service_order_poruchka.current_status = (status)i;
				temp_bool = false;
				break;
			}
		}
	}while(temp_bool == true);
	save_all_text_file(ardes); // Pri service_order zapazi vsichko nanovo
	system("pause");
}
void odit_menu(ComputerShop& ardes){
	if(ardes.order_counter == 0){
		system("cls");
		cout << "Nqma poruchki za Odit" << endl;
		system("pause");
		return;
	}
	int izbor;
	do{
		system("cls");
		cout << "Odit Menu" << endl;
		cout << "1. Izvjedane na vsichki servizni poruchki za daden mesec, sortirani po serien nomer" << endl;
		cout << "2. Filtrirane po tip ustroistvo, koito sa bili remontirani, sortirani po data nizhodqshto" << endl;
		cout << "3. Vsichki poruchki na klient" << endl;
		cout << "4. Obratno kum glavnoto menu" << endl;
		do{
			cout << "Vuvedi izbor: ";
			cin >> izbor;
		}while(izbor < 1 || izbor > 4);
		switch(izbor){
			case 1:
				sort_by_serial_number(ardes);
				break;
			case 2:
				filter_by_type(ardes);
				break;
			case 3:
				filter_by_name(ardes);
				break;
		}
	}while(izbor != 4);
}
void sort_by_serial_number(ComputerShop& ardes){
	system("cls");
	Order* sorted_orders[100];
	int orders_counter = 0;
	int mesec;
	cout << "Vuvedi mesec: ";
	cin >> mesec;
	for(int i = 0; i < ardes.order_counter; i++){
		if(ardes.orders[i].date_accepted.month == mesec){
			sorted_orders[orders_counter] = &ardes.orders[i];
			orders_counter++;
		}
	}
	
	for(int i = 0; i < orders_counter - 1; i++)
		for(int j = 0; j < orders_counter - i - 1; j++)
			if(sorted_orders[j]->serial_number > sorted_orders[j + 1]->serial_number) 
				swap(sorted_orders[j], sorted_orders[j + 1]);
	for(int i = 0; i < orders_counter; i++){
		print_one(*sorted_orders[i]);
	}
	system("pause");
}
void filter_by_type(ComputerShop& ardes){
	system("cls");
	Order* choosen_type[100];
	int order_counter = 0;
	bool temp_bool = true;
	int tip;
	string tip_str;
	do{
		cout << "Tip na ustroistvoto: ";
		cin >> tip_str;
		for(int i = 0; i < 5; i++)
			if(tip_str == device_types[i]){
				tip = i;
				temp_bool = false;
				break;
			}
	}while(temp_bool == true);
	for(int i = 0; i < ardes.order_counter; i++){
		Order& iteraciq = ardes.orders[i];
		if(iteraciq.device_type == tip && iteraciq.current_status == Remontiran){
			choosen_type[order_counter] = &iteraciq;
			order_counter++;
		}
	}
	// SORTITANE PO DATA
	for(int i = 0; i < order_counter; i++){
		print_one(*choosen_type[i]);
	}
	system("pause");
}
void filter_by_name(ComputerShop& ardes){
	system("cls");
	Order* sorted_orders[100];
	int order_counter = 0;
	string client_name;
	cout << "Vuvedi ime: ";
	getline(cin >> ws, client_name);
	for(int i = 0; i < ardes.order_counter; i++){
		if(ardes.orders[i].client_name == client_name){
			sorted_orders[order_counter] = &ardes.orders[i];
			order_counter++;
		}
	}
	for(int i = 0; i < order_counter - 1; i++)
		for(int j = 0; j < order_counter - i - 1; j++)
			if(sorted_orders[j]->serial_number > sorted_orders[j + 1]->serial_number) 
				swap(sorted_orders[j], sorted_orders[j + 1]);
	for(int i = 0; i < order_counter; i++){
		print_one(*sorted_orders[i]);
	}
	system("pause");
}
void read_from_text_file(ComputerShop& ardes){
	ifstream fin("tekst.txt");
	if(!fin.is_open()) return;
	while(!fin.eof()){
		Order& new_order = ardes.orders[ardes.order_counter];
		fin >> new_order.order_id;
		fin >> new_order.date_accepted.day;
		fin >> new_order.date_accepted.month;
		fin >> new_order.date_accepted.year;
			
		getline(fin >> ws, new_order.client_name);
		
		fin >> new_order.device_type;
		fin >> new_order.serial_number;
		fin.ignore(1000,'\n');
		fin.getline(new_order.device_problem, 50);
		getline(fin, new_order.tehnician_name);
		fin.getline(new_order.repair, 50);
		
		fin >> new_order.price;
		fin >> new_order.days_in_shop;
		fin >> new_order.current_status;
		if(!fin) break;
		ardes.order_counter++;
	}
	fin.close();
}
void append_to_text_file(Order& new_order){
	ofstream fout("tekst.txt", ios::app);
	fout << new_order.order_id << '\n';
	fout << new_order.date_accepted.day << '\n';
	fout << new_order.date_accepted.month << '\n';
	fout << new_order.date_accepted.year << '\n';
	fout << new_order.client_name << '\n';
	fout << new_order.device_type << '\n';
	fout << new_order.serial_number << '\n';
	fout << new_order.device_problem << '\n';
	fout << new_order.tehnician_name << '\n';
	fout << new_order.repair << '\n';
	fout << new_order.price << '\n';
	fout << new_order.days_in_shop << '\n';
	fout << new_order.current_status << '\n';
	fout.close();
}
void save_all_text_file(ComputerShop& ardes){
	ofstream fout("tekst.txt"); // Otvarqme i zatvarqme faila za da go iztriem
	fout.close();
	for(int i = 0; i < ardes.order_counter; i++)
		append_to_text_file(ardes.orders[i]);
}
bool izhod(){
	system("cls");
	int izbor;
	cout << "Iskate da izlezete ot programata?" << endl;
	cout << "1. Da" << endl;
	cout << "2. Ne" << endl;
	do{
		cout << "Vuvedi izbor: ";
		cin >> izbor;
	}while(izbor < 1 || izbor > 2);
	if(izbor == 1) return true;
	return false;
}
