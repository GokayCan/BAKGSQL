#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "bakg.h"

using namespace std;
enum query
{
    _create = 1, // database veya tablo olustur                //create database dname //create table dname/tname p1,p2,p3,
    _select = 2, // tablodan veri oku                         //select dname/dtable
    _insert = 3, // tabloya veri ekle                        //insert into alperen/kisi adi,soyadi,tel no, values ,alperen,sari,03 333,
    _update = 4, // tablodaki veriyi guncelle               //update dname/dtable X id,ad, values ,yeni id,yeni ad,  x = id
    _delete = 5, // tablodan veri silmek                   //delete dname/dtable id
    _list = 6,   // databaseleri veya tablolari listele   //list databases   //list tables dname
    _drop = 7,   // database veya tabloyu sil            //drop database dname //drop table dname/tname
    none = 8,    // bos
};

int main()
{
    string sorgu, kelime;
    vector<string> kelimeler;
    query qType = none;

    cout << "=>";
    getline(cin, sorgu);
    logger(sorgu);

    while (sorgu != "q")
    {
        stringstream ss(sorgu);
        while (ss >> kelime)
        {
            kelimeler.push_back(kelime);
        }
        if (kelimeler[0] == "create")
        {
            qType = _create;
        }
        else if (kelimeler[0] == "list")
        {
            qType = _list;
        }
        else if (kelimeler[0] == "drop")
        {
            qType = _drop;
        }
        else if (kelimeler[0] == "insert")
        {
            qType = _insert;
        }
        else if (kelimeler[0] == "select")
        {
            qType = _select;
        }
        else if (kelimeler[0] == "delete")
        {
            qType = _delete;
        }
        else if (kelimeler[0] == "update")
        {
            qType = _update;
        }

        switch (qType)
        {

        case _create:
            if (kelimeler[1] == "database")
            {
                createDatabase(kelimeler[2]);
            }
            else if (kelimeler[1] == "table")
            {
                createTable(kelimeler);
            }
            break;

        case _list:
            if (kelimeler[1] == "databases")
            {
                listDatabases();
            }
            else if (kelimeler[1] == "tables")
            {
                listTables(kelimeler);
            }
            break;

        case _drop:
            if (kelimeler[1] == "database")
            {
                dropDatabase(kelimeler);
            }
            else if (kelimeler[1] == "table")
            {
                dropTable(kelimeler[2]);
            }
            break;

        case _insert:

            insert(kelimeler);

            kelimeler.clear();
            sorgu = "";
            break;

        case _select:
        {
            select(kelimeler[1]);
        }
        break;
        case _delete:
        {
            deletee(kelimeler);
        }
        break;
        case _update:
        {
            update(kelimeler);
            break;
        }

        default:
            kelimeler.clear();
            sorgu = "";
            break;
        }

        kelimeler.clear();
        sorgu = "";

        cout << "=>";
        getline(cin, sorgu);

        logger(sorgu);
    }
    cout << endl << "Program Sonu";
    return 0;
}