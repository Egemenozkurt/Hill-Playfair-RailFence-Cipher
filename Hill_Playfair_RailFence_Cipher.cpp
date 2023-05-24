#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<bits/stdc++.h>
using namespace std;

typedef struct{
	int row;
	int col;
}position;

char mat[5][5];

void generateMatrix(string key){
    int flag[26] = {0};
    int x = 0, y = 0;

    for(int i=0; i<key.length(); i++){
        if(key[i] == 'j') key[i] = 'i';

        if(flag[key[i]-'a'] == 0){
            mat[x][y++] = key[i];
            flag[key[i]-'a'] = 1;
        }
        if(y==5) x++, y=0;
    }

    for(char ch = 'a'; ch <= 'z'; ch++){
        if(ch == 'j') continue;
        if(flag[ch - 'a'] == 0){
            mat[x][y++] = ch;
            flag[ch - 'a'] = 1 ;
        }
        if(y==5) x++, y=0;
    }
}

string formatMessage(string msg){
    for(int i=0; i<msg.length(); i++){
        if(msg[i] == 'j')  msg[i] = 'i';
    }

    for(int i=1; i<msg.length(); i+=2){
        if(msg[i-1] == msg[i])  msg.insert(i, "x");
    }
    
    if(msg.length()%2 != 0)  msg += "x";
    return msg;
}

position getPosition(char c){
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(c == mat[i][j]){
                position p = {i, j};
                return p;
            }
}

string encrypt(string message){
    string ctext = "";
    for(int i=0; i<message.length(); i+=2){
		position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;
    
        if( x1 == x2 ){
            ctext +=  mat[x1][(y1+1)%5];
            ctext +=  mat[x2][(y2+1)%5];
        }
        else if( y1 == y2 ){
            ctext += mat[ (x1+1)%5 ][ y1 ];
            ctext += mat[ (x2+1)%5 ][ y2 ];
        }
        else{
            ctext += mat[ x1 ][ y2 ];
            ctext += mat[ x2 ][ y1 ];
        }
    }
    return ctext;
}


string Decrypt(string message){
    string ptext = "";
    for(int i=0; i<message.length(); i+=2) {
        position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;

        if( x1 == x2 ){
            ptext += mat[x1][ --y1<0 ? 4: y1 ];
            ptext += mat[x2][ --y2<0 ? 4: y2 ];
        }
        else if( y1 == y2 ){
            ptext += mat[ --x1<0 ? 4: x1 ][y1];
            ptext += mat[ --x2<0 ? 4: x2 ][y2];
        }
        else{
            ptext += mat[ x1 ][ y2 ];
            ptext += mat[ x2 ][ y1 ];
        }
    }
    return ptext;
}

void playfair(){
    string plaintext, key;
    cout << "Enter the message to encrypt: ";
    cin >> plaintext;
    cout<< "Enter key: ";
    cin >> key;
    generateMatrix(key);
    cout << "Key Matrix:" << endl;
    for(int k=0;k<5;k++){
        for(int j=0;j<5;j++){
            cout << mat[k][j] << "  ";
        }
        cout << endl;
    }
    cout << "Entered text: " << plaintext << endl;
    string fmsg = formatMessage(plaintext);
    string ciphertext = encrypt(fmsg);
    cout << "Cipher text after applying playfair cipher: " << ciphertext << endl;
    string decryptmsg = Decrypt(ciphertext);
    cout<< "Decrypted Message: " << decryptmsg << endl;
}

void hillCipher(){
    int x,y,i,j,k,n;
    cout<<"Enter the size of key matrix: ";
    cin>>n;
    cout<<"Enter the key matrix\n";
    int a[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    cout<<"Enter the message to encrypt: ";
    string s;
    cin>>s;
    int temp = (n-s.size()%n)%n;
    for(i=0;i<temp;i++){
        s+='x';
    }
    k=0;
    string ans="";
    while(k<s.size()){
        for(i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += (a[i][j]%26*(s[temp++]-'a')%26)%26;
                sum = sum%26;
            }
            ans+=(sum+'a');
        }
        k+=n;
    }
	cout<<"Entered text: "<<s<<endl;
    cout<<"Cipher text after applying hill cipher: "<<ans<<endl;
}

void railFenceCipher(){
    int key,i,j = 0;
    string original;
    cout<<"Enter the message to encrypt: ";
    cin>>original;
    cout<<"Enter the key: ";
    cin>>key;
    vector<vector<char>> a(key,vector<char>(original.size(),' '));
    int flag=0;
    for(i=0;i<original.size();i++){
        a[j][i] = original[i];
         if(j==key-1){
            flag=1;
        }
        else if(j==0)
            flag=0;
        if(flag==0){
            j++;
        }
        else j--;
    }
	cout<<"Entered text: "<<original<<endl;
    cout<<"Cipher text after applying rail fence: ";
    for(i=0;i<key;i++){
        for(j=0;j<original.size();j++){
            if(a[i][j]!=' ')
                cout<<a[i][j];
        }
    }
    cout<<'\n';   
}

int main(){
    int choice;

    cout<<"Enter 1 for Playfair \n";
	cout<<"Enter 2 for Hill Cipher \n";
	cout<<"Enter 3 for Rail Fence Cipher \n";
    cin>>choice;
    switch(choice){
        case 1:playfair();
                break;
        case 2:hillCipher();
                break;
        case 3:railFenceCipher();
                break;
        default:cout<<"You did not enter 1, 2, or 3!\n";
    }
    return 0;
}