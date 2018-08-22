#include<bits/stdc++.h>
using namespace std;

vector < pair<string ,pair <string , pair <string , string> > > > data;
string starting_address;
string temp;
string arr[65536] ;
string carry_flag,zero_flag;
char mode = 'w';
string reg[7];
string prog_counter[100];
int xy = 1;


int opcode_check(string str)
{
    
    map<string,int>g1;
    g1.insert(pair<string,int>("MOV",1));
    g1.insert(pair<string,int>("MVI",2));
    g1.insert(pair<string,int>("LXI",3));
    g1.insert(pair<string,int>("LDA",3));
    g1.insert(pair<string,int>("STA",3));
    g1.insert(pair<string,int>("LHLD",3));
    g1.insert(pair<string,int>("SHLD",3));
    g1.insert(pair<string,int>("STAX",1));
    g1.insert(pair<string,int>("XCHG",1));
    g1.insert(pair<string,int>("ADD",1));
    g1.insert(pair<string,int>("ADI",2)); 
    g1.insert(pair<string,int>("SUB",1)); 
    g1.insert(pair<string,int>("INR",1));
    g1.insert(pair<string,int>("DCR",1));
    g1.insert(pair<string,int>("INX",1));
    g1.insert(pair<string,int>("DCX",1));
    g1.insert(pair<string,int>("DAD",1));
    g1.insert(pair<string,int>("SUI",2)); 
    g1.insert(pair<string,int>("CMA",1));
    g1.insert(pair<string,int>("CMP",1));
    g1.insert(pair<string,int>("JMP",3));
    g1.insert(pair<string,int>("JC",3));
    g1.insert(pair<string,int>("JNC",3));
    g1.insert(pair<string,int>("JZ",3));
    g1.insert(pair<string,int>("JNZ",3));
    g1.insert(pair<string,int>("HLT",0));
    
    if(g1.find(str) != g1.end())
    {
        return g1[str];
    }
    else
    {
        return -1;
    }
}

int hexToDec(string str)
{
    int y;
    stringstream stream;
    stream << str;
    stream >> hex >> y;
    return y;
}

string decToHex(int num)
{
    stringstream stream;
    stream << hex << num;
    return stream.str();
}

void func_SET(string O1 , string O2)
{
    int y = hexToDec(O1);
    int x = hexToDec(O2);
    if(y > 0 && y < 65536)
    {
        if(x >= 0 && x < 256)
        {
            arr[y] = O2;
        }
        else
        {
            cout << "The value entered is out of range " << endl;
        }
    }
    else
    {
        cout << "The address entered is out of range" << endl;
    }
}

int seperate(string str )   //return a value to main if encounters HLT
{
    int i,j,len=str.length();
    string t , s;
    for(i=0;i<len;i++)
    {
        if(str[i]!=32)
        {
            t=t+str[i];
        }
        else
        {
            for(int j=i+1;j<len;j++)
            {
                s=s+str[j];
            }
            break;   
        }
    }
    int le = s.length();
    string te ,se;
    for(i=0;i<le;i++)
    {
        if(s[i]!=32)
        {
            te=te+s[i];
        }
        else
        {
            for(int j=i+1; j<=le-1;j++)
            {
                se=se+s[j];
            }
            break;   
        }
    }
    if(t == "SET")
    {
        func_SET(te , se);
    }
    else
    {
        int x = opcode_check(t);
        if(x > 0)
        { 
            data.push_back(make_pair(temp , make_pair(t,make_pair(te ,se))));
            int random , value;
            random = hexToDec(temp);
            value = random + x;
            temp = decToHex(value);
            return 1;
        }
        else
        {
            return x;
        }
    }
}

void prog_count(string temp , string memo)
{
    int random , value;
    random = hexToDec(temp);
    int x = opcode_check(memo);
    if(x != -1)
    value = random + x;
    prog_counter[xy++] = decToHex(value);
}

void func_LDA(string O1 , string O2)
{
    int new_address = hexToDec(O1);
    string input;
    int l = O1.length();
    if(O2.length() == '\0' && l == 4)
    {
        if( (new_address > 0 && new_address < 65536))
        {
            cout << "Enter value at " << O1 << endl;
            cin >> input;
            if(hexToDec(input) >= 0 && hexToDec(input) < 256)
            {
                arr[new_address] = input ;
            }
            else
            {
                cout << "The value entered is out of range" << endl; 
            }
            reg[0] = arr[new_address];
            if(mode == 'r')
            {
                cout << reg[0] << endl;
            }
        }
        else
        {
            cout << "The operand entered for LDA command is invalid " << endl ;
        }
    }   
    else
    {
        cout << "THE SYNTAX ENTERED FOR THE LDA COMMAND IS INCORRECT " << endl;
    }
}

void func_STA(string O1 , string O2)
{
    int new_address = hexToDec(O1);
    int l = O1.length();
    if(O2.length() == '\0' && l == 5)
    {
        if( (new_address > 0 && new_address < 65536))
        {
            
            arr[new_address] = reg[0]  ;
            if(mode == 'w')
            {
                cout <<"VALUE AT " << O1 << " IS : " << arr[new_address] << endl;
            }
        }
        else
        {
            cout << "The operand entered for STA command is invalid " << endl ;
        }
    }   
    else
    {
        cout << "THE SYNTAX ENTERED FOR THE STA COMMAND IS INCORRECT " << endl;
    }
}

