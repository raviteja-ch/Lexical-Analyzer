/* 
 * File:   Lex_A.cpp
 * Author: RaviTeja
 *
 * Created on November 12, 2015, 2:13 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <iterator>

using namespace std;

vector<string> res_word  = {"printf","==","<>","<",">","<=",">=",";",",",".","+","-","*","/","=","and","not","or","//","(",")","{","}","[","]","/*","*/","put","if","then","else","for","class","int","float","get","return","void","main"};
vector<string> op_pun_res;
vector<string> id;
vector<string> alphanum;
vector<string> num;
vector<string> err_token;
vector<string> fraction;

void token_identifier(string );

/*
 * 
 */
int main(int argc, char** argv) {
    string str,holder,log_ope ;
    char ch;
    char token[100];
    int j =0,len;
   std:: queue<string>  tok;
   std:: queue<string> operators;
    fstream myfile;
    myfile.open("hello.txt");
    if (myfile.is_open())
       
    while(myfile>>str)
    {
          len = strlen(str.c_str());
         
        while(j<len)
        {
            if(isalpha(str[j]) || isdigit(str[j]) || str[j]== '_' || str[j]=='.')
            {
                holder+=str[j];  
            }
            
            else if(str[j]=='/' && str[j+1]=='*')
            {
                
                myfile>>str;
                len = strlen(str.c_str());
                
                while (str[len-1]!='/' && str[len-2]!='*')
                {
                   
                    myfile>>str;
                    len = strlen(str.c_str());
                   
                }
                j=len;
            }
            
            else if(str[j]=='=' || str[j]=='<'  || str[j]=='>')
            {
                if(str[j+1]=='=' || str[j+1]=='<'  || str[j+1]=='>')
                {
                    log_ope= log_ope+str[j];
                    log_ope+=str[j+1];
                    operators.push(log_ope);
                    j=j+1;
                }
                else
                {
                    log_ope=str[j];
                    operators.push(log_ope);
                }
                 tok.push(holder);
                 holder.clear();
                 log_ope.clear();
            }
            
            else
            {
                log_ope=str[j];
                 operators.push(log_ope);
                 tok.push(holder);
                 holder.clear();
                 log_ope.clear();
            }
            
            j++;
        }
        j=0;
        tok.push(holder);
        holder.clear();
       
    }
   for (std::queue<string> dump = tok; !dump.empty(); dump.pop())
   {
       if(!dump.front().empty())
       {
        token_identifier(dump.front());
    //   std::cout << dump.front() << '\t';
       }
   }
   cout<<endl;
    for (std::queue<string> pump = operators; !pump.empty(); pump.pop())
    {
        token_identifier(pump.front());
    //    std::cout << pump.front() << '\t';
    }
   
   
   cout<<endl;
   cout<<"Operators and Reserves words :"<<endl;
     for(std::vector<string>::iterator it = op_pun_res.begin(); it !=op_pun_res.end();it++)
     {
         cout<<*it<<"\t";
     }
   cout<<endl;
   cout<<endl;
   cout<<"alphanum :"<<endl;
   for(std::vector<string>::iterator it = alphanum.begin(); it !=alphanum.end();it++)
     {
         cout<<*it<<"\t";
     }
   cout<<endl;
   cout<<endl;
   cout<<"num :"<<endl;
   for(std::vector<string>::iterator it = num.begin(); it !=num.end();it++)
     {
         cout<<*it<<"\t";
     }
   cout<<endl;
   cout<<endl;
   cout<<"id :"<<endl;
   for(std::vector<string>::iterator it = id.begin(); it !=id.end();it++)
     {
         cout<<*it<<"\t";
     }
   cout<<endl;
   cout<<endl;
   cout<<"error :"<<endl;
   for(std::vector<string>::iterator it = err_token.begin(); it !=err_token.end();it++)
     {
         cout<<*it<<"\t";
     }
   cout<<endl;
   cout<<endl;
   cout<<"fraction :"<<endl;
   for(std::vector<string>::iterator it = fraction.begin(); it !=fraction.end();it++)
     {
         cout<<*it<<"\t";
     }
   
    return 0;
}

void token_identifier(string tok)
{
    int len= strlen(tok.c_str());
    int op_res =0;
    for(std::vector<string>::iterator it = res_word.begin(); it !=res_word.end();it++)
    {
        if (tok==*it)
        {
            
            op_pun_res.push_back(tok);
            op_res=1;
        }
    }
    if(op_res==0)
    {
        if(len==1)
        {
            if( isdigit(tok[0]) || tok[0]== '_')
            {
                
                alphanum.push_back(tok);
            }
            else if (isalpha(tok[0]))
            {
               
                id.push_back(tok);
            }
            else
            {
               
                err_token.push_back(tok);
            }
        }
        
        
        else if(len>1)
        {
            int idflag=0;
            if(isalpha(tok[0]))                      // find id
            {
               
                id.push_back(tok);
                idflag=1;
            }
            
            int numfinder=0;
            for(int i=0;i<len;i++)
            {
                if(isdigit(tok[i]) || tok[i]=='.')
                {
                    
                }
                else
                    numfinder=1;
            }
            
            if(numfinder==0)                      //find num
            {
                if(tok[0]=='.')
            {
                fraction.push_back(tok);
            }
                else
                num.push_back(tok);
            }
            
            else
            {
                if(idflag!=1)
                err_token.push_back(tok);
            }
            
        }
        
        
        
        
    }
}