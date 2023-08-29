//
// Created by aniki on 8/27/23.
//

#include "Person.h"

int Person::count = 0;

Person::Person(){
    this->age = 0;
    this->FName[0] = '\0';
    this->LName[0] = '\0';
}

Person::Person(unsigned int age, const char FName[20],const char LName[20]) {
        int i = 0;
        this->age = age;
        for (i = 0; FName[i] != '\0'; ++i) {
            this->FName[i] = FName[i];
        }
        this->FName[i] = '\0';
        for (i = 0; LName[i] != '\0'; ++i) {
            this->LName[i] = LName[i];
        }
        this->LName[i] = '\0';

};
Person::Person(const Person &per){
        int i=0;
        this->age = per.age;
        for ( i = 0; per.FName[i]!='\0' ; ++i) {
            this-> FName[i] = per.FName[i];
        }
        this->FName[i]='\0';
        for (i = 0; per.LName[i]!='\0' ; ++i) {
            this->LName[i] = per.LName[i];
        }
        this->LName[i]='\0';
        this->ID=per.ID;
};

