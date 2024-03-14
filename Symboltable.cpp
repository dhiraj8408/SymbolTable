#include<bits/stdc++.h>
using namespace std;

const string Begin = "begin";
const string End = "end";
const string Assign = "assign";
const string Print = "print";
const int bucketSize = 29;
const int weight = 3;
class SymbolTable{
private:
    vector<list<pair<string,int>>>hashTable;
public:
    SymbolTable(){
        this->hashTable.resize(bucketSize);
        this->outerScope = NULL;
    }

    int hashValue(string variablename){
        int hashval = 0;
        int size = variablename.size();
        for(int i = 0;i < size;i++){
            int factor = (int)pow(weight,size - i - 1);
            factor *= (variablename[i] - 'a');
            factor %=  bucketSize;
            hashval += factor;
        }
        hashval %= bucketSize;
        return hashval;
    }

    bool find(string name,int &val){
        bool ans = false;
        int idx = hashValue(name);
        for(auto itr = hashTable[idx].begin(); itr != hashTable[idx].end() && !ans; ++itr){
            if(itr->first == name){
                ans = true;
                val = itr->second;
            }
        }
        return ans;
    }

    void insert(string name,int val){
        int idx = hashValue(name);
        if(hashTable[idx].empty()){
            hashTable[idx].push_back({name,val});
        }
        else{
            int val;
            if(find(name,val)){
                cout<<"REDECLARATION OF THE VARIABLE  - "<<name<<endl;
            }
            else{
                hashTable[idx].push_back({name,val});
            }
        }
    }
    SymbolTable* outerScope;
};

int isSubstring(const string line1, const string line2) {
    int i = 0;
    int j = 0;
    int m = line1.length();
    int n = line2.length();
    bool found = false;
    while (i < m && !found) {
        if (line1[i] == line2[j]) {
            i++;
            j++;
            while (i < m && j < n && line1[i] == line2[j]) {
                i++;
                j++;
            }
            if (j < n)
                j = 0;
            else
                found = true;
        } 
        else {
            i++;
        }
    }
    int ret_val = (found) ? i - n : -1;
    return ret_val;
}

bool findVariable(SymbolTable *currScope,string name,int &val){
    SymbolTable *scope = currScope;
    bool found = false;
    while(!found && scope){
        found = scope->find(name,val);
        if(!found)
            scope = scope->outerScope;
    }
    return found;
}

string getvariableName(string name,int &idx){
    string ans = "";
    while(idx < name.length() && name[idx] != ' '){
        ans += name[idx++];
    }
    return ans;
}

int getValue(string line,int idx){
    bool isneg = false;
    int ans = 0;
    if(line[idx] == '-'){
        isneg = true;
        idx++;
    }
    while(idx < line.length() && line[idx] != ' '){
        ans = (ans * 10) + (line[idx++] - '0');
    }
    if(isneg)
        ans *= -1;
    return ans;
}

int main()
{
    SymbolTable *currScope = NULL;
    ifstream inputcode("samplecode.txt");
    string line;
    string variableName;
    string value;
    int val;
    int idx;
    if(inputcode.is_open()){
        while(getline(inputcode,line)){
            if( (idx = isSubstring(line,Begin)) != -1){
                SymbolTable *newScope = new SymbolTable();
                newScope->outerScope = currScope;
                currScope = newScope;
            }
            else if( (idx = isSubstring(line,Assign)) != -1){
                idx += Assign.length() + 1;
                variableName = getvariableName(line,idx);
                int val = getValue(line,idx + 1);
                currScope->insert(variableName,val);
            }
            else if( (idx = isSubstring(line,Print)) != -1){
                idx += Print.length() + 1;
                variableName = getvariableName(line,idx);
                bool found = findVariable(currScope,variableName,val);
                if(found)
                    cout<<variableName<<" = "<<val<<endl;
                else
                    cout<<"IMPLICIT DECLARATION OF THE VARIABLE  - "<<variableName<<endl;
            }
            else if( (idx = isSubstring(line,End)) != -1){
                SymbolTable *exhaustedScope = currScope;
                currScope = currScope->outerScope;
                delete exhaustedScope;
            }
        }
    }

    inputcode.close();
    return 0;
}