void func_LHLD(string O1 , string O2)
{
    int new_address = hexToDec(O1) , new_address1;
    string input , input1;
    int l = O1.length();
    if(O2.length() == '\0' && l == 4)
    {
        if( (new_address > 0 && new_address < 65536))
        {
            cout << "Enter value at " << O1 << endl;
            cin >> input;
            new_address1 = new_address + 1;
            if( (new_address1 > 0 && new_address1 < 65536))
            {
                cout << "Enter value at " << decToHex(new_address1) << endl;
                cin >> input1;
                if((hexToDec(input) >= 0 && hexToDec(input) < 256) && (hexToDec(input1) >= 0 && hexToDec(input1) < 256))
                {
                    reg[6] = input;
                    reg[5] = input1;
                }
                else
                {
                    cout << "The value entered is out of range" << endl; 
                }
                if(mode == 'r')
                {
                    cout << "Value in regiter L is " << reg[6]<< endl;
                    cout << "Value in regiter H is " << reg[5]<< endl;
                }
            }
            else
            {
                cout << "The operand entered for LHLD command is invalid " << endl ;
            }
        }
        else
            {
                cout << "The operand entered for LHLD command is invalid " << endl ;
            }
    }
    else
    {
        cout << "THE SYNTAX ENTERED FOR THE LHLD COMMAND IS INCORRECT " << endl;
    }
}

void func_SHLD(string O1 , string O2)
{
    int new_address = hexToDec(O1) , new_address1;
    int l = O1.length();
    if(O2.length() == '\0' && l == 4)
    {
        if( (new_address > 0 && new_address < 65536))
        {
            new_address1 = new_address + 1;
            if( (new_address1 > 0 && new_address1 < 65536))
            {
                arr[new_address] =  reg[6];
                arr[new_address1] = reg[5];
                if(mode == 'w')
                {
                    cout << "Value in address " << O1 <<" is " << reg[6]<< endl;
                    cout << "Value in address " <<  decToHex(new_address1)  <<" is " << reg[5]<< endl;
                }
            }
            else
            {
                cout << "The operand entered for SHLD command is invalid " << endl ;
            }
        }   
        else
        {
            cout << "The operand entered for SHLD command is invalid " << endl ;
        }
    }
    else
    {
        cout << "THE SYNTAX ENTERED FOR THE SHLD COMMAND IS INCORRECT " << endl;
    }
}

void func_STAX(string O1 , string O2)
{
    int l = O1.length();
    string B , C;
    if(O2.length() == '\0' && l == 1)
    {
        if(O1 == "H" || O1 == "B" || O1 == "D")
        {
            if(O1 == "H")
            {
                B = reg[5];
                C = reg[6];
            }
            if(O1 == "B" || O1 == "D" )
            {
                B = reg[O1[0] - 'A'];
                C = reg[O1[0] - 'A'];   
            }
            if(B.length() == 2 && C.length() == 2)
            {
                if((hexToDec(B) >=0 && hexToDec(B)<=255) && (hexToDec(C) >=0 && hexToDec(C)<=255) )
                {
                    string x = B + C;
                    int new_address = hexToDec(x);
                    if( (new_address > 0 && new_address < 65536))
                    {
                        arr[new_address] = reg[0];
                        if(mode == 'r')
                        {
                            cout << "value at " << x <<"is :" << arr[new_address] << endl;
                        }
                    }
                    else
                    {
                        cout << "The value of the register contains is invalid " << endl;
                    }
                }
            }
            else
            {
                cout << "The operand entered no value  " << endl ;
            }
        }
        else
        {
            cout << "The operand entered is invalid " << endl ;
        }
    }   
    else
    {
        cout << "THE SYNTAX ENTERED FOR THE STAX COMMAND IS INCORRECT " << endl;
    }
}

void func_XCHG(string O1 , string O2)
{
    if(O1.length() == '\0' && O2.length() == '\0')
    {
        string t1;
        t1 = reg[6];
        reg[6] = reg[4];
        reg[4] = t1;
        t1 = reg[5];
        reg[5] = reg[3];
        reg[3] = t1;
    }
    else
    {
        cout << "THE SYNTAX ENTERED FOR THE XCHG COMMAND IS INCORRECT " << endl;
    }
}

void func_LXI(string O1 , string O2)
{
    string B , C;
    if(O1.length() == 1 && O2.length() == 4)
    {
        if(O1 == "H" || O1 == "B" || O1 == "D")
        {
            if(hexToDec(O2) > 0 && hexToDec(O2) <= 65536)
            {
                B = O2.substr( 0 ,2);
                C = O2.substr(2 , 2);
            }
            else
            {
                cout << "The memory of register pair does not exist " << endl;
            }
            if(O1 == "H")
            {
                reg[5] = B;
                reg[6] = C;
                //cout << reg[5] <<reg[6] << endl;
            }
            if(O1 == "B" || O1 == "D" )
            {
                reg[O1[0] - 'A'] = B;
                reg[O1[0] + 1 - 'A'] = C;
                //cout<< reg[O1[0] - 'A']<<reg[O1[0] + 1 - 'A']<<endl;
            }
        }
        else
        {
            cout << "The register pair defined does not exist" << endl;
        }
    }
    else
    {
        cout << "The syntax entered for the LXI commmand is invalid" << endl;
    }
}

