//Neusa Antonia Romao Caxicane/dni-y3080401w
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <string.h>
#include <stdlib.h>
#include<sstream>

using namespace std;
const int numPeople=100;
const int LowPeople=50;
const int MIN = 0;


struct Base {
   string name;
   int people;
   int equipment;
   double x,y;
};

struct Ship {
   string name;
   int maxPeople;
   int maxEquipment;
   int curPeople;
   int curEquipment;
   vector<Base> bases;
};

struct Planet {
  string name;
  vector<Base> bases;
  vector<Ship> ships;
};

// -----------------------------------------------------
const int MAXNAME=15;
struct BinBase {
  char name[MAXNAME];
  int people;
  int equipment;
  double x,y;
};

struct BinShip {
  char name[MAXNAME];
  int maxPeople;
  int maxEquipment;
};

struct BinPlanet {
  char name[MAXNAME];
  unsigned int nbases;
  unsigned int nships;
};


// ---------------- error -------------------------

enum Error {
  ERR_UNKNOWN_OPTION, 
  ERR_WRONG_NUMBER, 
  ERR_LOW_PEOPLE, 
  ERR_WRONG_BASE_NAME, 
  ERR_WRONG_SHIP_NAME,
  ERR_NO_BASES,
  ERR_NO_SHIPS,
  ERR_CANT_OPEN_FILE,
  ERR_ARGS
}; 

void error(Error n)
{
  switch (n) {
   
    case ERR_UNKNOWN_OPTION:
      cout << "Error, unknown option" << endl;
      break;

    case ERR_WRONG_NUMBER:
      cout << "Error, wrong number, must be positive" << endl;
      break;

    case ERR_LOW_PEOPLE:
      cout << "Error, low people number" << endl;
      break;

    case ERR_WRONG_BASE_NAME:
      cout << "Error, base name not found" << endl;
      break;

    case ERR_WRONG_SHIP_NAME:
      cout << "Error, wrong ship name" << endl;
      break;

    case ERR_NO_BASES:
      cout << "Error, there are no bases in the planet" << endl;
      break;

    case ERR_NO_SHIPS:
      cout << "Error, there are no ships in the planet" << endl;
      break;

    case ERR_CANT_OPEN_FILE:
      cout << "Error, can't open file" << endl;
      break;

    case ERR_ARGS:
      cout << "Error, wrong arguments" << endl
           << "Usage: evacuationOfHoth [-b filename] [-s filename] [-l filename]" << endl;
      break;
  }
}

// ------------------------------------------------------
void menu()
{
  cout << "-----========== Evacuation ==========-----" << endl
       << "1- List info" << endl
       << "2- Add/modify base" << endl
       << "3- Add ship" << endl
       << "4- Delete base" << endl
       << "5- Delete ship" << endl
       << "6- Evacuation plan" << endl
       << "7- Import bases" << endl
       << "8- Import ships" << endl
       << "9- Save data" << endl
       << "0- Load data" << endl
       << "q- Quit" << endl
       << "Option: " ;
}


// ------------------------------------------------------
bool processArguments(int argc,char *argv[],Planet &planet)
{
return true;
}
// ------------------------------------------------------------------
void printShip(const Ship &ship)//prints ship info
{
	cout <<"["<<"("<< ship.name <<")"<<" "<<ship.maxPeople <<"{"<<ship.curPeople<< "}" <<" "<<ship.maxEquipment <<"{"<<ship.curEquipment <<"}" <<"]";
  cout <<endl;
}

//----------------function to print base info---------
void printBase(const Base &base){
  
  cout<<"["<<"("<< base.name <<")"<<" "<<base.people <<" "<<base.equipment<< " ("<<base.x<<"," <<base.y <<")" <<"]" ;
  cout <<endl;
  }
