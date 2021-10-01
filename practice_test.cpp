#include<bits/stdc++.h>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<deque>
#include<list>
#include<set>
#include<vector>
#include<iostream>
#define ll long long
#define re register
#define inf 0x7f7f7f7f
#define inl inline
#define sqr(x) (x*x)
#define max(a,b) (a>b?a:b)
#define mp(a,b) make_pair(a,b)
#define eps 1e-8
#define debug puts("**************************");
//#pragma comment(linker, "/STACK:1024000000,1024000000")
//#pragma GCC optimize (2)
//#pragma G++ optimize (2)
using namespace std;
//const ll mod;
//const ll MAXN;
inl ll read() {
    re ll x = 0; int f = 1;
    char ch = getchar();
    while(ch<'0'||ch>'9') { if(ch == '-' ) f = -1; ch = getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x * f;
}
inl char readc() {
    re char ch=getchar();
    while(('z'<ch||ch<'a')&&('Z'<ch||ch<'A')) ch=getchar();
    return ch;
}
void write(ll x){
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}
inl void writeln(ll x){
    if(x<0) {x=-x;putchar('-');}
    write(x); puts("");
}
inl ll gcd(re ll x,re ll y) {while(y^=x^=y^=x%=y);return x;}
inl ll Lcm(re ll a,re ll b) {return a/gcd(a,b)*b;}
inl void FR() {
    freopen("data.txt","r",stdin);
    freopen("1.out","w",stdout);
}
inl void FC() {
    fclose(stdin);
    fclose(stdout);
}

//省略字 
char FILTER[4]={' ','\t','\r','\n'};
//分隔符 
char SEPARATER[8]={';',',','{','}','[',']','(',')'};
//运算符
char OPERATOR[8]={'+','-','*','/','>','<','=','!'};
string OTHER_OPERATOR[12]={"&&","||","!=","==","<<",">>"
							"+=","-=","*=","/=",">=","<="};
bool IsFilter(char ch){
    for(re ll i=0;i<4;i++) {
        if(FILTER[i]==ch) {return true;}
    }
    return false;
}

//小写字母 
bool IsLowLetter(char ch){return ch>='a' && ch<='z';}
//大写字母 
bool IsUpLetter(char ch){return ch>='A' && ch<='Z';}
//数字 
bool IsDigit(char ch){return ch>='0' && ch<='9';}

//关键字
string KEYWORD[18]={"int","char","double","float","void",
					"#define","#include","if","else","return",
					"while","for","do","break","continue",
					"scanf","printf","getchar"};
bool IsKeyword(string word){
    for(re ll i=0;i<18;i++){
        if(KEYWORD[i]==word){return true;}
    }
    return false;
}

//每个符号的编号 
template <class T>
ll value(T *a,ll n,T str){
	for(re ll i=0;i<n;i++){
		if(a[i] == str) return i+1;
	}
	return -1;
}

const ll IDENTIFIER=100;//标识符
const ll CONSTANT=101;//常量
const ll FILTER_VALUE=102;//省略符 

void build() {
	
}

//回退 
char flag;
char getc() {
	char ch;
	if(flag) {ch=flag,flag=0;return ch;}
	else return ch=getchar();
}

queue<char>Q;
void work() {
	char ch;string arr;flag=0;
	while(~(ch=getc())) {
		arr = "";
		if(IsFilter(ch)) continue ;//忽略字
		else if(IsLowLetter(ch)||ch == '#') {
			while(IsLowLetter(ch)||ch == '#') {arr += ch;ch = getc();}
            if(IsKeyword(arr)) {
            	ll t = value(KEYWORD,18,arr);
            	printf("%3d    ",t);
				cout<<arr<<"  关键字"<<endl;
                if(t==16||t==17) {
                	while(!Q.empty()) Q.pop();
                	while((ch=getc())!='(');
                	while((ch = getc())!=')') {Q.push(ch);}
                	string ar;ar.clear();
                	char chx=Q.front();Q.pop();
                	while(chx!='"') {chx=Q.front();Q.pop();}
                	ar.push_back(chx);chx=Q.front();Q.pop();
                	while(chx!='"') {ar.push_back(chx=Q.front());Q.pop();}
                	if(t==16) cout<<"输入";
                	else cout<<"输出";
                	cout<<ar<<endl;
				}
			}
			else {
                printf("%3d    ",IDENTIFIER);
                cout<<arr<<"  标识符"<<endl;
            }
            flag=ch;
		}
		else if(IsDigit(ch)) {           //判断是否为数字
            while(IsDigit(ch)) {
                arr += ch;
                ch = getc();
                if(ch == '.') {arr += ch;ch = getc();}
            }
            flag=ch;
            printf("%3d    ",CONSTANT);
            cout<<arr<<"  整形数"<<endl;
        }
		else if(IsUpLetter(ch)||ch == '_'){
            while(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'||IsDigit(ch)){
                arr += ch;
                ch=getc();
            }
            flag=ch;
            printf("%3d    ",IDENTIFIER);
            cout<<arr<<"  标识符"<<endl;
        }
        else {
        	char ch2 = getc();
        	if(ch2=='<'||ch2=='>'||ch2== '='||ch2=='&'||ch2=='|') {
        		arr += ch;arr+=ch2;
        		for(re ll i=0;i<12;i++) {
        			if(OTHER_OPERATOR[i]==arr) {
        				printf("%3d    ",
						value(OTHER_OPERATOR,12,arr));
		                cout<<arr<<"  运算符"<<endl;
					}
				}
			}
        	else {
        		flag = ch2;
        		switch(ch){
			        case '+':
			        case '-':
			        case '*':
			        case '/':
			        case '>':
			        case '<':
			        case '=':
			        case '!':
			            {
			                arr += ch;
			                printf("%3d    ",value(OPERATOR,8,*arr.data()));
			                cout<<arr<<"  运算符"<<endl;
			                break;
			            }
			        case ';':
			        case ',':
			        case '(':
			        case ')':
			        case '[':
			        case ']':
			        case '{':
			        case '}':
			            {
			              arr += ch;
			              printf("%3d    ",value(SEPARATER,8,*arr.data()));
			              cout<<arr<<"  分隔符"<<endl;
			              break;
			            }
			        default :cout<<"\""<<ch<<"\":无法识别的字符！"<<endl;
		        }
			}
		}
	}
}
int main() {
//  FR();
	build();
	work();
//  FC();
    return 0;
}
