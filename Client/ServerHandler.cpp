//
// Created by aniki on 8/26/23.
//

#include "ServerHandler.h"

ServerHandler::ServerHandler(int sock) {
    this->fd = sock;
    pack_size= sizeof(packet_type);
    sizeDisplay = sizeof(client);
}

void ServerHandler::run() {
    int cou;
    std::cout<<"Run"<<std::endl;
    int nbytes= recv(fd, (char*)&cou, sizeof(int), 0);
    std::cout<<cou<<std::endl;
    Person *pre = new Person[cou];
    nbytes= recv(fd, (char*)pre, sizeof(Person)*cou, 0);

    for (int j = 0; j < cou; ++j) {
        std::cout<<pre[j].ID<< " " <<pre[j].age<<" "<<pre[j].FName<<" "<<pre[j].LName<<std::endl;
    }
    delete[] pre;

    //thread for read
    std::thread th([&](){
        readSocket();
    });
    start();
};

void ServerHandler::start() {

        while (true) {
            //write
            int nbytes;
            std::cin >> pac;
            if (pac ==  Package::Show_Table) {
                packet_ = Package::Show_Table;
            } else if (pac == Change) {
                packet_ = Package::Change;
            } else {
                std::cout << "Input Error";
            }
            std::cout << "Pac: "<< pac << std::endl;

            char qw[] = "Dest";
            char qw1[] = "Pest";
            Person person_(43, qw, qw1);
            switch (packet_) {
                case Show_Table:
                    nbytes = send(fd, (char*)&packet_, sizeof(Package), 0);
                    if(nbytes<0){
                        std::cout<< "Client: Response was not sent (\"Show_Table\") " <<std::endl;
                    }
                    nbytes = send(fd, (char*)&client, sizeof(Table), 0); // Input from console!!!!!
                    if(nbytes<0){
                        std::cout<< "Client: Response was not sent (\"Show_Table\") " <<std::endl;
                    }
                    break;
                case Change:
                    nbytes = send(fd, (char*)&packet_, sizeof(Package), 0);
                    if(nbytes<0){
                        std::cout<< "Client: Response was not sent (\"Show_Table\") " <<std::endl;
                    }
                    std::cout<<"FName :"<<person_.FName<<std::endl;
                    if (send(fd, (char*)&person_, sizeof(Person), 0) < 0) {
                        std::cout<< "Server: Response was not sent (\"Show_Table\") " <<std::endl;
                        break;
                    }
                    break;
            }
        }
}

void ServerHandler::readSocket() {
    while(true) {
        std::cout<<"New thread"<<std::endl;
        int sizeArrayPerson;
        int nbytes = recv(fd, (char *)&sizeArrayPerson, sizeof(int), 0);
        std::cout << "Cou: " << sizeArrayPerson << std::endl;
        {
            Person *pre1 = new Person[sizeArrayPerson];
            nbytes = recv(fd, pre1, sizeof(Person) * sizeArrayPerson, 0);
            for (int j = 0; j < sizeArrayPerson; ++j) {
                std::cout << pre1[j].ID << " " << pre1[j].age << " " << pre1[j].FName << " " << pre1[j].LName
                          << std::endl;
            }
            delete[] pre1;
        }
    }
}



