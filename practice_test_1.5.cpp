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
#define debug puts("ERROR");
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
    freopen("2.out","w",stdout);
}
inl void FC() {
    fclose(stdin);
    fclose(stdout);
}

//省略字 
char FILTER[4]={' ','\t','\r','\n'};
//分隔符 
char SEPARATER[9]={';',',','{','}','[',']','(',')','"'};
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

//回退 
char flag;
char getc() {
	char ch;
	if(flag) {ch=flag,flag=0;return ch;}
	else return ch=getchar();
}

struct zifu {
	ll bh;
	string type;//GUANJIANZI,BIAOSHIFU,SHUZI,YUNSUANFU,FENGEFU,UNKNOWN
	string name;
	zifu(ll t=0,string a="",string b="") {
		bh=t;type=a;name=b;
	}
};
queue<zifu>Q;

void get_Q() {//拆分 
	char ch;string arr;flag=0;
	while(~(ch=getc())) {
		arr = "";
		if(IsFilter(ch)) continue ;//忽略字
		else if(IsLowLetter(ch)||ch == '#') {
			while(IsUpLetter(ch)||IsLowLetter(ch)
			||ch=='_'||IsDigit(ch)||ch=='.'||ch=='#') 
			{arr += ch;ch = getc();}
            if(IsKeyword(arr)) {
            	ll t = value(KEYWORD,18,arr);
				Q.push(zifu(t,"GUANJIANZI",arr));
			}
			else {
                Q.push(zifu(-1,"BIAOSHIFU",arr));
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
            Q.push(zifu(CONSTANT,"SHUZI",arr));
        }
		else if(IsUpLetter(ch)||ch == '_'){
            while(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'||IsDigit(ch)){
                arr += ch;ch = getc();
            }
            flag = ch;
            Q.push(zifu(IDENTIFIER,"BIAOSHIFU","arr"));
        }
        else {
        	char ch2 = getc();
        	if(ch2=='<'||ch2=='>'||ch2== '='||ch2=='&'||ch2=='|') {
        		arr += ch;arr+=ch2;
        		for(re ll i=0;i<12;i++) {
        			if(OTHER_OPERATOR[i]==arr) {
        				ll t=value(OTHER_OPERATOR,12,arr);
		                Q.push(zifu(t,"YUNSUANFU",arr));
						break ;
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
			                arr += ch;ll t=value(OPERATOR,8,*arr.data());
			                Q.push(zifu(t,"YUNSUANFU",arr));
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
			        case '"':
			            {
			              arr += ch;ll t=value(SEPARATER,9,*arr.data());
			              Q.push(zifu(t,"FENGEFU",arr));
			              break;
			            }
			        default :{
			        	arr+=ch;
			        	Q.push(zifu(-1,"UNKNOWN",arr));
						break;
					}
		        }
			}
		}
	}
}
void check_Q() {
	while(!Q.empty()) {
		zifu a=Q.front();Q.pop();
		cout<<"编号："<<a.bh<<endl;
		cout<<"TYPE:"<<a.type<<endl;
		cout<<"NAME:"<<a.name<<endl;
	}
}

ll Node_cnt;
struct Node {
	string type;
	string content;
	ll children_num;
	ll id;
	ll depth;ll width;
	vector<ll>children;
	void clear(){
		id=children_num=depth=width=0;
		type.clear();content.clear();
		children.clear();
	}
	Node() {clear();}
};
vector<Node>node;
ll condition(ll dep,ll wid,string a) {
	
}
ll biaodashi(ll dep,ll wid,string a) {
	
}
ll dfs(ll dep,ll wid,zifu a) {
	ll t=++Node_cnt;Node x;
	x.id=t;node.push_back(x);
	if(a.type=="GUANJIANZI") {//关键字
		switch(a.bh) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: {//数据类型申明 
				
				break;
			}
			case 6: {//define
				
				break;
			}
			case 7: {//include
				
				break;
			}
			case 8: {//if
				
				break;
			}
			case 9: {//else
				
				break;
			}
			case 10: {//return
				
				break;
			} 
			case 11: {//while
				
				break;
			}
			case 12: {//for
				
				break;
			}
			case 13: {//do
				
				break;
			}
			case 14: {//break
				
				break;
			}
			case 15: {//continue
				
				break;
			}
			case 16: {//scanf
				
				break;
			} 
			case 17: {//printf
				
				break;
			}
			case 18: {//getchar
				
				break;
			}
		}
	}
	else if(a.type=="BIAOSHIFU") {
		
	}
	return t;
}
void solve() {
	Node rt;rt.clear();
	while(!Q.empty()) {
		Node p;
		ll t=++rt.children_num;
		zifu a=Q.front();Q.pop();
		rt.children.push_back(0);
		rt.children[t]=dfs(1,t,a);
	}
}
int main() {
  FR();
	get_Q();/*check_Q();*/
	solve();
//  FC();
    return 0;
}
