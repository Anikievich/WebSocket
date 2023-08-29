//
// Created by aniki on 8/27/23.
//

#ifndef SERVER_PERSON_H
#define SERVER_PERSON_H


struct Person{
    Person();
    Person( unsigned int age, const char FName[20],const char LName[20]);
    Person (const Person &per);
    static int getCount();

    int ID;
    unsigned int age{};
    char FName[20]{};
    char LName[20]{};

private:
    static int count;

};



#endif //SERVER_PERSON_H