void func_ADD(string o1 , string o2)  //change in add function is required and memory function
{
    //cout << o1 << o1.length() << endl;
    string input;
    if((o1 == "A" || o1 == "B" || o1 == "C" || o1 == "D" || o1 == "E" || o1 == "H" || o1 == "L" || o1 == "M") && (o2.length() == '\0'))
    {
        if(o1 == "B" || o1 == "C" || o1 == "D" || o1 == "E")
        {
            input = reg[o1[0] - 'A'];
        }
        if(o1 == "H")
        {
            input = reg[5];
        }
        if(o1 == "L")   
        {
            input = reg[6];
        }
        if (o1=="A")
        {
            input = reg[0];
            int y=hexToDec(reg[0]);
            int z=y+y;
            string t = decToHex(z);
            if(t.length() > 2)
                t.erase(0,1);
            //cout<<t<<endl;
            reg[0] = t;
        }
            if(hexToDec(input) > 0 && hexToDec(input) < 256 && (o1 != "M"))
            {
                int x = hexToDec(input);
                int y = hexToDec(reg[0]);
                int z = x + y;
                string t = decToHex(z);         
                if(t.length() > 2)
                {
                    t.erase(0 , 1);
                }
                //cout<<t<<endl;
                reg[0] = t;   
            }
            else
            {
                cout << "The value entered is out of range " << endl; 
            }
        
        if(o1 == "M")
        {
            string r = reg[5] + reg[6];
            int x = hexToDec(r);
            string s = arr[x];
            int q = hexToDec(s);
            int y = hexToDec(reg[0]);
            int z = q + y;
            string t = decToHex(z);
            if(t.length() > 2)
                t.erase(0,1);
            reg[0] = t;
        }
    }
    else
    {
        cout<<"The operand for ADD command is invalid"<<endl;
    }
}

void func_INR(string o1 , string o2)
{
    string random;
    if((o1=="A" || o1=="B" || o1=="C" || o1=="D" || o1=="E" || o1=="H" || o1=="L" || o1=="M") && (o2.length() =='\0'))
    {
        if(o1 != "H" || o1 != "L" || o1 != "M")
        {
            string temp = reg[o1[0] - 'A'];
            temp = reg[0];
            int x = hexToDec(temp);
            x = x + 1;
            if(x == 256)
                random = decToHex(0);
            else
                random = decToHex(x);
            reg[o1[0] - 'A'] = random;
            reg[0] = random;
        }
        if(o1 == "H")
        {
            string temp = reg[5];
            int x = hexToDec(temp);
            x = x + 1;
            if(x == 256)
                random = decToHex(0);
            else
                 random = decToHex(x);
            reg[5] = random;  
        }
        if(o1 == "L")
        {
            string temp = reg[6];
            int x = hexToDec(temp);
            x = x + 1;
            if(x == 256)
                random = decToHex(0);
            else
                random = decToHex(x);
            reg[6] = random; 
        }
        if(o1 == "M" )
        {
            string x;
            x = reg[5] + reg[6];
            if(hexToDec(x) > 0 && hexToDec(x) < 65536)
            {
                int y = hexToDec(arr[hexToDec(x)]);
                y = y+1;
                if(y == 256)
                    random = decToHex(0);
                else
                    random = decToHex(y);
                arr[hexToDec(x)] = random; 
            }
            else
            {
                cout << "The value of memory location is not specified" << endl;
            }
        }
    }
    else
    {
        cout << "The syntax for INR command is invalid" << endl;
    }
}

void func_DCR(string o1 , string o2)
{
    string random;
    if((o1=="A" || o1=="B" || o1=="C" || o1=="D" || o1=="E" || o1=="H" || o1=="L" || o1=="M") && (o2.length() =='\0'))
    {
        if(o1 != "H" || o1 != "L" || o1 != "M")
        {
            string temp = reg[o1[0] - 'A'];
            int x = hexToDec(temp);
            if(x == 0 || x > 255)
                cout << "Value cannot be decremented" << endl;
            else
            {
                x = x - 1;
                random = decToHex(x);
                reg[o1[0] - 'A'] = random;
            }
        }
        if(o1 == "H")
        {
            string temp = reg[5];
            int x = hexToDec(temp);
            if(x == 0 || x > 255)
                cout << "Value cannot be decremented" << endl;
            else
            {
                x = x - 1;
                random = decToHex(x);
                reg[5] = random;
            }  
        }
        if(o1 == "L")
        {
            string temp = reg[6];
            int x = hexToDec(temp);
            if(x == 0 || x > 255)
                cout << "Value cannot be decremented" << endl;
            else
            {
                x = x - 1;
                random = decToHex(x);
                reg[6] = random;
            } 
        }
        if(o1 == "M" )
        {
            string x;
            x = reg[5] + reg[6];
            if(hexToDec(x) > 0 && hexToDec(x) < 65536)
            {
                int y = hexToDec(arr[hexToDec(x)]);
                if(y == 0 || y > 255)
                    cout << "Value cannot be decremented" << endl;
                else
                {
                    y = y - 1;
                    random = decToHex(y);
                    arr[hexToDec(x)] = random; 
                }
            }
            else
            {
                cout << "The value of memory location is not specified" << endl;
            }
        }
    }
    else
    {
        cout << "The syntax for INR command is invalid" << endl;
    }
}

