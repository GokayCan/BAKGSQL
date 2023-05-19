#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum query{
    _create = 1,
    //_select = 2,
    none = 3,    
};

int main(){
    string sorgu,kelime;
    vector<string> kelimeler;
    query qType = none;
    string cdScript = "./CDatabase.sh";
    string ctScript = "./CTable.sh";
    bool flag = false;

    cout<<"lütfen sorgunuzu giriniz:(çıkmak için q tuşlayınız)";
    getline(cin,sorgu);

    while(sorgu!="q" || !flag){
        stringstream ss(sorgu);
        while(ss >> kelime) kelimeler.push_back(kelime);

        if(kelimeler[0] == "create") qType = _create;
        //else if (kelimeler[0] == "select") qType = _select;


        switch (qType)
        {
        case _create:
            
            if(kelimeler[1] == "database"){
                string command = cdScript + " " + kelimeler[2];
                int result = system(command.c_str());
                if(result == -1) cout<<"database oluşturulurken hata meydana geldi"<< endl;
                else cout<<"database başarıyla oluşturuldu"<< endl;
                kelimeler.clear();
            }
            else if(kelimeler[1] == "table"){
                string tableName = kelimeler[2],command;
                vector<string> params;
                int sayac=0;
                for(int i=3; i<kelimeler.size();i++){ 
                    sayac++;
                    params.push_back(kelimeler[i]);
                }
                command = ctScript + " " + tableName + " ";

                for(int i = 0;i<params.size();i++){
                    command += " " + params[i];
                }
                system(command.c_str());
                params.clear();
                kelimeler.clear();
            }
            flag = true;
            break;
        
        default:
            cout<<"zooort";
            break;
        }

        cout<<"lütfen sorgunuzu giriniz:(çıkmak için q tuşlayınız)";
        getline(cin,sorgu);
    }


} 