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
                    //vector<string> params;
                    int sayac = 0;

                    int pos = tableName.find("/");
                    string databaseName = tableName.substr(0,pos);
                    tableName = tableName.substr(pos+1);

                    // parametrelerin başına ve sonuna , koyan kısım. sorgu şu şekilde yazılmalı -> create table alperen/table1 adi,soyadi,yasi,hava durumu, 
                    string shString= kelimeler[3];//kelimeler kısmı 26. satırda boşluklara göre bölündüğü için sıkıntı çıkarıyor. sorgu, parametrelerden itibaren kesintisiz alınmalı bi şekilde
                    cout<<shString<<endl;
                    vector<string> shParams;
                    int parampos =0;
                    while(parampos != -1){
                        parampos = shString.find(",");
                        string word = shString.substr(0,parampos);
                        word = "," + word + ",";
                        shParams.push_back(word);
                        cout<<"calisti"<<endl;
                        shString = shString.substr(parampos+1);
                        parampos = shString.find(",");// bu kısımda parampos -1 mi diye if konulup eğer -1 ise kalan kısım yine word e konulur ve diziye atılır. bu şekilde kullanıcı sorguyu yazarken en sona virgül koymasına gerek kalmaz. bkz 67
                    }//
                    //-----------------------------------------------------------//

                    /*for(int i = 3; i < kelimeler.size(); i++){ 
                        sayac++;
                        params.push_back(kelimeler[i]);
                    }*/

                    command = ctScript + " " + databaseName + " " + tableName + " ";

                    for(int i = 0;i<shParams.size();i++){
                        command += " " + shParams[i];
                    }
                    system(command.c_str());
                    shParams.clear();
                    kelimeler.clear();
            }
            break;
        
            default:
                kelimeler.clear();
                
            break;
        }

        cout<<"=>";
        getline(cin,sorgu);
    }
    cout << endl << "Program Sonu";
    return 0;
} 