void func_ADI(string o1 , string o2)
{
    int x = hexToDec(o1);
    if((x > 0 && x < 256) && (o2.length()=='\0'))
    {
        
        int y=hexToDec(reg[0]);
        int z=x+y;
        string t =decToHex(z);
        int n=t.length();
        if(n>2)
        {
            t.erase(0,1);
        }
        //cout<<t<<endl;
        reg[0] = t;
    }
    else
    {
        cout<<"The syntax entered for ADI command is invalid"<<endl;
    }
}

void func_SUB(string o1 , string o2) //change in sub function is required and memory function
{
    string input;
    if((o1 == "A" || o1 == "B" || o1 == "C" || o1 == "D" || o1 == "E" || o1 == "H" || o1 == "L" || o1 == "M") && o2.length() == '\0')
    {
        if(o1 == "B" || o1 == "C" || o1 == "D" || o1 == "E")
        {
            input = reg[o1[0] - 'A'];
        }
        if(o1 == "H")
        {
            input = reg[5];
        }
        if(o1 == "L")   
        {
            input = reg[6];
        }
         if (o1=="A")
        {
            input = reg[0];/*
            int y=hexToDec(reg[0]);
            int z=y-y;
            reg[0] = "0";*/
            //cout<<"0"<<endl;
        } 

            if(hexToDec(input) > 0 && hexToDec(input) < 256 && (o1!="M"))
            {
                int x = hexToDec(input);
                int y = hexToDec(reg[0]);
                int z = y - x;
                string t = decToHex(z);         
                if(t.length() > 2)
                {
                    t.erase(0 , 1);
                }
                //cout<<t<<endl;
                reg[0] = t;
            }
            else
            {
                cout << "The value entered is out of range" << endl; 
            }
          
        if(o1=="M")
        {
            string r=reg[5] + reg[6];
            int x=hexToDec(r);
            string s=arr[x];
            int q=hexToDec(s);
            int y=hexToDec(reg[0]);
            int z=y-q;
            string t=decToHex(z);
            if(t.length() > 2)
                t.erase(0,1);
            reg[0] = t;
            //cout<<t<<endl;
        }
    }
    else
    {
        cout<<"The operand for SUB command is invalid"<<endl;
    }
}

void func_SUI(string o1 , string o2)
{
    int len=o1.length();
    int x=hexToDec(o1);
    if((len<=2 && o2.length()=='\0') && (x > 0 && x < 256))
    {
        
        int y=hexToDec(reg[0]);
        int z=y-x;
        string t =decToHex(z);
        int n=t.length();
        if(t.length() > 2)
        {
            t.erase(0 , 1);
        }
       // cout<<t<<endl;
        reg[0] = t;
    }
    else
    {
        cout<<"The syntax entered for SBI command is invalid"<<endl;
    }
}

void func_CMP(string o1 , string o2)
{
    if((o1=="A" || o1=="B" || o1=="C"  || o1=="D"  || o1=="E" || o1=="M") && o2.length() =='\0')
    {
        if(o1=="A")
        {
            //int x=reg[0]-reg[0];
            zero_flag="1";
        }
        if(o1=="B" || o1=="C" || o1=="D" || o1=="E")
        {
            string input;
            cout<<"Enter value in "<<o1<<endl;
            cin>>input;
            if(hexToDec(input)>=0 && hexToDec(input)<256)
            {
                if(hexToDec(input)<=hexToDec(reg[0]))
                {
                    zero_flag="0";
                    if(hexToDec(input)<hexToDec(reg[0]))
                    {    
                        carry_flag = "0";
                    }
                }
                if(hexToDec(input)>hexToDec(reg[0]))
                {
                    carry_flag="1";
                }

            }
            else
            {
                cout<<"The value entered is out of range"<<endl;
            }
        }
        if(o1=="M")
        {
            string x = reg[5] + reg[6];
            if(hexToDec(x) > 0 && hexToDec(x) < 65536)
           {
                if(hexToDec(arr[hexToDec(x)])<=hexToDec(reg[0]))
                {
                    zero_flag="0";
                    if(hexToDec(arr[hexToDec(x)])<hexToDec(reg[0]))
                    {    
                        carry_flag = "0";
                    }
                }
                if(hexToDec(arr[hexToDec(x)])>hexToDec(reg[0]))
                {
                    carry_flag="1";
                }
            }
            else
            {
                cout << "The value of memory location is not specified" << endl;
            }
        }
        
    }
    else
    {
         cout<<"The syntax entered for CMP command is invalid"<<endl;
    }
}

