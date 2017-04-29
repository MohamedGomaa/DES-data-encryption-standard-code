#include<iostream>
using namespace std;

// These functions for keys generation

void keyGen (int key[], int genKey[]);
void shL1 (int arr[],int arrayLength);
void shL2 (int arr[],int arrayLength);
void pc1(int src[],int des[]);
void pc2(int src[],int des[]);
void concatinate (int arr[], int larr[], int rarr[], int subArrSize);
void devide (int arr[], int larr[], int rarr[],int arrayLength);
void printArr(int arr[],int arrSize);

//These functions for encoding
void encode(int plainText[],int cipherText[],int key[]);
void invIp(int src[],int des[]);
void ip(int src[],int des[]);
void expantion(int src[],int des[]);
void copyArr(int src[],int des[],int arrSize);
void xorr(int arr1[],int arr2[],int arrSize);
void functionn(int right[],int genKey[]);
void fixedP(int src[],int des[]);
void binaryConvert(int number,int arr[],int endr);

int main()
{
    int key[64] = {0,0,0,1,0,0,1,1, 0,0,1,1,0,1,0,0, 0,1,0,1,0,1,1,1, 0,1,1,1,1,0,0,1, 1,0,0,1,1,0,1,1, 1,0,1,1,1,1,0,0, 1,1,0,1,1,1,1,1, 1,1,1,1,0,0,0,1};
    int plainText[64] = {0,0,0,0, 0,0,0,1, 0,0,1,0, 0,0,1,1, 0,1,0,0, 0,1,0,1, 0,1,1,0, 0,1,1,1, 1,0,0,0, 1,0,0,1, 1,0,1,0, 1,0,1,1, 1,1,0,0, 1,1,0,1 ,1,1,1,0 ,1,1,1,1};
    int cipherText[64];
    cout<<"Plain text = ";
    printArr(plainText,64);
    encode(plainText,cipherText,key);
    cout<<"Cipher text = ";
    printArr(cipherText,64);
    return 0;
}

// These functions for keys generation

void keyGen (int key[], int genKey[],int keyNum)
{
    int c[28],d[28] ;
    devide(key,c,d,56);
    if(keyNum==0 || keyNum==1 || keyNum==8 || keyNum==15)
    {
        shL1(c,28);
        shL1(d,28);
    }
    else
    {
        shL2(c,28);
        shL2(d,28);
    }
    concatinate(key,c,d,28);
    pc2(key,genKey);
}
// These functions tp perform shifting right or left, per one or two bits
void shL1 (int arr[],int arrayLength)
{
    int temp = arr[0];
    for (int i = 0;i<arrayLength;i++)
    {
        arr[i] = arr[i+1];
    }
    arr[arrayLength-1] = temp;
}
void shL2 (int arr[],int arrayLength)
{
    int temp1,temp2;
    temp1= arr[0];
    temp2= arr[1];
    for (int i = 0;i<arrayLength-1;i++)
    {
        arr[i] = arr[i+2];
    }
    arr[arrayLength-2] = temp1;
    arr[arrayLength-1] = temp2;
}
void concatinate (int arr[], int larr[], int rarr[], int subArrSize)
{
    int coun=subArrSize;
    for(int i=0; i<subArrSize; i++)
    {
        arr[i] = larr[i];
        arr[coun] = rarr[i];
        coun++;
    }
}
void devide (int arr[], int larr[], int rarr[],int arrayLength)
{
    int middle,j;
    middle= arrayLength/2;
    j=0;
    for (int i=0 ;i<middle; i++)
    {
        larr[j] = arr[i];
        j++;
    }
    j=0;
    for (int i=middle ;i<arrayLength; i++)
    {
        rarr[j] = arr[i];
        j++;
    }
}
void pc1(int src[],int des[])
{
    int pc[56]= {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,
           23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
    for (int i=0;i<56;i++)
    {
        des[i] = src[pc[i]-1];
    }
}
void pc2(int src[],int des[])
{
    int pc[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49
                    ,39,56,34,53,46,42,50,36,29,32};
    for (int i=0;i<48;i++)
    {
        des[i] = src[pc[i]-1];
    }
}
void printArr(int arr[],int arrSize)
{
    for (int i=0; i<arrSize;i++)
    {
        cout<<arr[i];
    }
    cout <<endl;
}

//These functions for encoding
void encode(int plainText[],int cipherText[],int key[])
{
    int temp[64] ,primutedKey[56],l[32],r[32] , temp1[32];
    int genKey[48];

    pc1(key,primutedKey);
    ip(plainText,temp);
    cout<<"Primuted text = ";
    printArr(temp,64);
    devide(temp,l,r,64);

    for (int i=0 ;i<16;i++)
    {
        cout <<"l["<<i<<"]= ";
        printArr(l,32);
        cout <<"r["<<i<<"]= ";
        printArr(r,32);
        keyGen(primutedKey,genKey,i);
        cout <<"key["<<i<<"]= ";
        printArr(genKey,48);
        copyArr(l,temp1,32);
        copyArr(r,l,32);
        functionn(r,genKey);
        xorr(r,temp1,32);
    }
    concatinate(temp,r,l,32);
    invIp(temp,cipherText);
}
void invIp(int src[],int des[])
{
    int ip[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,
                    35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
    for (int i=0;i<64;i++)
    {
        des[i] = src[ip[i]-1];
    }
}
void ip(int src[],int des[])
{
    int ip[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17
                ,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    for (int i=0;i<64;i++)
    {
        des[i] = src[ip[i]-1];
    }
}
void expantion(int src[],int des[])
{
    int e[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,
                28,29,28,29,30,31,32,1};
    for (int i=0;i<48;i++)
    {
        des[i] = src[e[i]-1];
    }
}
void copyArr(int src[],int des[],int arrSize)
{
    for (int i=0;i<arrSize;i++)
    {
        des[i] = src[i];
    }
}
void xorr(int arr1[],int arr2[],int arrSize)
{
    for (int i=0 ; i<arrSize ; i++)
    {
        arr1[i]=((arr1[i]+arr2[i])%2);
    }
}
void functionn(int right[],int genKey[])
{
    int temp[48] ,temp1[32], j=3;
    int sBoxes[8][4][16] = {{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },


    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};
    expantion(right,temp);
    xorr(temp,genKey,48);
    for (int i=0;i<48;i+=6)
    {
        int row,col;
        row = (temp[i]*2) + temp[i+5];
        col = (temp[i+1]*8) + (temp[i+2]*4) +(temp[i+3]*2) +temp[i+4];
        cout <<"(row,col) = "<<row<<","<<col<<" = "<<sBoxes[i/6][row][col]<<endl;
        binaryConvert(sBoxes[i/6][row][col],temp1,j);
        j+=4;
    }
    fixedP(temp1,right);
}
void fixedP(int src[],int des[])
{
    int p[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
    for (int i=0;i<32;i++)
    {
        des[i] = src[p[i]-1];
    }
}
void binaryConvert(int number,int arr[],int endr)
{
    arr[endr]=0;
    arr[endr-1]=0;
    arr[endr-2]=0;
    arr[endr-3]=0;
    while(number > 0) {
        int bin = number % 2;
        number /= 2;
        arr[endr]=bin;
        endr--;
    }
}
