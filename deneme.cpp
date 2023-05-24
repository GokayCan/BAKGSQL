#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum query{
    _create = 1, // database veya tablo olustur           //create database dname //create table dname/tname p1,p2,p3,
    _select = 2, // tablodan veri oku
    _insert = 3, // tabloya veri ekle
    _update = 4, // tablodaki veriyi guncelle
    _delete = 5, // database veya tabloyu sil            //delete database dname //delete table dname/tname
    _list = 6, // databaseleri veya tablolari listele   //list databases   //list tables dname
    none = 7, //bos
};

int main(){
    string sorgu,kelime;
    vector<string> kelimeler;
    query qType = none;

    //Create SH
    string createDatabaseSH = "./CreateDatabase.sh";
    string createTableSH = "./CreateTable.sh";
    //List SH
    string listTablesSH = "./ListTables.sh";
    string listDatabasesSH = "./ListDatabases.sh";
    //Delete SH
    string deleteDatabaseSH = "./DeleteDatabase.sh";
    string deleteTableSH = "./DeleteTable.sh";
    //Insert SH
    string insertTable = "./InsertTable.sh";


    cout<<"=>";
    getline(cin,sorgu);

    while(sorgu!="q"){
        stringstream ss(sorgu);
        while(ss >> kelime) {
            kelimeler.push_back(kelime);
        }
        if(kelimeler[0] == "create"){
            qType = _create;
        }
            
        else if (kelimeler[0] == "list"){
            qType = _list;
        }
        else if (kelimeler[0] == "delete"){
            qType = _delete;
        }
        else if(kelimeler[0]== "insert"){
            qType = _insert;
        }

        switch (qType)
        {
            //create islemi yapmak icin
            case _create:
                //database olusturmak icin
                if(kelimeler[1] == "database"){
                    string command = createDatabaseSH + " " + kelimeler[2];
                    int result = system(command.c_str());

                    if(result == -1) {
                        cout<<"database oluşturulurken hata meydana geldi"<< endl;
                    }
                    else {
                        cout<<"database başarıyla oluşturuldu"<< endl;
                    } 

                    kelimeler.clear();
                }
                //tablo olusturmak icin
                else if(kelimeler[1] == "table"){
                    string command,tableName = kelimeler[2];
                    //vector<string> params;
                    int sayac = 0;

                    int pos = tableName.find("/");
                    string databaseName = tableName.substr(0,pos);
                    tableName = tableName.substr(pos+1);

                    // parametrelerin basina ve sonuna , koyulan kisim. sorgu su sekilde yazilmali -> create table alperen/table1 adi,soyadi,yasi,hava durumu, 
                    string shString = "";
                    //cout<<kelimeler.size()<<endl;
                    for(int i = 3; i< kelimeler.size();i++){
                        //cout<<kelimeler[i]<<endl;
                        shString += kelimeler[i];
                        shString += " ";
                    }
                    //cout<<shString<<endl;
                    vector<string> shParams;
                    int parampos =0;
                    while(parampos != -1){
                        parampos = shString.find(",");
                        string word = shString.substr(0,parampos);
                        word = "," + word + ",";
                        shParams.push_back(word);
                        //cout<<"calisti"<<endl;
                        shString = shString.substr(parampos+1);
                        parampos = shString.find(",");// bu kisimda parampos -1 mi diye if konulup eger -1 ise kalan kisim yine word e konulur ve diziye atılır. bu sekilde kullanici sorguyu yazarken en sona virgul koymasina gerek kalmaz. bkz 67
                    }//
                    //-----------------------------------------------------------//

                    command = createTableSH + " " + databaseName + " " + tableName + " ";

                    for(int i = 0;i<shParams.size();i++){
                        command += " " + shParams[i];
                    }
                    system(command.c_str());
                    shParams.clear();
                    kelimeler.clear();
                    sorgu="";
                }
            break;
            case _list:
                if(kelimeler[1]=="databases"){
                    string command = listDatabasesSH;
                    int result = system(command.c_str());
                    if(result==-1){
                        cout<<"Listeleme Yaparken Bir Sorun Oldu!!"<<endl;
                    }
                    kelimeler.clear();
                }
                else if(kelimeler[1]=="tables"){
                    string databaseName;
                    databaseName = kelimeler[kelimeler.size()-1];
                    string command = listTablesSH + " " + databaseName;
                    int result = system(command.c_str());
                    if(result==-1){
                        cout<<"Listeleme Yaparken Bir Sorun Oldu!!"<<endl;
                    }
                }
                kelimeler.clear();
                sorgu="";
            break;

            case _delete:
                if(kelimeler[1] == "database"){
                    string databaseName;
                    databaseName = kelimeler[kelimeler.size()-1];
                    string command = deleteDatabaseSH + " " + databaseName;
                    int result = system(command.c_str());
                    if(result==-1){
                        cout<<"Database Silinemedi"<<endl;
                    }
                }
                else if (kelimeler[1] == "table"){
                    string command = deleteTableSH + " " + kelimeler[2];
                    int result = system(command.c_str());
                    if(result==-1){
                        cout<<"Table Silinemedi"<<endl;
                    }
                }
                kelimeler.clear();
                sorgu="";
            break;

            case _insert:
                //insert into alperen/kisi adi,soyadi,tel no, values ,alperen,sari,03 333,
                if(true){
                    string tableName = kelimeler[2],command; 

                    int pos = tableName.find("/");
                    string databaseName = tableName.substr(0,pos);
                    tableName = tableName.substr(pos+1);

                    string shString = "";
                    vector<string> shParams;
                    vector<string> shValues;

                    for(int i = 3;i<kelimeler.size();i++){
                        shString += kelimeler[i];
                        shString += " ";
                    }
                    cout<<shString<<endl;
                
                    int parampos = shString.find(",");
                    int cutter = shString.find("values");
                    //cout<<to_string(cutter);
                    while(parampos != -1){
                        string word = shString.substr(0,parampos);
                        word = "," + word + ",";
                        shString = shString.substr(parampos+1);
                        cutter = shString.find("values");
                        parampos = shString.find(",");
                        //cout<<to_string(parampos)<<endl;
                        if(parampos<cutter) shParams.push_back(word);
                        else shValues.push_back(word);
                    }
                
                    for(int i =0;i<shParams.size();i++)
                        cout<<shParams[i]<< " ";
                    cout<<"param bitti"<<endl;

                    for(int i =0;i<shValues.size();i++)
                        cout<<shValues[i]<< " ";
                    cout<<endl;
                
                
                
                }

            break;

            default:
                kelimeler.clear();
                sorgu="";
            break;
        }
        cout<<"=>";
        getline(cin,sorgu);
    }
    cout << endl << "Program Sonu";
    return 0;
} 