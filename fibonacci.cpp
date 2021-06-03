#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>

using namespace std;

void *Fibonacci(void *arg)
{
        vector<unsigned int> *fib_series = (vector<unsigned int>*)arg;
        fib_series[0][0] = 1;
        fib_series[0][1] = 1;
        for ( int i = 2 ; i < fib_series[0].size() ; i++ )
        {
                fib_series[0][i] = fib_series[0][i - 1] + fib_series[0][i - 2];
        }
        return NULL;
}

int main(int argc, char *argv[])
{
        pthread_t tid;
        if ( argc != 2)
        {
                cout << "Invalid arguments\n Usage: ./partA [number]\n";
        }
        int val = stoi(argv[1]);
        vector<unsigned int> fib_series(val);
        pthread_create(&tid,NULL,Fibonacci,(void*)&fib_series);

        pthread_join(tid,NULL);

        cout << "Fibonacci Series : ";
        for ( int i = 0 ; i < fib_series.size() ; ++i )
        {
                cout << fib_series[i] << " ";
        }
        cout << endl;
        return 0;
}