#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

int sort(vector<vector<long long>> & v, long long start, long long end){

    long long m = start, k = (start + end)/2;
    vector<long long> p;

    if(end-start < 1) return 0;

    long long x = v[k][0];

    for(long long i = start; i <= end; i++)
        if(v[i][0] < x) m++;

    p = v[m];
    v[m] = v[k];
    v[k] = p;

    long long s1 = start, s2 = m+1;
    while(s1 < m && s2 <= end){
        if(v[s1][0] >= x){
            while(v[s2][0] >= x && s2 < end) s2++;

            p = v[s1];
            v[s1] = v[s2];
            v[s2] = p;
        }
        s1++;
    }

    sort(v, start, m-1);
    sort(v, m+1, end);

    return 0;
}

int main(){

    vector<vector<long long>> citi = {};
    vector<vector<long long>> citi1 = {};
    vector<vector<long long>> bom = {};

    long long n, m, ni, mi, j = 0;

    ifstream fin("shelter.in");
    ofstream fout("shelter.out");

    fin >> n;
    for(long long i = 0; i < n; i++){
        fin >> ni;
        citi.push_back({ni, i});
    }

    fin >> m;
    for(long long i = 1; i <= m; i++){
        fin >> mi;
        bom.push_back({mi, i});
    }

    citi1 = citi;

    sort(citi, 0, n-1);

    sort(bom, 0, m-1);

    for(long long i = 0; i < n; i++)
    {
        while(j < m-1 && abs(citi[i][0] - bom[j][0]) > abs(citi[i][0] - bom[j+1][0]))
        {
            j++;
        }
        citi1[citi[i][1]][1] = bom[j][1];
    }

    for(long long i = 0; i < n; i++){
        fout << citi1[i][1] << " ";
    }

}