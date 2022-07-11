#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int randomize() 
{   
    return (rand() % 10); 
}
int main() {
    // Write C++ code here
   // std::cout << "Hello world!";
    long long  v;
    cout<<"Enter the number of the vertices \n";
    cin>>v;
    long long  i , j;
    vector<int>arr(5);
    long long  src , des , a , b , c;
    srand(time(NULL)); 
    //generate(arr.begin(), arr.end(), randomize);
    long long  no_of_edges = v*(v-1)/2;
    ofstream MyFile("writefile.txt");
    MyFile<<v<<" "<<no_of_edges<<" "<<"3"<<endl;
    for(i=0; i<v; i++)
    {
        for(j = i+1; j<v; j++)
        {
            src = i;
            des = j;
            a = rand()%10;
            b = rand()%10;
            c = rand()%10;
            //for each iteration write these 5 values in a line with space
            // between each value at first src then des followed by a , b , 
            // using FS 
            // PS i am out in FS
            MyFile<<src<<" "<<des<<" "<<a<<" "<<b<<" "<<c<<endl;
        }
    }
    MyFile.close();
    return 0;
}