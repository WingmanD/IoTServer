#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>

struct Measurement
{
    int ID;
    int Value;
    std::string Timestamp;
};

class DBStatics
{
public:
    inline static auto DBStorage = sqlite_orm::make_storage("db.sqlite",
                                               sqlite_orm::make_table("measurements",
                                                                      sqlite_orm::make_column(
                                                                          "id", &Measurement::ID,
                                                                          sqlite_orm::primary_key().autoincrement()),
                                                                      sqlite_orm::make_column(
                                                                          "value", &Measurement::Value),
                                                                      sqlite_orm::make_column(
                                                                          "timestamp", &Measurement::Timestamp)
                                               ));
    
};
