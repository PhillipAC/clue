#include<iostream.h>
#include<iomanip.h>
#include<vector>
#include<time.h>
using namespace std;

void personD(int input);
void locationD(int input);
void weaponD(int input);
int randomNum(int HIGH, int LOW);

class Card
{
public:
   Card(int id, int type, int name, int used);
   void Setup(int id, int type, int name, int used);
   void write();
   int check();
   int c_used;
   int c_id;
   int c_type;
   int c_name;
private:
};

Card::Card(int id, int type, int name, int used):
               c_id(id),
               c_type(type),
               c_name(name),
               c_used(used)
{}

void Card::Setup(int id, int type, int name, int used)
{
   c_id = id;
   c_type = type;
   c_name = name;
   c_used = used;
}

void Card::write()
{
     //cout << "type: " << c_type << "\nName: " << c_name << "\nId: " << c_id;
     switch(c_type){
          case 0:
               personD(c_name);
               break;
          case 1:
               locationD(c_name);
               break;
          case 2:
               weaponD(c_name);
               break;
     }
}

int Card::check()
{
     if (c_used == 0)
        return 0;
     else
         return 1;
}

class Answer
{
public:
      Answer(Card person, Card location, Card weapon);
      void choiceperson(Card person);
      void choicelocation(Card location);
      void choiceweapon(Card weapon);
      void write();
private:
        Card a_person;
        Card a_location;
        Card a_weapon;
};

Answer::Answer(Card person, Card location, Card weapon):
                    a_person(person),
                    a_location(location),
                    a_weapon(weapon)
{}

void Answer::choiceperson(Card person){a_person = person;};
void Answer::choicelocation(Card location){a_location = location;};
void Answer::choiceweapon(Card weapon){a_weapon = weapon;};

void Answer::write()
{
     cout << "It was ";
     a_person.write();
     cout << " in the ";
     a_location.write();
     cout << " with the ";
     a_weapon.write();
     cout << "!";
 }
 
class Hand
{
public:
   void add(Card picked);
   int accuse(int person, int location, int weapon);
   int accuseComputer(int person, int location, int weapon);
   void read();   
   int cardsinhand;
private:
   vector<Card> Hands;
};
void Hand::add(Card picked) {Hands.push_back(picked), cardsinhand++;};
int Hand::accuse(int person, int location, int weapon)
{
   int random = 0;
   int choice = 0;
   int personf = 0;
   int locationf = 0;
   int weaponf = 0;
   int info[3] = {0,0,0};
   for (int a = 0; a < cardsinhand; a++)
   {
       if (person == Hands[a].c_name && 0 == Hands[a].c_type){
          choice =1;
          info[0] = 1;}
       else if (location == Hands[a].c_name && 1 == Hands[a].c_type){
          choice =1;
          info[1] = 1;}
       else if (weapon == Hands[a].c_name && 2 == Hands[a].c_type){
          choice =1;
          info[2] = 1;}
   }
   if (choice == 1)
   {
       back:
       random = randomNum(2,0);
       switch(random)
       {
          case 0:
            if(info[0] == 1){
               cout << " it was not ";
               personD(person);
               cout << endl;
               return person;
            }
            break;
          case 1:
            if(info[1] == 1){
               cout << " it was not in the ";
               locationD(location);
               cout << endl;
               return location;
            }
            break;
          case 2:
            if(info[2] == 1){
               cout << " it was not with the ";
               weaponD(weapon);
               cout << endl;
               return weapon;
            }
            break;
       }
       goto back;
   }
   cout << " could not dispute it.\n";
   return 10;
}
int Hand::accuseComputer(int person, int location, int weapon)
{
   for (int a = 0; a < cardsinhand; a++)
   {
       if (person == Hands[a].c_name && 0 == Hands[a].c_type){
          return person;}
       else if (location == Hands[a].c_name && 1 == Hands[a].c_type){
          return location;}
       else if (weapon == Hands[a].c_name && 2 == Hands[a].c_type){
          return weapon;}
   }
   return 10;
}
void Hand::read()
{
     for (int a = 0; a < cardsinhand; a++)
     {
         cout << "\n::Card " << a + 1 << "\n";
         Hands[a].write();
     }
     
 }

