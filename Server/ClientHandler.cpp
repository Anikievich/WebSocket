//
// Created by aniki on 8/26/23.
//

#include "ClientHandler.h"

ClientHandler::ClientHandler(Socket const *socket) {
    this->fd = socket->fd;
    this->addr_from = socket->addr_from;
    this->read_set = socket->read_set;
    this->active_set = socket->active_set;
    tv.tv_sec = 0;
    tv.tv_usec = 10;

}

void ClientHandler::run() {
    char qw[]= "dfsf";
    char qw1[]= "nhgm";
    person_vec.emplace_back(34, qw, qw1);
    for (int i = 0; i < NUM_THREAD; ++i) {
        thread_vec.push_back(std::make_shared<std::thread>(std::thread([&](){
            start();
        })));
    }
    while (true) {
        sleep(DELAY);
        if(select(FD_SETSIZE, &active_set, NULL, NULL, &tv)){
            if(FD_ISSET(fd, &active_set)){
                thread_vec.push_back(std::make_shared<std::thread>(std::thread([&](){
                    start();
                })));
            }
        }
    }
};

void ClientHandler::start() {
    Package packet_type;
    size_t pack_size= sizeof(packet_type);
    size_t sizeDisplay = sizeof(client);

    unsigned size = sizeof(addr_from);
    int newsock = accept(fd, (struct sockaddr *) &addr_from, &size);
    FD_SET(newsock, &read_set);

    std::cout<<"NewSocket: "<< newsock <<std::endl;

    Person *p = DisplayHandler(client[newsock]);

    int as = 10;
    size_t sizePerson = sizeof(*p) * as;

    send(newsock, (char*)&as, sizeof(int), 0);
    send(newsock, (char*)p, sizePerson, 0);

    delete[] p;


    while (true) {
        // request from scroller

        recv(newsock, (char*)&packet_type, pack_size, 0);
        //
        switch (packet_type) {
            case Show_Table:

                if(recv(newsock, (char*)&client[newsock], sizeDisplay, 0)<0){
                    std::cout<< "Client: Response was not sent (\"Show_Table\") " <<std::endl;
                }

                p = DisplayHandler(client[newsock]);

                if (send(newsock, (char*)&client[newsock].height, sizeof(int), 0) < 0) {
                    std::cout<< "Server: Response was not sent (\"Show_Table\") " <<std::endl;
                    delete[]p;
                    break;
                }
                sizePerson = sizeof(*p) * client[newsock].height;
                if (send(newsock, p, sizePerson, 0) < 0) {
                    std::cout<< "Server: Response was not sent (\"Show_Table\") " <<std::endl;
                    delete[]p;
                    break;
                }
                delete[]p;
                break;
            case Change:
                //Adding new person
                Person person_;

                recv(newsock, (char*)&person_, sizeof(Person), 0);
                std::cout<<"ID "<<person_.ID<<std::endl;
                //Into function!!!!!
                person_.ID = Person::getCount();
                person_vec.push_back(person_);
                std::cout<<"ID "<<person_.ID<<std::endl;

                for (int i = 0; i < FD_SETSIZE; ++i) {
                    if(i!=fd) {
                        if (FD_ISSET(i, &read_set)) {
                            std::cout<<"I :"<<i<<std::endl;
                            //client[i].height+=1;

                            p = DisplayHandler(client[i]);
                            sizePerson = sizeof(*p) * client[i].height;
                            if (send(i, (char*)&client[i].height, sizeof(int), 0) < 0) {
                                std::cout<< "Server: Response was not sent (\"Show_Table\") " <<std::endl;
                                delete[]p;
                                break;
                            }
                            std::cout<< "Person: "<< p[0].age <<std::endl;
                            send(i, p, sizePerson, 0);
                            delete[]p;
                        }
                    }
                }
                break;
        }

    }
}

Person* ClientHandler::DisplayHandler(struct Table &client1){

  /*  if (person_vec.size() - client1.position < client1.height) {
        client1.height = person_vec.size() - client1.position;
    }*/
    Person *per = new Person[client1.height];
    if(client1.empty()) {
        for (int i = 0, j = static_cast<int>(client1.position); i < client1.height; ++i, ++j) {
            per[i] = person_vec[j];
        }
    }
    else{
        std::vector<Person> newvec = person_vec;
        if(client1.age.value() && client1.FName == std::nullopt && client1.LName == std::nullopt) {
            std::sort(newvec.begin(), newvec.end(), [](const Person &p1, const Person &p2) {
                return p1.age < p2.age;
            });
        }else if(!client1.age.value() && client1.FName == std::nullopt && client1.LName == std::nullopt){
            std::sort(newvec.begin(), newvec.end(), [](const Person &p1, const Person &p2) {
                return p1.age > p2.age;
            });
        }else if(client1.FName.value() && client1.age == std::nullopt && client1.LName == std::nullopt){
            std::sort(newvec.begin(), newvec.end(), [](const Person &p1, const Person &p2) {
                return p1.FName < p2.FName;
            });
        }else if(!client1.FName.value() && client1.age == std::nullopt && client1.LName == std::nullopt){
            std::sort(newvec.begin(), newvec.end(), [](const Person &p1, const Person &p2) {
                return p1.FName > p2.FName;
            });
        }else if(client1.LName.value() && client1.age == std::nullopt && client1.FName == std::nullopt){
            std::sort(newvec.begin(), newvec.end(), [](const Person &p1, const Person &p2) {
                return p1.LName < p2.LName;
            });
        }else if(!client1.LName.value() && client1.age == std::nullopt && client1.FName == std::nullopt){
            std::sort(newvec.begin(), newvec.end(), [](const Person &p1, const Person &p2) {
                return p1.LName > p2.LName;
            });
        }
        for (int i = 0, j = static_cast<int>(client1.position); i < client1.height; ++i, ++j) {
            per[i] = newvec[j];
        }
    }
    return per;
}


