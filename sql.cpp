#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum command{
    create = 1,
    select = 2,
    none = 3
};
//create database denemeee
void CreateDatabase(string dbname);
void CreateTable(string dbname,string tablename);

int main(){
    string sorgu = "";
    int flag = 1;
    int pos = 0;
    command ctype = none;
    vector<string> sorgukelimeleri;
    cout << "Hosgeldiniz \n";
    cout << "Komut Bekleniyor => ";
    getline(cin, sorgu);
    
    while (flag){
        
        while ((pos = sorgu.find(" ")) != string::npos) {
        	sorgukelimeleri.push_back(sorgu.substr(0, pos));
			sorgu.erase(0, pos + 1);
    	}
    	sorgukelimeleri.push_back(sorgu);
    	
    	/*for (int i = 0 ; i < sorgukelimeleri.size() ; i++) {
        	std::cout << sorgukelimeleri[i] << std::endl;
    	}*/
        
        if(sorgukelimeleri[0].compare("create") == 0){
            ctype = create;
        }
        else if (sorgukelimeleri[0].compare("select") == 0){
            ctype = select;
        }
        else{
            ctype = none;
        }

        switch(ctype){
            case 1: //create kismi
                cout << "Create Komutu Secildi" << endl;
                
                if (sorgukelimeleri[1].compare("database") == 0){
                	CreateDatabase(sorgukelimeleri[2]);
				}
				
                break;
            case 2: //select kismi
                cout << "Select Komutu Secildi" << endl;
                
                break;    
            default:
                break;
        }
        cout << "Komut Bekleniyor => ";
		sorgukelimeleri.clear();   
        getline(cin, sorgu);
    }
    return 0;
}


void CreateDatabase(string dbname)
{
	cout << "Database Eklenecek : " << dbname << endl;
}
void CreateTable(string dbname,string tablename)
{
	cout << "Tablo eklenecek" << endl;
}