int main()
{
    //Setting up the Game
    int id = 0;
    int namemax = 0;
    int selected = 0;
    int temp = 0;
    int person = 0;
    int place = 0;
    int weapon = 0;
    int output = 0;
    int round = 1;
    Card tempCard(0,0,0,0);
    Answer final(tempCard,tempCard,tempCard);
    vector<Card> cards;
    bool test = 0;
    Hand player1, player2, player3, you;
    for (int type = 0; type < 4; type++)
    {
        if (type == 0) {namemax = 6;}
        else if (type == 1) {namemax = 9;}
        else {namemax = 6;};
        for (int name = 0; name < namemax; name++)
        {
            tempCard.Setup(id, type, name,0);
            cards.push_back(tempCard);
            id++;
        }
    }
    cout << "Choosing the Murder... [Press Enter]";
    cin.ignore(1);
    selected = randomNum(5,0);
    final.choiceperson(cards[selected]);
    cards[selected].c_used = 1;
    cout << "Choosing the Murder... [Press Enter]";
    cin.ignore(1);
    selected = randomNum(14,6);
    final.choicelocation(cards[selected]);
    cards[selected].c_used = 1;
    cout << "Choosing the Weapon... [Press Enter]";
    cin.ignore(1);
    selected = randomNum(20,15);
    final.choiceweapon(cards[selected]);
    cards[selected].c_used = 1;
    
        player1.cardsinhand = 0;
    for (int a = 0; a < 4; a++)
    {
        do{
         selected = randomNum(20, 0);
         temp = cards[selected].check();
        }while (temp == 1);
        player1.add(cards[selected]);
        cards[selected].c_used = 1;        
        cout << "Card Found\n";
    }
        player2.cardsinhand = 0;
    for (int a = 0; a < 5; a++)
    {
        do{
         selected = randomNum(20, 0);
         temp = cards[selected].check();
        }while (temp == 1);
        player2.add(cards[selected]);
        cards[selected].c_used = 1;  
        cout << "Card Found\n";      
    }
        player3.cardsinhand = 0;
    for (int a = 0; a < 5; a++)
    {
        do{
         selected = randomNum(20, 0);
         temp = cards[selected].check();
        }while (temp == 1);;
        player3.add(cards[selected]);
        cards[selected].c_used = 1;  
        cout << "Card Found\n";      
    }
        you.cardsinhand = 0;
    for (int a = 0; a < 4; a++)
    {
        do{
         selected = randomNum(20, 0);
         temp = cards[selected].check();
        }while (temp == 1);
        you.add(cards[selected]);
        cards[selected].c_used = 1;  
        cout << "Card Found\n";      
    }
    cout << endl << "You have ";
    you.read();
    // TEST RIGHT HERE
    cout << "\n\nPlayer 1 had";
    player1.read();
    cout << "\n\nPlayer 2 had";
    player2.read();
    cout << "\n\nPlayer 3 had";
    player3.read();
    cout << "\n\nWhat really happened was:\n";
    final.write();
    cin.ignore(2);
    // TEST RIGHT HERE
    cout << endl << endl;
    
    while (person != 20 || place != 20 || weapon != 20)
    {
          cout << "Round: " << round << endl << "When done type 20 for any of them\n";
          cout << "Who did it?\n0) Miss Scarlet\n1) Colonel Mustard\n2) Mrs. White\n3) Mr. Green\n4) Mrs. Peacock\n5) Professor Plum\nInput: ";
          cin >> person; 
          cout << "Where was it done?\n0) Kitchen\n1) Ballroom\n2) Conservatory\n3) Billiard Room\n4) Library\n5) Study\n6) Hall\n7) Lounge\n8) Dining Room\nInput: ";
          cin >> place;
          cout << "With what was it done?\n0) Candlestick\n1) Knife\n2) Lead Pipe\n3) Revolver\n4) Rope\n5) Wrench\nInput: ";
          cin >> weapon;
          if (person != 20 || place != 20 || weapon != 20){
              cout << "Player 1 says";
              output = player1.accuse(person, place, weapon);
              if (output == 10){
                 cout << "Player 2 says";
                 output = player2.accuse(person, place, weapon);}
              if (output == 10){
                 cout << "Player 3 says";
                 output = player3.accuse(person, place, weapon);}
              cin.ignore(1);
              //Player 1 Goes
              person = randomNum(5,0);
              place = randomNum(8,0);
              weapon = randomNum(5,0);
              cin.ignore(1);
              cout << "Player 1: \"It was ";
              personD(person);
              cout << " in the ";
              locationD(place);
              cout << " with the ";
              weaponD(weapon); 
              cout << "\"\n";
              cin.ignore(1);
              output = player2.accuseComputer(person, place, weapon);
              if (output != 10)
                 {cout << "Player 2 can dispute it\n";
                  goto nextround0;}
              else if (output == 10){
                 cout << "Player 2 can not dispute it\n";
                 output = player3.accuseComputer(person, place, weapon);}
              if (output != 10)
                 {cout << "Player 3 can dispute it\n";
                  goto nextround0;}
              else if (output == 10){
                 cout << "Player 3 can not dispute it\n";
                 output = you.accuseComputer(person, place, weapon);}
              if (output != 10){
                 cout << "You can dispute it\n";
                  goto nextround0;}
              else if (output == 10){
                 cout << "You can not dispute it\n";}  
              nextround0: 
              cin.ignore(1);
              //Player 2 Goes
              person = randomNum(5,0);
              place = randomNum(8,0);
              weapon = randomNum(5,0);
              cin.ignore(1);
              cout << "Player 2: \"It was ";
              personD(person);
              cout << " in the ";
              locationD(place);
              cout << " with the ";
              weaponD(weapon); 
              cout << "\"\n";
              cin.ignore(1);
              output = player3.accuseComputer(person, place, weapon);
              if (output != 10)
                 {cout << "Player 3 can dispute it\n";
                  goto nextround;}
              else if (output == 10){
                 cout << "Player 3 can not dispute it\n";
                 output = you.accuseComputer(person, place, weapon);}
              if (output != 10)
                 {cout << "You can dispute it\n";
                  goto nextround;}
              else if (output == 10){
                 cout << "You can not dispute it\n";
                 output = player1.accuseComputer(person, place, weapon);}
              if (output != 10)
                 {cout << "Player 1 can dispute it\n";
                  goto nextround;}
              else if (output == 10){
                 cout << "Player 1 can not dispute it\n";} 
              nextround:
              cin.ignore(1);
              //Player 3 Goes
              person = randomNum(5,0);
              place = randomNum(8,0);
              weapon = randomNum(5,0);
              cin.ignore(1);
              cout << "Player 3: \"It was ";
              personD(person);
              cout << " in the ";
              locationD(place);
              cout << " with the ";
              weaponD(weapon); 
              cout << "\"\n";
              cin.ignore(1);
              output = you.accuseComputer(person, place, weapon);
              if (output != 10)
                 {cout << "You can dispute it\n";
                  goto nextround2;}
              else if (output == 10){
                 cout << "You can not dispute it\n";
                 output = player1.accuseComputer(person, place, weapon);}
              if (output != 10)
                 {cout << "Player 1 can dispute it\n";
                  goto nextround2;}
              else if (output == 10){
                 cout << "Player 1 can not dispute it\n";
                 output = player2.accuseComputer(person, place, weapon);} 
              if (output != 10)
                 {cout << "Player 2 can dispute it\n";
                  goto nextround2;}
              else if (output == 10){
                 cout << "Player 2 can not dispute it\n";}
              nextround2:
              cin.ignore(1);
              round++;
          }
           
    };
    
    cout << "\n\nPlayer 1 had";
    player1.read();
    cout << "\n\nPlayer 2 had";
    player2.read();
    cout << "\n\nPlayer 3 had";
    player3.read();
    cout << "\n\nWhat really happened was:\n";
    final.write();
    cin.ignore(2);
    

}


