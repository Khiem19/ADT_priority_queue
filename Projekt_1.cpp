#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


// struktura pakietow n
struct node {
    string data;                                //dane w pakiecie
    int priority;                               //priorytet w pakiecie, zeby klasyfikowac potem
    struct node* next;                          //otwotrzyc nastepny pakiet
};

//Kolejka ADT
class Queue {
    struct node* head = NULL;

    public:
       void enqueue (string data, int priority); //dodac dane i priorytet do Kolejki
       void dequeue ();                          //usunac pierwszy dane w kolejce
       string peek();                            //return pierwszy dane w kolejce
       bool isEmpty();                           //sprawdzac czy kolejke jest pusty czy nie 
       void display();                           //wyswietlac dane i priorytet w kolejce
       void merge();                             //laczy pakiety do jednego textu(texta)
};

Queue queue;

bool Queue::isEmpty() {                         //sprawdzac czy kolejke jest pusty czy nie 
    if (queue.head == NULL)                     //kolejka zwykle jest pusty, gdy pierwszy element jest NULL
        return true;
    else
        return false;
};

void Queue::enqueue (string data, int priority){                            //dodac dane i priorytet do Kolejki
    struct node* new_node = new node;                                       
    new_node->data = data;
    new_node->priority = priority;

    if (queue.isEmpty() || priority < queue.head->priority){                //dodac nowy pakiet do kolejki, gdy kolejka jest pusty
        new_node->next = queue.head;
        queue.head = new_node;
    }
    else {
        struct node* temp = queue.head;
        while (temp->next != NULL && temp->next->priority <= priority ) {   //szukac odpowiednia lokalizacje aby dodac nowy pakiet
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

void Queue::dequeue() {                     //usunac pierwszy dane w kolejce
    if (!queue.isEmpty())
    {
        struct node* temp = queue.head;     
        queue.head = queue.head->next;      //zmienic drugi pakiet na pierwszy
        free(temp);
    }
}

string Queue::peek() {                      //return pierwszy dane w kolejce
    return queue.head->data;
}

void Queue::display(){                                                          //wyswietlac dane i priorytet w kolejce
    struct node* temp = queue.head;
    while (temp != NULL)
    {
        cout << "[" << temp->data << "],[" << temp->priority << "]"<< endl;
        temp = temp->next;
    }
}

void Queue::merge() {                               //laczy pakiety do jednego textu(texta) [nie jestem pewnym o przypadku Dopelniacz :((]
    fstream new_txt;
    new_txt.open("Wiadomosc_W.txt",ios::out);       //otworzyc nowy *.txt
    if (new_txt.is_open()) {                
        while (!queue.isEmpty()) {
            new_txt << queue.peek() <<endl;         //pisac dane pakietow do new_txt
            queue.dequeue();                        //usunac dane, ktora juz pisalem do new_txt
        }
    }
    new_txt.close();   
}

//wyslac wiadomosc. Podzielic wiadmosc i losowac kolejnosc
void send_infor(string fileName) {                  
    string line;
    ifstream file (fileName);
    int count = 0;

    if (file.is_open()) {                                         //czytac wiadomosc 
        getline(file, line);
        int sizeOfLetter = stoi(line);

        string *list_string = new string[sizeOfLetter];
        int *list_priority = new int[sizeOfLetter];
        //Podzielic wiadomosc
        while (getline(file, line)) {
            list_string[count] = line;
            list_priority[count] = count;
            count++;
        }

        //losowac kolejnosc
        srand(1);
        random_shuffle(list_string, list_string + sizeOfLetter);
        srand(1);
        random_shuffle(list_priority, list_priority + sizeOfLetter);

        //dodac dane i priorytet wiadomoscia do Kolejki
        for (int i = 0; i < sizeOfLetter; i++) {
            //sprawdzac czy mamy dobre winiki
            cout << "string: " << list_string[i] << ", " << "priority: " << list_priority[i] << endl;
            queue.enqueue(list_string[i], list_priority[i]);
        }
    }

    file.close();
}

int main (){
    send_infor("data.txt"); //wyslac wiadomosc data.txt
    cout << "\n" << endl;
    queue.display();   //sprawdzac wyniki
    queue.merge();     //laczy pakiety do nowego textu(texta) "Wiadomosc_W"
    return 0;       
}