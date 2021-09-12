#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

char * Text= new char[25];  // Text variable contain Text sequence
char* pattern=new char[10]; // pattern variable contain Pattern sequence
int* flarray=new int[strlen(pattern)+1]; // failure array contain failure link of each node in pattern
char* prefix=new char[strlen(pattern)+1]; // prefix array contain each iteration prefix
char* Propersuffix=new char[strlen(pattern)-1]; // proper suffix array contain each iteration proper suffixes

//function of calc each iteration prefix
void getPrefix(int i_index,int j_index,char* prefix)
{
    int end_index=0;
    for(int i=i_index; i<j_index; i++)
    {
        prefix[i]=pattern[i];
        end_index=i;

    }
    prefix[end_index+1]='\0'; // put \0 at the end of each prefix to pretend garbage
}

//function of calc each iteration proper suffixes
int getPropersuffix(char * prefix)
{
    int max_index=0;
    int counter_pattern=0;
    for(int i=0; i<strlen(prefix)-1; i++) // number of proper suffix for each prefix = len(prefix) - 1
    {
        for(int j=i+1; j<strlen(prefix); j++) // number of char inside each proper suffix  = i+1
        {
            Propersuffix[i]=prefix[j];
            if(Propersuffix[i]==pattern[counter_pattern])
            {
                if(j==strlen(prefix)-1) // last char of  proper suffix == current counter of patter that mean current suffix match pattern
                {
                    max_index++;
                    return max_index;
                }
                max_index=counter_pattern+1;
                counter_pattern++;
            }
            else  // one char of proper suffix does not match one char of pattern
            {
                max_index=0;
                counter_pattern=0;
                break;
            }
        }
    }
    return max_index;
}

// function to calculate failure link of pattern
int* preprocessing(char* pattern)
{

    flarray[0]=-1;  // failure link of first node always equal -1

    for(int i=1; i<=strlen(pattern); i++)  // loop from node 1 to last node
    {
        getPrefix(0,i,prefix);
        if(i==1) //  node1 failure link always refer to first node
        {
            flarray[i]=0;
            continue;
        }
        int max_index=getPropersuffix(prefix);
        flarray[i]=max_index;
    }
    return flarray;
}
// function to report match between patter and text
void Search(char* Text,int* flarray,char* pattern)
{
    int i=0;
    int j=0;
    while(i<=strlen(Text)) // stop condition when index of i equal to length of text
    {
        if(Text[i]==pattern[j]) // char of text equal char of pattern
        {
            cout<<"t = "<<i<<" p = "<<j<<endl;
            i++;
            j++; // mover arrow of text and pattern
        }
        else // no match between char of text and char of pattern
        {

            if(j == strlen(pattern)) // report match when index of pattern reach last node of pattern and match at the same time
            {
                cout<<"t = "<<i<<" p = "<<j;
                cout<<" rep( "<<i-strlen(pattern)<<")"<<endl;
            }
            else
                cout<<"t = "<<i<<" p = "<<j<<endl;
            if(j==0) // no match and j at start of pattern then ---> move arrow of text
            {
                i++;
            }
            else
            {
                j=flarray[j]; // not match and j not at start of patter then ---> move pattern arrow of pattern to failure link of curnt index
            }
        }
    }
}
// general function of KMP
void KMP(char* Text,char *pattern)
{
    int* flarray = new int[10];
    flarray=preprocessing(pattern);
    Search(Text,flarray,pattern);
}
int main()
{
    Text="AGAGAAGAGGAGAAGAGAAGAGA";
    pattern="AGAAGAG";
    KMP(Text,pattern);
    return 0;
}
