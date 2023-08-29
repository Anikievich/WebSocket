//
// Created by aniki on 8/27/23.
//

#ifndef SERVER_TABLE_H
#define SERVER_TABLE_H
#include <optional>

struct Table {

        bool empty(){
            return (age == std::nullopt && FName == std::nullopt && LName == std::nullopt);
        }
        unsigned int position = 0;
        unsigned int height = 10;
        std::optional<bool> age = std::nullopt; //true is ascending, false is descending
        std::optional<bool> FName = std::nullopt;
        std::optional<bool> LName = std::nullopt;
    };


#endif //SERVER_TABLE_H
