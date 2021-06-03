#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>

using namespace std;

bool isVowel(char c)
{
        c = tolower(c);
        switch(c)
        {
                case 'a':
                        return true;
                case 'e':
                        return true;
                case 'i':
                        return true;
                case 'o':
                        return true;
                case 'u':
                        return true;                               
        }
        return false;
}
void *vow(void *arg)
{
        string s = (char*) arg;
        for ( int i = 0 ; i < s.length() ; i++ )
        {
                if ( ((i != 0 && s[i - 1] == ' ' ) || (i == 0)) && isVowel(s[i]) )
                {
                        cout << "vow: ";
                        for ( int j = i ; ; j++)
                        {
                                if ( s[j] == ' ' || s[j] == '\0' )
                                {
                                        break;
                                }
                                cout << s[j];
                        }
                        cout << endl;
                }
        }
        return NULL;
}

void *con(void *arg)
{
        string s = (char*) arg;
        for ( int i = 0 ; i < s.length() ; i++ )
        {
                if ( ((i != 0 && s[i - 1] == ' ' ) || (i == 0)) && !isVowel(s[i]) )
                {
                        cout << "con: ";
                        for ( int j = i ; ; j++)
                        {
                                if ( s[j] == ' ' || s[j] == '\0' )
                                {
                                        break;
                                }
                                cout << s[j];
                        }
                        cout << endl;
                }
        }
        return NULL;
}
int main(int argc, char*argv[])
{
        if ( argc != 2)
        {
                cout << "Invalid Argument\nUsage: ./partB \"Close string in double quotes\"\n";
        }

        pthread_t tid1, tid2;
        pthread_create(&tid1,NULL,vow,(void*)argv[1]);
        pthread_create(&tid2,NULL,con,(void*)argv[1]);

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
}