int randomNum(int HIGH, int LOW)
{
    int random;
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    random=rand()%(HIGH-LOW+1)+LOW;
    return random;
}

void personD(int input)
{
            switch(input){
            case 0:
                 cout << "Miss Scarlett";
                 break;
            case 1:
                 cout << "Colonel Mustard";
                 break;
            case 2:
                 cout << "Mrs. White";
                 break;
            case 3:
                 cout << "Mr. Green";
                 break;
            case 4:
                 cout << "Mrs. Peacock";
                 break;
            case 5:
                 cout << "Professor Plum";
                 break;
            }
}

void locationD(int input)
{
            switch(input)
            {
                 case 0:
                 cout << "Kitchen";
                 break;
                 case 1:
                 cout << "Ballroom";
                 break;
                 case 2:
                 cout << "Conservatory";
                 break;
                 case 3:
                 cout << "Billiard Room";
                 break;
                 case 4:
                 cout << "Library";
                 break;
                 case 5:
                 cout << "Study";
                 break;
                 case 6:
                 cout << "Hall";
                 break;
                 case 7:
                 cout << "Lounge";
                 break;
                 case 8:
                 cout << "Dining Room";
                 break;
            }
}

void weaponD(int input)
{
            switch(input){
            case 0:
                 cout << "Candelstick";
                 break;
            case 1:
                 cout << "Knife";
                 break;
            case 2:
                 cout << "Lead Pipe";
                 break;
            case 3:
                 cout << "Revolver";
                 break;
            case 4:
                 cout << "Rope";
                 break;
            case 5:
                 cout << "Wrench";
                 break;
            }
}