//------Function to modify a base--------------
void modifyBase(Planet &planet, Base &base, int pos){
  
  char choice1, choice2;//variable to store the user option about modifying or not the base details
  cout <<"Modify base data (Y/N)? ";
  cin>>choice1;
  cin.get();
  if(choice1== 'Y'){
      cout<<"Which base data (p/e/c)? ";
      cin>>choice2;
      cin.get();
  switch(choice2){
    case 'p': cout <<"Enter base people: ";
              cin>>planet.bases[pos].people;
              cin.get();
    if(base.people <=MIN){
      error(ERR_WRONG_NUMBER);
    }
    else if(base.people < LowPeople){
           error(ERR_LOW_PEOPLE);
    };
    break;
    case 'e': cout <<"Enter base equipment: ";
              cin>>planet.bases[pos].equipment;
              cin.get();
    if(base.equipment <=MIN){
        error(ERR_WRONG_NUMBER);
    };
    break;
    case 'c':cout <<"Enter base coordinates: ";
             cin>>base.x;
             cin.get();
             cout <<"Enter base coordinates: ";
             cin>>planet.bases[pos].y;
             cin.get();
     break;
     default: error(ERR_UNKNOWN_OPTION);
     break;
    } 
  }
} 

//----------------------------Creates/modifies a base
void createBase(Planet &planet)
{
  string base1;//base name enter by user
  bool found=false;
  unsigned int i;
  Base base;

  cout << "Enter base name: ";
  getline(cin, base1);
  for(i=0; i<planet.bases.size()&& !found; i++){
    if(planet.bases[i].name==base1){
    found=true;
    base=planet.bases[i];
    printBase(base);
    modifyBase(planet, base, i);
    return;
    }
  }
  if(!found){
  base.name = base1;
  cout <<"Enter base people: ";
  cin>>base.people;
  cin.get();
    if(base.people <=MIN){
      error(ERR_WRONG_NUMBER);
      return;
    }else if(base.people < LowPeople){
      error(ERR_LOW_PEOPLE);
      return;
    }else
      cout<< "Enter base equipment (Kg): ";
      cin>>base.equipment;
      cin.get();
        if(base.equipment<=MIN){
          error(ERR_WRONG_NUMBER);
          return;
        }else
        cout <<"Enter base coordinate x: ";
        cin>>base.x;
        cin.get();
        cout <<"Enter base coordinate y: ";
        cin>>base.y;
        cin.get();
     planet.bases.push_back(base);
  }
}

//-----------Creates a ship---------------
void createShip(Planet &planet)
{
  unsigned int i;
  bool found =false;
  string usership;//user imput name of the ship
  Base base;
  Ship ship;

  cout <<"Enter ship name: ";
  getline(cin, usership);
  for(i = 0; i<planet.ships.size()&&!found; i++){
    if(planet.ships[i].name==usership){
      found=true;
      error(ERR_WRONG_SHIP_NAME);
      ship=planet.ships[i];
      printShip(planet.ships[i]);
    }
  }
  if(!found){
    ship.name = usership;
    cout <<"Enter ship maximum people: ";
    cin>>ship.maxPeople;
    cin.get();
   
    if(ship.maxPeople <=MIN){
      error(ERR_WRONG_NUMBER);
      return;
    }
    else if(ship.maxPeople <LowPeople){
      error(ERR_LOW_PEOPLE);
      return;
    }
    else{
      cout <<"Enter ship maximum equipment: ";
       cin>>ship.maxEquipment;
       cin.get();
      if(ship.maxEquipment < MIN){
        error(ERR_WRONG_NUMBER);
       return;
        }
    }
    ship.curPeople =0;
    ship.curEquipment=0;
    planet.ships.push_back(ship);
  }
}

void deleteBase(Planet &planet)
{
  string userbase;//name of the base enter by the user
  char opt; 
  unsigned int i;
  Base base;

  //verify if the vector base is empty
  if(planet.bases.empty()){
        error(ERR_NO_BASES);
  }
    //if is not empty ask the name of the base and search in vector
  else{
      cout <<" Enter Name: ";
       getline(cin,userbase);

      for(i =0; i<planet.bases.size(); i++){
        if(planet.bases[i].name == userbase){
          base=planet.bases[i];
          printBase(planet.bases[i]);
          cout <<"Delete (Y/N)? ";
          cin>>opt;
          cin.get();
          if(opt=='Y')
         planet.bases.erase(planet.bases.begin()+i);//delete the base
        }else
         error(ERR_WRONG_BASE_NAME);
      }  
    }
}

