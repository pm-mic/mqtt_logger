#include "mqtt_database.h"
#include <stdexcept>
#include <sstream>

mqtt_database::mqtt_database(std::string filename)
{
    int rc = sqlite3_open(filename.c_str(), &this->_db);
    
    // just rage quit if it doesn't work
    if( rc != SQLITE_OK ) 
    {
        throw std::runtime_error(sqlite3_errmsg(this->_db));
    }
    
    // create table
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS MESSAGES(" \
        "ID        INTEGER   PRIMARY KEY," \
        "TOPIC     TEXT                 NOT NULL," \
        "MESSAGE   TEXT                 NOT NULL," \
        "TIMESTAMP DATETIME             NOT NULL" \
        ")";
    
    sqlite3_stmt *stmt;
    
    sqlite3_prepare_v2(this->_db, sql, -1, &stmt, NULL);

    // just rage quit if it doesn't work
    if( sqlite3_step(stmt) != SQLITE_DONE ) 
    {
        throw std::runtime_error(sqlite3_errmsg(this->_db));
    }
    
    sqlite3_finalize(stmt);
}
    
void mqtt_database::store_message(mqtt_message &message)
{
    std::ostringstream sql;
    
    sql << "INSERT INTO MESSAGES ( TOPIC, MESSAGE, TIMESTAMP ) VALUES ( '"
        << message.topic << "','" 
        << message.payload << "','" 
        << message.timestamp << "')";
    
    sqlite3_stmt *stmt;
    
    int rc = sqlite3_prepare_v2(this->_db, sql.str().c_str(), -1, &stmt, NULL);
    
    if( rc != SQLITE_OK )
    {
        throw std::runtime_error(sqlite3_errmsg(this->_db));
    }
    
    // just rage quit if it doesn't work
    if( sqlite3_step(stmt) != SQLITE_DONE ) 
    {
        throw std::runtime_error(sqlite3_errmsg(this->_db));
    }
    
    sqlite3_finalize(stmt);
}

void mqtt_database::call(mqtt_message &message)
{
    this->store_message(message);
}