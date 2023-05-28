#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
enum query
{
    _create = 1, // database veya tablo olustur                //create database dname //create table dname/tname p1,p2,p3,
    _select = 2, // tablodan veri oku                         //select dname/dtable
    _insert = 3, // tabloya veri ekle                        //insert into alperen/kisi adi,soyadi,tel no, values ,alperen,sari,03 333,
    _update = 4, // tablodaki veriyi guncelle               //update dname/dtable id ad,soyadi,tel no, values gad,gsoyadi,gtel no 
    _delete = 5, // tablodan veri silmek                   //delete dname/dtable id
    _list = 6,   // databaseleri veya tablolari listele   //list databases   //list tables dname
    _drop = 7,   // database veya tabloyu sil            //drop database dname //drop table dname/tname
    none = 8,    // bos
};

void logger(string logText);

int main()
{
    string sorgu, kelime;
    vector<string> kelimeler;
    query qType = none;

    // Create SH
    string createDatabaseSH = "./CreateDatabase.sh";
    string createTableSH = "./CreateTable.sh";
    // List SH
    string listTablesSH = "./ListTables.sh";
    string listDatabasesSH = "./ListDatabases.sh";
    // Delete SH
    string dropDatabaseSH = "./DropDatabase.sh";
    string dropTableSH = "./DropTable.sh";
    // Insert SH
    string insertTable = "./InsertTable.sh";

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
        else if(kelimeler[0]=="update"){
            qType=_update;
        }
        switch (qType)
        {
        // create islemi yapmak icin
        case _create:
            // database olusturmak icin
            if (kelimeler[1] == "database")
            {
                string command = createDatabaseSH + " " + kelimeler[2];
                int result = system(command.c_str());

                if (result == -1)
                {
                    cout << "database oluşturulurken hata meydana geldi" << endl;
                }
                else
                {
                    cout << "database başarıyla oluşturuldu" << endl;
                }
            }
            // tablo olusturmak icin
            else if (kelimeler[1] == "table")
            {
                string command, tableName = kelimeler[2];
                // vector<string> params;
                int sayac = 0;

                int pos = tableName.find("/");
                string databaseName = tableName.substr(0, pos);
                tableName = tableName.substr(pos + 1);

                // parametrelerin basina ve sonuna , koyulan kisim. sorgu su sekilde yazilmali -> create table alperen/table1 adi,soyadi,yasi,hava durumu,
                string shString = "";
                // cout<<kelimeler.size()<<endl;
                for (int i = 3; i < kelimeler.size(); i++)
                {
                    // cout<<kelimeler[i]<<endl;
                    shString += kelimeler[i];
                    shString += " ";
                }
                // cout<<shString<<endl;
                vector<string> shParams;
                int parampos = 0;
                while (parampos != -1)
                {
                    parampos = shString.find(",");
                    string word = shString.substr(0, parampos);
                    word = "," + word + ",";
                    shParams.push_back(word);
                    // cout<<"calisti"<<endl;
                    shString = shString.substr(parampos + 1);
                    parampos = shString.find(","); // bu kisimda parampos -1 mi diye if konulup eger -1 ise kalan kisim yine word e konulur ve diziye atılır. bu sekilde kullanici sorguyu yazarken en sona virgul koymasina gerek kalmaz. bkz 67
                }                                  //
                //-----------------------------------------------------------//

                command = createTableSH + " " + databaseName + " " + tableName + " ";

                for (int i = 0; i < shParams.size(); i++)
                {
                    command += " " + shParams[i];
                }
                system(command.c_str());
                shParams.clear();
                kelimeler.clear();
                sorgu = "";
            }
            break;
        case _list:
            if (kelimeler[1] == "databases")
            {
                string command = listDatabasesSH;
                int result = system(command.c_str());
                if (result == -1)
                {
                    cout << "Listeleme Yaparken Bir Sorun Oldu!!" << endl;
                }
                kelimeler.clear();
            }
            else if (kelimeler[1] == "tables")
            {
                string databaseName;
                databaseName = kelimeler[kelimeler.size() - 1];
                string command = listTablesSH + " " + databaseName;
                int result = system(command.c_str());
                if (result == -1)
                {
                    cout << "Listeleme Yaparken Bir Sorun Oldu!!" << endl;
                }
            }
            kelimeler.clear();
            sorgu = "";
            break;

        case _drop:
            if (kelimeler[1] == "database")
            {
                string databaseName;
                databaseName = kelimeler[kelimeler.size() - 1];
                string command = dropDatabaseSH + " " + databaseName;
                int result = system(command.c_str());
                if (result == -1)
                {
                    cout << "Database Silinemedi" << endl;
                }
            }
            else if (kelimeler[1] == "table")
            {
                string command = dropTableSH + " " + kelimeler[2];
                int result = system(command.c_str());
                if (result == -1)
                {
                    cout << "Table Silinemedi" << endl;
                }
            }
            kelimeler.clear();
            sorgu = "";
            break;

        case _insert:
            // insert into alperen/kisi id,adi,soyadi,tel no, values ,5,alperen,sari,03 333,
            if (true)
            {
                string tableName = kelimeler[2], command;

                int pos = tableName.find("/");
                string databaseName = tableName.substr(0, pos);
                tableName = tableName.substr(pos + 1);

                string shString = "";
                vector<string> shParams;
                vector<string> shValues;

                for (int i = 3; i < kelimeler.size(); i++)
                {
                    shString += kelimeler[i];
                    shString += " ";
                }
                // cout<<shString<<endl;

                int parampos = shString.find(",");
                int cutter = shString.find("values");
                // cout<<"param:"<<to_string(parampos)<<endl;
                // cout<<"cutter:"<<to_string(cutter)<<endl;
                while (parampos != -1)
                {
                    string word = shString.substr(0, parampos);
                    word = "," + word + ",";
                    shString = shString.substr(parampos + 1);
                    if (parampos < cutter)
                        shParams.push_back(word);
                    else if (parampos > cutter && word != ", values ,")
                        shValues.push_back(word);
                    cutter = shString.find("values");
                    parampos = shString.find(",");
                    // cout<<"param:"<<to_string(parampos)<<endl;
                    // cout<<"cutter:"<<to_string(cutter)<<endl;
                    // cout<<to_string(parampos)<<endl;
                }

                /*for(int i =0;i<shParams.size();i++)
                    cout<<shParams[i]<< " ";
                cout<<"param bitti"<<endl;

                for(int i =0;i<shValues.size();i++)
                    cout<<shValues[i]<< "/";
                cout<<endl;*/

                command = insertTable + " " + databaseName + " " + tableName + " ";

                for (int i = 0; i < shParams.size(); i++)
                {
                    command += shParams[i] + " ";
                }

                command += "_ ";

                for (int i = 0; i < shValues.size(); i++)
                {
                    command += shValues[i] + " ";
                }
                system(command.c_str());
                kelimeler.clear();
                sorgu = "";
            }
            break;

        case _select:
        {
            ifstream file(kelimeler[1] + ".bakg");

            if (file.is_open())
            {
                string line;

                // İlk satırı oku ve sütun adlarını göster
                getline(file, line);
                istringstream iss(line);
                string column;

                while (getline(iss, column, ','))
                {
                    if (!column.empty())
                    {
                        cout << left << setw(10) << column;
                    }
                }

                cout << endl;

                // Verileri oku ve ekrana bas
                while (getline(file, line))
                {
                    istringstream iss(line);
                    string data;

                    while (getline(iss, data, ','))
                    {
                        if (!data.empty())
                        {
                            cout << left << setw(10) << data;
                        }
                    }

                    cout << endl;
                }

                file.close();
            }
            else
            {
                cout << "Dosya açılamadı." << endl;
            }
            kelimeler.clear();
            sorgu = "";
        }
        break;
        case _delete:
        {
            string tableName = kelimeler[1];
            int pos = tableName.find("/");
            string databaseName = tableName.substr(0,pos);
            tableName = tableName.substr(pos+1);

            ifstream file(kelimeler[1] + ".bakg");
            string id,deletedId;
            bool flag=false;
            vector<string> records;
            id = kelimeler[2];

            if (file.is_open()) {
                string line;

                getline(file, line);
                istringstream iss(line);
                string column;
                records.push_back(line);
                while (getline(file, line)) {
                    istringstream iss(line);
                    string data;

                    while (getline(iss, data, ',')) {
                        if (!data.empty()) {
                            if(data==id){
                                flag=true;
                                break;
                            }
                        }
                    }

                    if (!flag) {
                        records.push_back(line);
                    }
                    flag=false;
                }
                file.close();

                ofstream outFile(databaseName+"/" + tableName + ".bakg");
                if(outFile.is_open()){
                    for(const string& record:records){
                        outFile<<record<<endl;
                    }
                    outFile.close();
                    //remove(databaseName+"/"+tableName+".bakg");
                    //rename(databaseName+"/temp.bakg",databaseName+"/"+tableName+".bakg");
                    cout<<"Kayit Silindi"<<endl;
                }
            }
            else {
                cout << "Dosya açılamadı." << endl;
            }
            kelimeler.clear();
            sorgu = "";
        }
        break;
        case _update:
        {
            // update alperen/kisi id id,adi,soyadi,tel no, values ,5,alperen,sari,03 333,
            if (true)
            {
                string tableName = kelimeler[1], command;
                int pos = tableName.find("/");
                string databaseName = tableName.substr(0,pos);
                tableName = tableName.substr(pos+1);


                string oldValue,updateValue,result,token;

                for (int i = 3; i < kelimeler.size(); i++)
                {
                    oldValue=kelimeler[i];
                }

                cout<<"Mevcut Veri:"<<oldValue<<endl;

                stringstream ss(oldValue);

                while (std::getline(ss, token, ',')) {
                    if (!token.empty()) {
                        result += " ," + token + ",";
                    }
                }

                updateValue=result;

                cout<<"Güncellenmiş veri:"<<updateValue<<endl;                

                ifstream file(kelimeler[1] + ".bakg");
                string id,deletedId;
                bool flag=false;
                vector<string> records;
                id = kelimeler[2];

                if (file.is_open()) {
                    string line;

                    getline(file, line);
                    istringstream iss(line);
                    string column;
                    records.push_back(line);
                    while (getline(file, line)) {
                        istringstream iss(line);
                        string data;

                        while (getline(iss, data, ',')) {
                            if (!data.empty()) {
                                if(data==id){
                                    records.push_back(updateValue);
                                    flag=true;
                                    break;
                                }
                            }
                        }

                        if (!flag) {
                            records.push_back(line);
                        }
                        flag=false;
                    }
                    file.close();

                    ofstream outFile(databaseName+"/" + tableName + ".bakg");
                    if(outFile.is_open()){
                        for(const string& record:records){
                            outFile<<record<<endl;
                        }
                        outFile.close();
                        cout<<"Kayit Güncellendi"<<endl;
                    }
                }
                

                //system(command.c_str());
                kelimeler.clear();
                sorgu = "";
            }
            break;
        }

        default:
            kelimeler.clear();
            sorgu = "";
            break;
        }
        cout << "=>";
        getline(cin, sorgu);
        logger(sorgu);
    }
    cout << endl
         << "Program Sonu";
    return 0;
}

//insert into db/kisiler id,ad,soyad,yas, values ,2,gokay,can,21,
//insert into db/kisiler id,ad,soyad,yas, values ,3,gokay,can,21,
//insert into db/kisiler id,ad,soyad,yas, values ,4,gokay,can,21,
//insert into db/kisiler id,ad,soyad,yas, values ,7,gokay,can,21,

void logger(string logText)
{
    string sh = "./Logger.sh";
    string command = sh + " " + logText;
    int result = system(command.c_str());
}