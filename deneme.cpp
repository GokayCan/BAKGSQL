#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum query{
    _create = 1,
    _select = 2,
    none = 3,    
};

int main(){
    string sorgu,kelime;
    vector<string> kelimeler;
    query qType = none;
    string cdScript = "./CDatabase.sh";
    string ctScript = "./CTable.sh";

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
            
        else if (kelimeler[0] == "select") 
        {
            qType = _select;
        }


        switch (qType)
        {
            //create islemi yapmak icin
            case _create:
                //database olusturmak icin
                if(kelimeler[1] == "database"){
                    string command = cdScript + " " + kelimeler[2];
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
                    vector<string> params;
                    int sayac = 0;

                    int pos = tableName.find("/");
                    string databaseName = tableName.substr(0,pos);
                    tableName = tableName.substr(pos+1);

                    for(int i = 3; i < kelimeler.size(); i++){ 
                        sayac++;
                        params.push_back(kelimeler[i]);
                    }

                    command = ctScript + " " + databaseName + " " + tableName + " ";

                    for(int i = 0;i<params.size();i++){
                        command += " " + params[i];
                    }
                    system(command.c_str());
                    params.clear();
                    kelimeler.clear();
            }
            break;
        
            default:      
            break;
        }

        cout<<"=>";
        getline(cin,sorgu);
    }
    cout << endl << "Program Sonu";
    return 0;
} 