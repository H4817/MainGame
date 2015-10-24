/*#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;


    fp = fopen("/home/nikolai/ClionProjects/untitled2/input", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        while (line[i] != '"' or i <= strlen(line))
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}*/ //last exp


#include <fstream>
#include <string>
#include<iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;



int main (int argc, char *argv[]){
//bool findedQuote = false;


    char line[255];
    char index[255];
    //char* ptr=line;
    //const char linex = '"';
    FILE *InputFile = fopen("/home/nikolai/ClionProjects/untitled2/input", "r");
    FILE *OutputFile = fopen("/home/nikolai/ClionProjects/untitled2/output", "w");
    ofstream fout;
    fout.open("/home/nikolai/ClionProjects/untitled2/output1");



    while (fgets(line, 255, InputFile) != NULL){
        int i = 0;
        int j = 1;
        int k = 0;
        while (i <= int (strlen(line)) ) {

            bool findedQuote = false;

            if (i != 0 && line[i] == '"' && line[i+1] == '"') { index[k] = i; k++; i++; j = i+1; index[k] = i; k++; findedQuote = true; }

            else if (line[0] == '"') { index[k] = 0; k++; findedQuote = true; }

            while ((line[i] != '"') && (i <= int (strlen(line)))) {
                i++;
                j = i + 1;
                if (line[i] == '"' ) {
                    //memmove(&line[i], &line[i + 1], strlen(line) - i);
                    findedQuote = true;
                    if (index[k] != index[k-1]){index[k] = i; k++;}
                    //else {index[k] = i; k++;}
                    //index[k] = i; k++;

                                     //line[i] = line[i] - 2;   // 32      34- кавычка
                    /*std::string str (line);
                    str.erase(i, i);
                    cout << "STR.ERASE№1: " << str << endl;*/
                    break;
                }
            }
            while ((line[j] != '"') && (j <= int(strlen(line))) && findedQuote) {
                //cout << "Смена символа:" << endl;
                if (((97 <= line[j] && line[j] <= 122) || (224 <= line[j] && line[j] <= 255)))
                    line[j] = line[j] - 32;
                j++;
                i = j - 1;
            }
            if (line[j] == '"'){
                index[k] = j;
                k++;
                //std::string str (line);
                //(str.erase(j, j));
                //cout << "STR.ERASE№2: " << str << endl;
            }
                //line[j] = line[j] - 2;
            i++;
        }
        //strstr(line, '"');
        /*for (int k = 0; k <= int(strlen(line)); k++){
            if (line[k] != '"')
            strcat(linee, &line[k]);
            //cout << "ABC***:  " << linee << endl;
        }*/
        fputs(line, OutputFile);
        /*for (int k = 0; k <= int(strlen(line)); k++){
            linee[k] = 0;
        }*/
        //fout << str;
        //line > OutputFile;
    }
    fclose (InputFile);
    fclose (OutputFile);
    for (int o = 0; o <= strlen(index); o++)
    cout << "Test123Kappa**: " << int(index[o]) << endl;
}

/*#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE *f = fopen("/home/nikolai/ClionProjects/untitled2/input.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = (char *) malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;
}*/
/*#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::string filename;
    std::cout<<"Enter filename\n";
    std::getline(std::cin, filename);
    std::ifstream ifs(filename.c_str());
    if(!ifs)
    {
        std::cerr<<"Error. Can`t open file "<< filename <<'\n';
        return 1;
    }
    std::string finded, replaced;
    std::cout<<"Enter string for find\n";
    std::cin>>finded;
    std::cout<<"Enter string for replace\n";
    std::cin>>replaced;
    std::vector<std::string> Vec;
    int cnt=0;
    while(!ifs.eof())
    {
        std::string tmp;
        ifs>>tmp;
        if(tmp == finded)
        {
            tmp=replaced;
            ++cnt;
        }
        Vec.push_back(tmp);
    }
    std::ofstream ofs(filename.c_str());
    for(std::vector<std::string>::const_iterator it=Vec.begin();
        it != Vec.end(); ++it)
        ofs<<*it<<' ';
    ofs<<'\n';
    ofs<<"Numb of replaces is: "<< cnt <<'\n';
    std::cout<<"End\n";
    ofs.close();
    ifs.close();
    return 0;
}*/ //1
// while(buf[i] != '"');
/*
#include <fstream>
#include <string>
#include<iostream>
#include <string.h>

using namespace std;




int main(int argc, char* argv[])
{
    char c, str[255], buf[255];
    int i = 0;

    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
    char buff[50]; // буфер промежуточного хранения считываемого из файла текста
    ifstream fin("/home/nikolai/ClionProjects/untitled2/input"); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
    ofstream fout("output.txt", ios_base::out);

    if (!fin.is_open()) // если файл не открыт
        cout << "Файл не может быть открыт!\n"; // сообщить об этом
    else
    {
        while (!fin.eof() && buf[i++] != '"')
        {
            fin.getline(str, 255);

            for (int i = 0; i < strlen(str); i++) {
                if ((str[i] >= '1') && (str[i] <= '9'))
                    cout << atoi(&str[i]) << " ";
            }

            cout << "\n";

        }
        cin.get();

    }
        //fin >> buff; // считали первое слово из файла
        //cout << buff << endl; // напечатали это слово
        //while(!fin.eof())
        //{

        //fin.getline(buff, 255); // считали строку из файла
        //fin.close(); // закрываем файл
        //cout << buff << endl; // напечатали эту строку


    //}
    //system("pause");
    return 0;
}*/

/* string str;
    ifstream file("text.DAT",ios::in);
    while(!file.eof())
    {
        getline(file, str);
        cout<<str<<endl;
    };
    file.close();
    system("pause");
    return 0;}*/

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
int main(int argc, char** argv) {
    int i, j;
    char *str;
    float f;
    FILE *InputFile;
    InputFile = fopen("input.txt", "r");
    if (InputFile == NULL){
        printf("Error");
        exit(0);
    }
    while( !feof(InputFile) ){
        fscanf(InputFile, "%d", &i ); //считывание всех строк с числами из файла
        fscanf(InputFile, "%s%f", str, &f);
        cout<<"i="<<i;
        // gets(in_string); // функция gets() считывает все введённые символы с пробелами до тех пор, пока не будет нажата клавиша Enter

        if (i == '"'){
            j += i + 1;
        }
    }

    return (EXIT_SUCCESS);

    getline нагуглить
}*/

//fread fopen fread/работа с памятью, как считать весь файл в память, динамическая память. Массив записать в файл.
//c how read to buffer stackoverflow;          fseek, fwrite, fread.
//scanfs - обязательно говорить сколько байт нужно считывать.