void func_DAD(string o1 , string o2)
{
    if((o1=="B" || o1=="D" || o1=="H") && o2.length()=='\0')
    {
        if(o1=="B")
        {
            reg[6]= decToHex(hexToDec(reg[6])+hexToDec(reg[2]));
            if(reg[6].length()>2)
            {
                reg[6].erase(0,1);
                reg[5]=hexToDec(reg[5])+hexToDec(reg[1])+1;
                if(reg[5].length()>2)
                {
                    reg[5].erase(0,1);
                }
            }
            else
            {
                reg[5]=decToHex(hexToDec(reg[5])+hexToDec(reg[1]));
                if(reg[5].length()>2)
                {
                    reg[5].erase(0,1);
                }
            }
        }
        if(o1=="D")
        {
            reg[6]=decToHex(hexToDec(reg[6])+hexToDec(reg[4]));
            if(reg[6].length()>2)
            {
                reg[6].erase(0,1);
                reg[5]=hexToDec(reg[5])+hexToDec(reg[3])+1;
                if(reg[5].length()>2)
                {
                    reg[5].erase(0,1);
                }
            }
            else
            {
                reg[5]=decToHex(hexToDec(reg[5])+hexToDec(reg[3]));
                if(reg[5].length()>2)
                {
                    reg[5].erase(0,1);
                }
            }
        }
        if(o1=="H")
        {
            reg[6] = decToHex(hexToDec(reg[6])+hexToDec(reg[6]));
            if(reg[6].length()>2)
            {
                reg[6].erase(0,1);
                reg[5]=hexToDec(reg[5])+hexToDec(reg[5])+1;
                if(reg[5].length()>2)
                {
                    reg[5].erase(0,1);
                }
            }
            else
            {
                reg[5] = decToHex(hexToDec(reg[5])+hexToDec(reg[5]));
                if(reg[5].length()>2)
                {
                    reg[5].erase(0,1);
                }
            }
        }
    }
    else
    {
        cout<<"The syntax entered for DAD command is invalid"<<endl;
    }
}

int func_JMP(string O1 , string O2)
{
    int i = 0;
    int new_address = hexToDec(O1);
    int l = O1.length();
    if(O2.length() == '\0' && l == 4)
    {
        if( (new_address > 0 && new_address < 65536))
        {
            std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
            for( it = data.begin(); it < data.end(); it++)
            {
                if(O1 == (*it).first)
                {
                    /*cout << "Match found" << endl;
                    cout << "Jump at address " << (*it).first << endl;
                    cout << "Address at prog_counter = " << prog_counter[i] << endl;*/
                    return i;
                    break;
                }
                else
                {
                    i++; 
                }
            }
        }
    }
}

int func_JC(string O1 , string O2)
{
    if(carry_flag == "1")
    {
        int i = 0;
        int new_address = hexToDec(O1);
        int l = O1.length();
        if(O2.length() == '\0' && l == 4)
        {
            if( (new_address > 0 && new_address < 65536))
            {
                std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
                for( it = data.begin(); it < data.end(); it++)
                {
                    if(O1 == (*it).first)
                    {
                        /*cout << "Match found" << endl;
                        cout << "Jump at address " << (*it).first << endl;
                        cout << "Address at prog_counter = " << prog_counter[i] << endl;*/
                        return i;
                        break;
                    }
                    else
                    {
                        i++; 
                    }
                }
            }
        }
    }
    else
    {
        cout << "Cannot jump as carry flag is reset " << endl;
    }
}

int func_JNC(string O1 , string O2)
{
    if(carry_flag == "0")
    {
        int i = 0;
        int new_address = hexToDec(O1);
        int l = O1.length();
        if(O2.length() == '\0' && l == 4)
        {
            if( (new_address > 0 && new_address < 65536))
            {
                std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
                for( it = data.begin(); it < data.end(); it++)
                {
                    if(O1 == (*it).first)
                    {
                        /*cout << "Match found" << endl;
                        cout << "Jump at address " << (*it).first << endl;
                        cout << "Address at prog_counter = " << prog_counter[i] << endl;*/
                        return i;
                        break;
                    }
                    else
                    {
                        i++; 
                    }
                }
            }
        }
    }
    else
    {
        cout << "Cannot jump as carry flag is set " << endl;
    }
}

int func_JZ(string O1 , string O2)
{
    if(zero_flag == "1")
    {
        int i = 0;
        int new_address = hexToDec(O1);
        int l = O1.length();
        if(O2.length() == '\0' && l == 4)
        {
            if( (new_address > 0 && new_address < 65536))
            {
                std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
                for( it = data.begin(); it < data.end(); it++)
                {
                    if(O1 == (*it).first)
                    {
                        /*cout << "Match found" << endl;
                        cout << "Jump at address " << (*it).first << endl;
                        cout << "Address at prog_counter = " << prog_counter[i] << endl;*/
                        return i;
                        break;
                    }
                    else
                    {
                        i++; 
                    }
                }
            }
        }
    }
    else
    {
        cout << "Cannot jump as zero flag is reset " << endl;
    }
}