void deleteShip(Planet &planet)
{
  Ship ship;
  string usership;//name of the ship enter by the user
  char opt; //to store answer to delete or not
  unsigned int i;
  
  //verify if the vector ship is empty
  if(planet.ships.empty()){
     error(ERR_NO_SHIPS);
  }
 //if is not empty ask the name of the ship and search in vector
  else{
    cout <<"Enter Name: ";
      getline(cin, usership);

      for(i = 0; i<planet.ships.size(); i++){
        if(planet.ships[i].name == usership){
           ship=planet.ships[i];
           printShip(planet.ships[i]);
          cout <<"Delete (Y/N)? ";
          cin>>opt;
          cin.get();
          if(opt=='Y')
          planet.ships.erase(planet.ships.begin()+i);//delete the ship
         }else 
          error(ERR_WRONG_SHIP_NAME);
      }  
    }  
}
//---------------------print functions-----------------------------------
void printPlanet(const Planet &planet){//prints planet info
  Ship ship;
  Base base;

  cout << "Planet: " << planet.name << endl;
  cout << "Ships:"<< endl;
  for (unsigned int i = 0; i < planet.ships.size(); i++)
  {
    printShip(planet.ships[i]);
    for(unsigned int j = 0; j < planet.ships[i].bases.size(); j++)
    {
    printBase(planet.ships[i].bases[j]);
    }
  }
  cout <<"Bases: " << endl;
  for (unsigned int j = 0; j < planet.bases.size(); j++){
    printBase(planet.bases[j]);
  } cout <<"\n";
  
}
//--------------to check if base is assign to a ship or not-------------------------------
bool AsignBase(Planet &planet, Base &base){
  
  bool found = false;
  for(unsigned int i=0; i< planet.ships.size() && !found; i++){
    for(unsigned int j=0; j< planet.ships[i].bases.size() && !found; j++)
    if(planet.ships[i].bases[j].name == base.name){
      found =true;
    }
  }
  return found;
}

//Auxiliar function to find the centroid and the distance between bases
int Proximity(Planet &planet, Ship &ship){
 
  int Xc, Yc; //centroid coordinates
  int minDistance=9999999;
  long int distance =0;

  int position =-1;//Position of the closest base
   int n;//to store the vector capacity result
  bool encontrado = false;
  unsigned int j;
  bool asignbase =false;
  bool peopleSpace = false;
  bool Equipspace = false;


  for(j=0; j< planet.bases.size() && !encontrado; j++){
     n = planet.bases.capacity();
    Xc +=(planet.bases[j].x)/n;
    Yc +=(planet.bases[j].y)/n;
  }
  for(j=0; j < planet.bases.size(); j++){
    asignbase =AsignBase(planet, planet.bases[j]);//check if base not asigned
    peopleSpace =  planet.bases[j].people <= ship.maxPeople - ship.curPeople;
    Equipspace = planet.bases[j].equipment <= ship.maxEquipment;//comparing if base fits in the ship
    if(!asignbase && peopleSpace && Equipspace){ 
       distance = sqrt(pow(planet.bases[j].x - Xc, 2) + pow(planet.bases[j].y - Yc, 2));
       if(distance < minDistance){
         position = j;
         minDistance = distance;
        }
    } 
  }
  return position;
}

