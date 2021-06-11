#include<iostream>
#include<math.h>
#define N 3
using namespace std;
string ciphertext,decrypttext; 
int n;

void printarr(int *a,int r,int c)
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cout<<*((a+i*c)+j)<<" ";
        cout<<"\n";
    }
}

string encrypt(string s, int* a, int len){
    
    string text;
    int slen=s.length();
    for(int i=0;i<slen;i+=len)
    {
        for(int j=0;j<len;j++)
        {
            int l=0;
            for(int k=0;k<len;k++)
                l+=( *((a+k*len)+j) * (s[i+k]-'A') )%26;
                
            text+='A'+(l%26);
        }
    }
    return text;
}

int mod_inv(int a, int m){
    int m0 = m;
    int y = 0, x = 1;
    
    if (m == 1)
        return 0;
    a=a%m;
    
    if(a<0) a=a+m;

    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;
    return x;
}

int inv_d(int *a,int len){
    
    int temp[len*len-2*len+1],det=0;
    
    if(len==1) 
        return a[0];
    if (len==2) 
        return ((*a)*(*(a+3))-(*(a+1))*(*(a+2)));
    else
    {
        for(int i=0;i<len;i++)
        {
            int ctr=0;
            for(int j=0;j<len;j++)
            {
                for(int k=0;k<len;k++)
                {
                    if(k!=i && j!=0) 
                        temp[ctr++] = *(a+(len*j)+k);
                }
            }
            if(i%2==0) 
                det+=inv_d(temp,len-1)*(*(a+i));
            else 
                det-=inv_d(temp,len-1)*(*(a+i));
        }
        return det;
    }
}
string decrypt(string s, int *arr, int n) 
{
    int invkey[n][n];
    
    int D_inv = mod_inv(inv_d(arr, n), 26);
    cout<<D_inv;
    int temp[n*n-2*n+1],sn=1;
    
    for (int h=0;h<n;h++)
    {
        for(int i=0;i<n;i++)
        {
            if ((i+h)%2==1) 
                sn=-1;
            else 
                sn=1;
            
            int ctr=0;
            
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    if(k!=i && j!=h) 
                        temp[ctr++] = *(arr+(n*k)+j);
                }   
            }
            invkey[h][i]=((inv_d(temp,n-1)*sn)*D_inv)%26;
            
            if(invkey[h][i]<0) 
                invkey[h][i]+=26;
        }
    }

    cout<<"\n\n-------Inverse key------"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<invkey[i][j]%26<<' ';
        
        cout<<endl;
    }
    return encrypt(s,(int *) invkey, n);
}

int main(){
    
    string text;
    int n;
    
    cout<<"\nEnter the Plain Text :\t";
    cin>>text;
    
    cout<<"\nEnter the size of matrix :\t";
    cin>>n;
    
    int key[n][n];
    cout<<"\nEnter the key :\t";
    
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>key[i][j];

    ciphertext = encrypt(text,(int *) key, n);
    cout<<"\nCipher text :\t"<<ciphertext<<endl;
    decrypttext = decrypt(ciphertext, &key[0][0],n);
    cout<<"\nDecrypted text :\t"<<decrypttext<<endl;

    return 0;
}