int func_JNZ(string O1 , string O2)
{
    if(zero_flag == "0")
    {
        int i = 0;
        int new_address = hexToDec(O1);
        int l = O1.length();
        if(O2.length() == '\0' && l == 4)
        {
            if( (new_address > 0 && new_address < 65536))
            {
                std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
                for( it = data.begin(); it < data.end(); it++)
                {
                    if(O1 == (*it).first)
                    {
                        /*cout << "Match found" << endl;
                        cout << "Jump at address " << (*it).first << endl;
                        cout << "Address at prog_counter = " << prog_counter[i] << endl;*/
                        return i;
                        break;
                    }
                    else
                    {
                        i++; 
                    }
                }
            }
        }
    }
    else
    {
        cout << "Cannot jump as carry flag is set " << endl;
    }
}

void func_CMA(string o1 , string o2)
{
    if(o1.length()=='\0' && o2.length()=='\0')
    {
        if(reg[0]=="0")
        reg[0]="ff";
        else if(reg[0]=="ff" || reg[0]=="FF")
        reg[0]="0";
        else
        {
            reg[0]=decToHex(255-hexToDec(reg[0]));
        }
    }
    else
    {
        cout<<"The syntax entered for CMA command is invalid"<<endl;
    }
}

void func_INX(string o1 , string o2)
{
    if((o1=="B" || o1=="D" || o1=="H") && o2.length()=='\0')
    {
        if(o1=="B" && o2.length()=='\0')
        {
            if(reg[2]=="FF" || reg[2]=="ff")
            {
                reg[2]="0";
                reg[1]=decToHex(hexToDec(reg[1])+1);
            }
            else
            {
                reg[2]=decToHex(hexToDec(reg[2])+1);
            }
        }
        if(o1=="D" && o2.length()=='\0')
        {
            if(reg[4]=="FF" || reg[4]=="ff")
            {
                reg[4]="0";
                reg[3]=decToHex(hexToDec(reg[3])+1);
            }
            else
            {
                reg[4]=decToHex(hexToDec(reg[4])+1);
            }
        }
        if(o1=="H" && o2.length()=='\0')
        {
            if(reg[6]=="FF" || reg[6]=="ff")
            {
                reg[6]="0";
                reg[5]=decToHex(hexToDec(reg[5])+1);
            }
            else
            {
                reg[6]=decToHex(hexToDec(reg[6])+1);
            }
        }
    }
    else
    cout<<"The command entered for INX command is invalid"<<endl;
}

void func_MOV(string O1 , string O2)
{
    if(O1.length() == O2.length() )
    {
        if(O1 == "M" )
        {
            string xx;
            xx = reg[5] + reg[6];
            if(hexToDec(xx) > 0 && hexToDec(xx) < 65536)
            {
                int yx = hexToDec(xx);
                arr[yx] = reg[0];
            }
            else
            {
                cout << "The value of memory location is not specified" << endl;
            }
        }
        if(O1 == "A" || O1 == "B" || O1 == "C" || O1 == "D" || O1 == "E" && (O2 == "A" || O2 == "B" || O2 == "C" || O2 == "D" || O2 == "E"))
        {
            if(O1 != O2)
            {
                reg[O1[0] - 'A'] = reg[O2[0] - 'A'];
                cout << reg[O1[0] - 'A'] ;
            }
            else
            {
                cout << "The given registers are same error occuered" << endl;
            }
        }
        if(O1 == "A" || O1 == "B" || O1 == "C" || O1 == "D" || O1 == "E" || O1 == "L" && (O2 == "H"))
        {
            if(O1 == "L")
            {
                reg[6] = reg[5];
            }
            else
            {
                reg[O1[0] - 'A'] = reg[5];    
            }
        }
        if(O1 == "A" || O1 == "B" || O1 == "C" || O1 == "D" || O1 == "E" || O1 == "H" && (O2 == "L"))
        {
            if(O1 == "L")
            {
                reg[5] = reg[6];
            }
            else
            {
                reg[O1[0] - 'A'] = reg[6];    
            }
        }
    }
    else
    {
        cout << "The Syntax of the MOV command is invalid" << endl;
    }
    //cout << reg[1] << endl;   
    //cout << reg[2] << endl;
}

void func_MVI(string O1 , string O2)
{
    int flag = 0;
    int x = hexToDec(O2);
    if(x > 0 && x < 256)
    {
            flag  = 1;
    }
    else
    {
        cout << "The value entered is out of range " << endl;
    }
    if(O1 == "A" || O1 == "B" || O1 == "C" || O1 == "D" || O1 == "E" || O1 == "H" || O1 == "L" || O1 == "M")
    {
        if(O1 == "A" || O1 == "B" || O1 == "C" || O1 == "D" || O1 == "E")
        {
            if((flag == 1) && (O1.length()== 1))
            {
                reg[O1[0] - 'A'] = O2;  
                cout << O1 << reg[O1[0] - 'A'] << endl;
            }
        }
        if(O1 == "L")
        {
            if((flag == 1) && (O1.length()== 1))
            {
                reg[6] = O2;    
            }
        }
        if(O1 == "H")
        {
            if((flag == 1) && (O1.length()== 1))
            {
                reg[5] = O2;    
            }
        }
        if(O1 == "M" )
        {
            string xx;
            xx = reg[5] + reg[6];
            if(hexToDec(xx) > 0 && hexToDec(xx) < 65536)
            {
                x = hexToDec(xx);
                if((flag == 1) && (O1.length()== 1))
                {
                    arr[x] = O2;    
                }
            }
            else
            {
                cout << "The value of memory location is not specified" << endl;
            }
        }
    }
    else
    {
        cout<<"The syntax entered for MVI command is invalid"<<endl;
    }
}