// auxiliar function to finish evacuation plan and return bases int the planet
void FinishPlan(Planet &planet){
  unsigned int i, j;

  for(i=0;i< planet.ships.size(); i++){
    for(j=0; j<planet.ships[i].bases.size(); j++){
      planet.bases.push_back(planet.ships[i].bases[j]);//this return base to planet vector
      planet.ships[i].bases.erase(planet.ships[i].bases.begin()+j);
    }
      planet.ships[i].curPeople =0;
      planet.ships[i].curEquipment = 0;
  
  }
}
//------------Modules to write base and ship in a text file-------------------------
void writeBase(const Base base, ofstream &fich)
{
  fich << "["
       << "(" << base.name << " ) "
       << " " << base.people << " " << base.equipment << "(" << base.x << "," << base.y << ")"
       << "]";
  fich << endl;
}
//module to write ship info in a new text file---------------
void writeShip(const Ship ship, ofstream &fich)
{
  fich << "["
       << "(" << ship.name << ") "
       << " " << ship.maxPeople << "{" << ship.curPeople << "}"
       << " " << ship.maxEquipment << "{" << ship.curEquipment << "}";
  fich << endl;
}
//----------module to write planet info in a new text file-------------------
void writePlanet(const Planet &planet, ofstream &fich) // prints planet info
{
  Ship ship;
  Base base;
  fich << "Planet:" << planet.name << endl;
  fich << "Ships:" << endl;
  for (unsigned int i = 0; i < planet.ships.size(); i++)
  {
   writeShip(planet.ships[i], fich);
    for (unsigned int j = 0; j < planet.ships[i].bases.size(); j++)
    {
      writeBase(planet.ships[i].bases[j], fich);
    }
  }
  fich << "Bases :" << endl;
  for (unsigned int k = 0; k < planet.bases.size(); k++)
  {
    writeBase(planet.bases[k], fich);
  }
}
//---------function to save evacuation plan-----------------------------------------
void ExtensionofEvacutionplan(Planet planet)
{
  string userfile;
 
  cout << "Enter filename: ";
  cin >> userfile;
  ofstream Fichero;//file to store planet
  Fichero.open(userfile.c_str());
  if (Fichero.is_open())
  {
    writePlanet(planet, Fichero);
    Fichero.close();
  }
  else
    error(ERR_CANT_OPEN_FILE);
}
//-------Evacuation Plan-----------------------------------------------------------------------
void evacuationPlan(Planet &planet)
{
  unsigned int i, j;
  Ship ship;
  Base base;
  char answer;

  bool baseFound = false;
  int position=-1;
  int Bposition=0;
  bool asignbase =false;//to store the return if a base is asigned or not
  bool peopleSpace =false;//to verify people space in a base
  bool Equipspace=false;//to verify  equipment in a base
  int maxPeopleShip = 0;//to very space for people in a ship
  int maxPeopleBase = 0;//to very space for people in a ship
  
  if(!planet.ships.empty()){
    do{
      baseFound =false;
    maxPeopleShip=0;
    baseFound = false;
    position=-1;
    Bposition=0;
    asignbase =false;
    peopleSpace =false;
    Equipspace=false;
    maxPeopleShip = 0;
    maxPeopleBase = 0;

      for(i=0; i< planet.ships.size(); i++){
        if(planet.ships[i].maxPeople > maxPeopleShip  && planet.ships[i].bases.empty()){
          position =i;
          maxPeopleShip = planet.ships[i].maxPeople;
        }
  
      }
      if(position>-1){
        cout << "Chosen ship: " ;
        printShip(planet.ships[position]);
  //Select available bases to be evacuated
        for(j=0; j < planet.bases.size(); j++){
          asignbase= AsignBase(planet, planet.bases[j]);//check if base not asigned
          peopleSpace =  planet.bases[j].people <= planet.ships[position].maxPeople - planet.ships[position].curPeople;
          Equipspace = planet.bases[j].equipment <= planet.ships[position].maxEquipment-planet.ships[position].curEquipment;//comparing if base fits in the ship
          if(!asignbase && peopleSpace && Equipspace){ //selecting the biggest base with maxpeople in planet
            if(planet.bases[j].people > maxPeopleBase){
              Bposition =j;//select the biggest base
              baseFound = true;
              maxPeopleBase = planet.bases[j].people;
            }
          } 
          //printBase(planet.bases[j]);//print base selected
        } 
        if(baseFound){
          do{
            //printBase(planet.bases[Bposition]);
            planet.ships[position].bases.push_back(planet.bases[Bposition]);//add base in vector of ships
            planet.ships[position].curPeople += planet.bases[Bposition].people;//updating curpeople with number of people in the base
            planet.ships[position].curEquipment += planet.bases[Bposition].equipment;//update equipment
            planet.bases.erase(planet.bases.begin()+ Bposition);//erase base from planet vector
            Bposition=Proximity(planet, planet.ships[position]);
          }while(Bposition!= -1);
        }
        printPlanet(planet);
      } 
    }while(baseFound == true);
  } 
 cout << "Save evacuation plan (Y/N)? " <<endl;
  cin >> answer;
  if(answer == 'Y'){
    ExtensionofEvacutionplan(planet);
  }
  FinishPlan(planet); //return all bases to planet and delete from ship vector
  
}
//-----Option 7 import bases------------
void ImportBases(Planet &planet)
{
  string userfile;
  string linea;
  string people;
  string cordx;
  string cordy= "";
  int i = 0;
  string equipment;

  ifstream Bases;
  Base base;

  cout << "Enter filename: ";
  cin >> userfile;
  Bases.open(userfile.c_str());
  if (Bases.is_open())
  {
    while (getline(Bases, linea))
    {
       i = 0;
      base.name = "";
   //Jump initial spaces
      while (linea[i] == ' ' || linea[i] == '"')
      {
        i++;
      }
      //read base name
      while (linea[i] != '"')
      {
        base.name += linea[i];
        i++;
      }
      cout << base.name << endl;
      //jump comma and spaces between people
      while (linea[i] == '"' || linea[i] == ' ' || linea[i] == ',')
      {
        i++;
      }
      //extract people number
      people = "";
      while(linea[i]!= ':')
      {
        people += linea[i];
        i++;
      }
      base.people = atoi(people.c_str());

      cout << base.people << endl;

      while (linea[i] == ' ' || linea[i] == ':')
      {
        i++;
      }
      equipment = "";
      while (linea[i]!= ',' && linea[i] != ' ')
      {
        equipment += linea[i];
        i++;
      }
      base.equipment = atoi(equipment.c_str());
      cout << base.equipment << endl;
      i++;

      while(linea[i] == ' '|| linea[i]== ',')
      {
        i++;
      }
      while(linea[i] == '(')
      { 
        i++;
      }
      cordx = "";
      while(linea[i] != ',' && linea[i]!=' '){
        cordx += linea[i];
        i++;
      }
      base.x = atof(cordx.c_str());
      cout << base.x << endl;
      i++;
      }
      while(linea[i]!= ')'){
        cordy += linea[i];
        i++;
      }
      base.y = atof(cordy.c_str());
      cout << base.y <<endl;
      planet.bases.push_back(base);
      Bases.close();
  }
  else
    error(ERR_CANT_OPEN_FILE);
}

