#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

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

void logger(string logText)
{
    string sh = "./Logger.sh";
    string command = sh + " " + logText;
    int result = system(command.c_str());
}

void createDatabase(string kelime)
{
    string command = createDatabaseSH + " " + kelime;
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

void createTable(vector<string> kelimeler)
{
    string command, tableName = kelimeler[2];

    int sayac = 0;

    int pos = tableName.find("/");
    string databaseName = tableName.substr(0, pos);
    tableName = tableName.substr(pos + 1);

    // parametrelerin basina ve sonuna , koyulan kisim. sorgu su sekilde yazilmali -> create table alperen/table1 adi,soyadi,yasi,hava durumu,
    string shString = "";

    for (int i = 3; i < kelimeler.size(); i++)
    {

        shString += kelimeler[i];
        shString += " ";
    }

    vector<string> shParams;
    int parampos = 0;
    while (parampos != -1)
    {
        parampos = shString.find(",");
        string word = shString.substr(0, parampos);
        word = "," + word + ",";
        shParams.push_back(word);

        shString = shString.substr(parampos + 1);
        parampos = shString.find(","); // bu kisimda parampos -1 mi diye if konulup eger -1 ise kalan kisim yine word e konulur ve diziye atılır. bu sekilde kullanici sorguyu yazarken en sona virgul koymasina gerek kalmaz. bkz 67
    }                                  //
    //-----------------------------------------------------------//

    command = createTableSH + " " + databaseName + " " + tableName + " ";

    for (int i = 0; i < shParams.size(); i++)
    {
        command += " " + shParams[i];
    }
    int result = system(command.c_str());
    if (result == -1)
    {
        cout << "tablo oluşturulurken hata meydana geldi" << endl;
    }
    else
    {
        cout << "tablo başarıyla oluşturuldu" << endl;
    }
}

void listDatabases()
{
    string command = listDatabasesSH;
    int result = system(command.c_str());
    if (result == -1)
    {
        cout << "Listeleme Yaparken Bir Sorun Oldu!!" << endl;
    }
}

void listTables(vector<string> kelimeler)
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

void dropDatabase(vector<string> kelimeler)
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

void dropTable(string kelime)
{
    string command = dropTableSH + " " + kelime;
    int result = system(command.c_str());
    if (result == -1)
    {
        cout << "Table Silinemedi" << endl;
    }
}

void insert(vector<string> kelimeler)
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

    int parampos = shString.find(",");
    int cutter = shString.find("values");

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
    }

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
}

void select(string kelime)
{
    ifstream file(kelime + ".bakg");

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
}

void deletee(vector<string> kelimeler)
{
    string tableName = kelimeler[1];
    int pos = tableName.find("/");
    string databaseName = tableName.substr(0, pos);
    tableName = tableName.substr(pos + 1);

    ifstream file(kelimeler[1] + ".bakg");
    string id, deletedId;
    bool flag = false;
    vector<string> records;
    id = kelimeler[2];

    if (file.is_open())
    {
        string line;

        getline(file, line);
        istringstream iss(line);
        string column;
        records.push_back(line);
        while (getline(file, line))
        {
            istringstream iss(line);
            string data;

            while (getline(iss, data, ','))
            {
                if (!data.empty())
                {
                    if (data == id)
                    {
                        flag = true;
                        break;
                    }
                }
            }

            if (!flag)
            {
                records.push_back(line);
            }
            flag = false;
        }
        file.close();

        ofstream outFile(databaseName + "/" + tableName + ".bakg");
        if (outFile.is_open())
        {
            for (const string &record : records)
            {
                outFile << record << endl;
            }
            outFile.close();
            cout << "Kayit Silindi" << endl;
        }
    }
    else
    {
        cout << "Dosya açılamadı." << endl;
    }
}

void update(vector<string> kelimeler)
{
    string tableName = kelimeler[1], command;
    int pos = tableName.find("/");
    string databaseName = tableName.substr(0, pos);
    tableName = tableName.substr(pos + 1);

    string oldValue, updateValue, result, token;
    for (int i = 3; i < kelimeler.size(); i++)
    {
        oldValue = kelimeler[i];
    }

    stringstream ss(oldValue);

    while (std::getline(ss, token, ','))
    {
        if (!token.empty())
        {
            if (result.empty())
            {
                result += "," + token + ",";
            }
            else
            {
                result += " ," + token + ",";
            }
        }
    }

    updateValue = result;

    ifstream file(kelimeler[1] + ".bakg");
    string id, deletedId;
    bool flag = false;
    vector<string> records;
    id = kelimeler[2];

    if (file.is_open())
    {
        string line;

        getline(file, line);
        istringstream iss(line);
        string column;
        records.push_back(line);
        while (getline(file, line))
        {
            istringstream iss(line);
            string data;

            while (getline(iss, data, ','))
            {
                if (!data.empty())
                {
                    if (data == id)
                    {
                        records.push_back(updateValue);
                        flag = true;
                        break;
                    }
                }
            }

            if (!flag)
            {
                records.push_back(line);
            }
            flag = false;
        }
        file.close();

        ofstream outFile(databaseName + "/" + tableName + ".bakg");
        if (outFile.is_open())
        {
            for (const string &record : records)
            {
                outFile << record << endl;
            }
            outFile.close();
            cout << "Kayit Güncellendi" << endl;
        }
    }
}