void func_DCX(string o1 , string o2)
{
    if((o1=="B" || o1=="D" || o1=="H") && o2.length()=='\0')
    {
        if(o1=="B" && o2.length()=='\0')
        {
            if(reg[2]=="0")
            {
                reg[2]="ff";
                reg[1]=decToHex(hexToDec(reg[1])-1);
            }
            else
                reg[2]=decToHex(hexToDec(reg[2])-1);
         }
        if(o1=="D" && o2.length()=='\0')
        {
            if(reg[4]=="0")
            {
                reg[4]="ff";
                reg[3]=decToHex(hexToDec(reg[3])-1);
            }
            else
                reg[4]=decToHex(hexToDec(reg[4])-1);
         }
        if(o1=="H" && o2.length()=='\0')
        {
            if(reg[6]=="0")
            {
                reg[6]="ff";
                reg[5]=decToHex(hexToDec(reg[5])-1);
            }
            else
                reg[6]=decToHex(hexToDec(reg[6])-1);
        }
        cout<<reg[5]<<" "<<reg[6]<<endl;

    }
    else
    cout<<"The command entered for DCX command is invalid"<<endl;
}

int execute_one(vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it , int n , int z)
{
    for(it = data.begin(); it < data.end(); it++)
    {
            if((*it).second.first == "LDA" && (prog_counter[z] == (*it).first))
            {
                func_LDA((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "STA" && (prog_counter[z] == (*it).first))
            {
                func_STA((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "LHLD" && (prog_counter[z] == (*it).first))
            {
                func_LHLD((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "SHLD" && (prog_counter[z] == (*it).first))
            {
                func_SHLD((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "ADD" && (prog_counter[z] == (*it).first))
            { 
                func_ADD((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "ADI" && (prog_counter[z] == (*it).first))
            {
                func_ADI((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "SUB" && (prog_counter[z] == (*it).first))
            {
                func_SUB((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "SUI" && (prog_counter[z] == (*it).first))
            {
                func_SUI((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "INR" && (prog_counter[z] == (*it).first))
            {
                func_INR((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "DCR" && (prog_counter[z] == (*it).first))
            {
                func_DCR((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "STAX" && (prog_counter[z] == (*it).first))
            {
                func_STAX((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "XCHG" && (prog_counter[z] == (*it).first))
            {
                func_XCHG((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "LXI" && (prog_counter[z] == (*it).first))
            {
                func_LXI((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "CMP" && (prog_counter[z] == (*it).first))
            {
                func_CMP((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "DAD" && (prog_counter[z] == (*it).first))
            {
                func_DAD((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "CMA" && (prog_counter[z] == (*it).first))
            { 
                func_CMA((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "INX" && (prog_counter[z] == (*it).first))
            { 
                func_INX((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "DCX" && (prog_counter[z] == (*it).first))
            { 
                func_DCX((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "MOV" && (prog_counter[z] == (*it).first))
            { 
                func_MOV((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "MVI" && (prog_counter[z] == (*it).first))
            { 
                func_MVI((*it).second.second.first , (*it).second.second.second);
                return -1;
            }
            else if((*it).second.first == "JMP" && (prog_counter[z] == (*it).first))
            { 
                int YC = func_JMP((*it).second.second.first , (*it).second.second.second);
                return YC;
            }
            else if((*it).second.first == "JC" && (prog_counter[z] == (*it).first))
            {    
                int YC = func_JC((*it).second.second.first , (*it).second.second.second);
                return YC;   
            }
            else if((*it).second.first == "JNC" && (prog_counter[z] == (*it).first))
            { 
                int YC = func_JNC((*it).second.second.first , (*it).second.second.second);
                return YC;
            }
            else if((*it).second.first == "JZ" && (prog_counter[z] == (*it).first))
            { 
                int YC = func_JZ((*it).second.second.first , (*it).second.second.second);
                return YC;
            }
            else if((*it).second.first == "JNZ" && (prog_counter[z] == (*it).first))
            { 
                int YC = func_JNZ((*it).second.second.first , (*it).second.second.second);
                return YC;
            }  
    }
}

void execute_direct()
{
    std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
    it = data.begin();
    for(int z  = 0 ; z < xy - 1 ;)
    {
            int x = execute_one(it , 1 , z); 
            if(x != -1)
                z = x;
            else
                z = z+1;
           // cout << z << " " << x << " ";
    }
}

void custom_input(string str)
{
    ifstream Fin;
    Fin.open(str);
    string txt;
    /*cout << "Enter the starting address" << endl;         //If you want user to input the starting address then we can use custom input 
    getline (cin , starting_address);*/                    //else read starting address from the file
    getline(Fin, starting_address);
    temp = starting_address;
    prog_counter[0] = starting_address;
    do
    {
        getline(Fin, txt);
        //cout<<txt << endl;
        int abc = seperate(txt);
        if(abc == -1)
        {
            cout << "THE MEMONICS ENTERED IS INCORRET PROGRAM TERMINATED" << endl;
            break;
        }  
    }while(txt[0] != 'H');
    Fin.close();
    std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
    for(it = data.begin(); it < data.end(); it++)
    {
        prog_count((*it).first , (*it).second.first);
    }
    for( it = data.begin(); it < data.end(); it++)
    {
        cout << (*it).first << " " << (*it).second.first << " " << (*it).second.second.first << " "  << (*it).second.second.second << endl;
    }
}

void user_input()
{
    string str ;
    int i = 0,count = 0;
    cout << "Enter the starting address" << endl;
    getline (cin , starting_address);
    if(hexToDec(starting_address) > 0 && hexToDec(starting_address) < 65536)
    {
        temp = starting_address;
        prog_counter[0] = starting_address;
        do
        {
            getline(cin,str);
            count  = count + 1;
            // pair< string , pair<string,string> > g2;
            int abc = seperate(str );
            //cout << i << endl;
            /*if(abc == 0)
            {
                cout <<"PROGRAM TERMINATED AS END OF PROGRAM HLT HAS BEEN ENCOUNTERED" << endl;
                break;
            }*/
            if(abc == -1)
            {
                cout << "THE MEMONICS ENTERED IS INCORRET PROGRAM TERMINATED" << endl;
                break;
            }
        }while(str[0] != 'H');
        std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
        for(it = data.begin(); it < data.end(); it++)
        {
            prog_count((*it).first , (*it).second.first);
        }
    }
    else
    {
        cout << "The address entered is out of range" << endl;
    }
}

void debugger()
{
    std::vector< pair<string ,pair <string , pair <string , string> > > > :: iterator it;
    string input;
    it = data.begin();
    int z = 0 , z1 =0;
    int n , temp = 0 , xyz;
    do
    {
        getline(cin , input);
        if(input[0] =='h')
        {
            cout << "break or b with line number to decide the break point of the program in the debugger mode"<<endl;
            cout << "The main function of the break is to assign the break point to the given program" << endl;
            cout << "There can be multiple break point in the program " << endl;
            cout << endl;
            cout << "run or r is used to run the program until the break point of the program has been encounted" << endl;
            cout << "giving this command once will run the program till the first break point" << endl;
            cout << endl;
            cout << "step or s command is going to run the program line by line " << endl;
            cout << "execution of the program is done line by line only" << endl;
            cout << endl;
            cout << "print or p is used  to print the value in the memory or the registers" << endl;
            cout << "The printing format for registers is p A and for address is p x2500" << endl;
            cout << endl;
            cout << "quit or q command will be used to quit the debugger mode" << endl;
        }
        else if(input[0] == 's')        
        {
            if(z < xy)
            {
                int x = execute_one(it , 1 , z); 
                if(x != -1)
                    z = x;
                else
                    z = z+1;
            }
            else
            {
                cout << "The program has terminated no more commands left " << endl;
            }
        }
        else if(input[0] == 'b')
        {
            if(input.length() == 7 || input.length() == 8)
            {
                input.erase(0 , 6);
            }
            else if(input.length() == 3 || input.length() == 4)
            {
                input.erase(0 , 2);
            }
            stringstream geek(input);
            geek >> n;
        }
        else if(input[0] == 'r')
        {
            xyz = n - temp;
            while(xyz--)
            {
                if(z1 < xy)
                {
                    int x = execute_one(it , 1 , z1); 
                    if(x != -1)
                        z1 = x;
                    else
                        z1 = z1+1;
                }
                else
                {
                    cout << "The program has terminated no more commands left " << endl;
                }
            }
            temp = n;
        }
        else if(input[0] == 'p')
        {
            if(input.length()==7 && input[1]=='r')
            {
                input.erase(0,6);
            }
            if(input.length() == 11)
            { 
                input.erase(0,7);
            }
            if(input.length()==3)
            {
                input.erase(0,2);
            }
            if(input.length()==7 && input[1]==32)
            {
                input.erase(0,3);
            }
            int x=hexToDec(input);
            if(arr[x].length()=='\0')
            {
                cout<<"No Value exists int he specified memory loacation"<<endl;
            }
            else
            {
                cout<<arr[x]<<endl;
            }
        }   
        else
        {
            cout << "Invalid choice" << endl;
        }
    }while(input[0] != 'q');
}

int main(int argc, char *argv[])
{

    if(argc == 1)                   //simple execution of the program through user input
    {
        
            user_input();
            execute_direct();
    }
    else if(argc == 2)              //either there is an input file or we have to take input from the user and run in debugger mode
    {
        string ab = argv[1];
        if(ab == "--debugger")
        {
            user_input();
            //debugger();
        }
        else
        {
            string abc = argv[1];
            custom_input(abc);
            execute_direct();
        }
        
    }
    else if(argc == 3)              //the user wants to run the input file in debugger mode
    {

        //cout<<argv[0]<<argv[1]<<argv[2]<<endl; 
        string ab = argv[1];
        if(ab == "--debugger")
        {
            string abc = argv[2];
            custom_input(abc);
            //debugger();
        }
        else
        {
            cout << "Invalid Arguments passed" << endl;
        }
    }
    else
    {
        cout << "Invalid Number of Arguments" << endl;
    }
    return 0;
}