//------------Module to import a ship------------------------------------------------------
void Importship(Planet &planet){
  
  string userfile;
  string line;
  string mpeople;
  string mequipment;
  string cpeople;
  string cequipment;
  string sname, sname1;
  ifstream ships;
  Ship ship;
  int i;

  cout << "Enter filename: ";
  cin >> userfile;
  ships.open(userfile.c_str());
  if(ships.is_open()){
 
    do{
      while(getline(ships, line))
      {
          i = 0;
          ship.maxPeople= 0;
      //Jump initial spaces
          while(line[i] == '(')
          {
            i++;
          }
          //read base people
          while(line[i] != ',')
          {
            mpeople += line[i];
            i++;
          }
        ship.maxPeople = atoi(mpeople.c_str());
          cout << ship.maxPeople<< endl;
          i++;
          while(line[i] != ')')
          {
            mequipment += line[i];
            i++;
          }
          ship.maxEquipment=atoi(mequipment.c_str());
          cout <<ship.maxEquipment <<endl;
          i++;
          while(line[i]== ' ' || line[i]== '"'){
            i++;
          }
          while(line[i]!= '"'){
            sname1 +=line[i];
            i++;
          }
          while(line[i] == ' ' || line[i] == '"'){
            i++;
          }
          while(line[i]!= '"'){
            sname +=line[i]; 
            i++;
          }
        //concatenating the name
        string space = " ";
        ship.name += sname1 + space + sname;
        cout << ship.name <<endl;
        ships.close();
      }
      planet.ships.push_back(ship);
    }while(!ships.eof()); 
  
  }else
    error(ERR_CANT_OPEN_FILE);
}

//------------------------------------------------------
int main(int argc,char *argv[])
{
   Planet planet;
   planet.name = "Hoth";
   char option;

   if (processArguments(argc,argv,planet))
     do {
        menu();
        cin >> option; cin.get();
        
        switch (option) { 
          case '1': {
            printPlanet(planet);
            break;
          }
          case '2': { 
            createBase(planet);
            break;
          }
          case '3': {
            createShip(planet);
            break;
          }
          case '4': {
            deleteBase(planet);
            break;
          }
          case '5': {
            deleteShip(planet);
            break;
          }
          case '6': {
            evacuationPlan(planet);
            break;
          }
          case '7': {
            ImportBases(planet);
            break;
          }
          case '8': {
            Importship(planet);
            break;
          }
          case '9': {
            break;
          }
          case '0': {
            break;
          }
          case 'q': {
            break;
          }
          default:  {
            error(ERR_UNKNOWN_OPTION); 
            break;
          }
        }
     } while (option != 'q');
   
   return 0;
}

