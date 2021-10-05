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
//#define debug puts("ERROR");
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
        	if(ch=='/'&&ch2=='/') {/*printf("单行注释\n");*/
				char chx=getc();
        		while(chx!='\n') chx=getc();
			}
        	else if(ch=='/'&&ch2=='*') {
        		/*printf("多行注释\n");*/
				char chx=getc(),chy=getc();
        		while(chx!='*'||chy!='/') {
        			chx=chy,chy=getc();
				}
			}
        	else if((ch=='<'&&ch2=='<')||(ch=='>'&&ch2=='>')||
			((ch=='>'||ch=='<'||ch=='=')&&ch2== '=')
			||(ch=='&'&&ch2=='&')||(ch=='|'&&ch2=='|')) {
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

queue<zifu>Q_s;//处理内容 
ll biaodashi(ll dep,ll wid) {
	ll t=Node_cnt++;Node n_x;
	n_x.id=t;n_x.depth=dep;n_x.width=wid;
	node.push_back(n_x);
	node[t].type="BIAODASHI";
	while(!Q_s.empty()) {
		zifu x=Q_s.front();Q_s.pop();
		node[t].content+=x.name+" ";
	}
	return t;
}
ll condition(ll dep,ll wid) {
	ll t=Node_cnt++;Node n_x;
	n_x.id=t;n_x.depth=dep;n_x.width=wid;
	node.push_back(n_x); 
	node[t].type="con_dition";
	node[t].content="条件：";
	while(!Q_s.empty()) {
		zifu x=Q_s.front();Q_s.pop();
		node[t].content+=x.name+" ";
	}
	return t;
}
ll dfs(ll dep,ll wid,zifu a) {
	queue<zifu>Q_d;//单层处理内容 
	ll t=Node_cnt++;Node n_x;
	n_x.id=t;n_x.depth=dep,n_x.width=wid;
	node.push_back(n_x);
	if(a.type=="GUANJIANZI") {//关键字
		switch(a.bh) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: {//数据类型申明 	
				while(!Q_d.empty()) Q_d.pop();
				zifu x=Q.front();Q.pop();
				while(x.name!="("&&x.name!=";") {
					if(x.type!="FENGEFU") {Q_d.push(x);}
					x=Q.front();Q.pop();
				}
				if(x.name==";") {
					node[t].type="create_bianliang";
					node[t].content=a.name;
					/*cout<<node[t].type<<node[t].content<<endl;*/
					while(!Q_d.empty()) {
						zifu as=Q_d.front();Q_d.pop();
						ll cntt=node[t].children_num++;
						node[t].children.push_back(0);
						ll tt=Node_cnt++;
						Node ssx;node.push_back(ssx);
						node[t].children[cntt]=tt;node[tt].type="BIANLIANG";
						node[tt].content=as.name;node[tt].id=tt;
						node[tt].depth=dep+1;node[tt].width=wid+tt;
						/*cout<<node[tt].type<<node[tt].content<<endl;*/
					}
				}
				else {
					node[t].type="create_hanshu";
					node[t].content=a.name;
					/*cout<<node[t].type<<node[t].content<<endl;*/
					while(!Q_d.empty()) {
						zifu as=Q_d.front();Q_d.pop();
						ll cntt=node[t].children_num++;
						node[t].children.push_back(0);
						ll tt=Node_cnt++;
						Node ssx;node.push_back(ssx);
						node[t].children[cntt]=tt;node[tt].type="HANSHU";
						node[tt].content=as.name;node[tt].id=tt;
						node[tt].depth=dep+1;node[tt].width=wid+tt;
						/*cout<<node[tt].type<<node[tt].content<<endl;*/
						zifu sa=Q.front();Q.pop();
						if(sa.name!=")") {
							zifu sb=Q.front();Q.pop();
							while(sa.type=="GUANJIANZI"&&sb.type=="BIAOSHIFU") {
								ll stt=Node_cnt++;node[tt].children_num++;
								node[tt].children.push_back(stt);
								Node tmp;node.push_back(tmp);
								node[stt].type="BIANLIANG";node[stt].content=sb.name;node[stt].id=stt;
								node[stt].depth=node[tt].depth+1;node[stt].width=node[stt].width+stt;
								/*cout<<sa.name<<"变量"<<sb.name<<endl;*/
								zifu sx=Q.front();Q.pop();
								if(sx.name==")") break ;
								else {sa=Q.front();Q.pop();sb=Q.front();Q.pop();}
							}
						}
						sa=Q.front();Q.pop();
						if(sa.name==";") break ;
						else if(sa.name=="{") {
							ll stt=Node_cnt++;node[tt].children_num++;
							node[tt].children.push_back(stt);
							Node tmp;node.push_back(tmp);
							node[stt].type="function_body";node[stt].content="";node[stt].id=stt;
							node[stt].depth=node[tt].depth+1;node[stt].width=node[tt].width+stt;
							sa=Q.front();Q.pop();
							while(sa.name!="}") {
								ll sstt=node[stt].children_num++;
								node[stt].children.push_back(0);
								ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
								node[stt].children[sstt]=temp_d;
								sa=Q.front();Q.pop();
								/*cout<<node[stt].children[sstt]<<endl;
								cout<<sa.name<<endl;
								cout<<node[node[stt].children[sstt]].type<<endl;*/
							}
						}
					}
				}
				break;
			}
			case 6: {//define
				zifu x=Q.front();Q.pop();
				zifu y=Q.front();Q.pop();
				node[t].type="define";
				node[t].content=x.name+" "+y.name;
				/*cout<<x.name<<' '<<y.name<<endl;*/
				break;
			}
			case 7: {//include
				node[t].type="include";
				zifu x=Q.front();Q.pop();
				while(x.type=="YUNSUANFU") {x=Q.front();Q.pop();}
				node[t].content=x.name;
				/*cout<<"#include"<<"<"<<x.name<<">"<<endl;*/
				x=Q.front();Q.pop();
				break;
			}
			case 8: {//if
				node[t].type="i_f";
				node[t].content="条件：";
				zifu x=Q.front();Q.pop();
				while(!Q_s.empty()) Q_s.pop();
				x=Q.front();Q.pop();
				while(x.name!=")") {
					Q_s.push(x);
					node[t].content+=x.name+" ";
					x=Q.front();Q.pop();
				}
				ll st=node[t].children_num++;
				node[t].children.push_back(0);
				ll temp_d=condition(n_x.depth+1,n_x.width);
				node[t].children[st]=temp_d;
				zifu sa=Q.front();Q.pop();
				if(sa.name==";") break ;
				else if(sa.name=="{") {
					ll stt=Node_cnt++;node[t].children_num++;
					node[t].children.push_back(stt);
					Node tmp;node.push_back(tmp);
					node[stt].type="if_body";node[stt].content="";node[stt].id=stt;
					node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
					sa=Q.front();Q.pop();
					while(sa.name!="}") {
						ll sstt=node[stt].children_num++;
						node[stt].children.push_back(0);
						ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
						node[stt].children[sstt]=temp_d;
						sa=Q.front();Q.pop();
						/*cout<<node[stt].children[sstt]<<endl;
						cout<<sa.name<<endl;
						cout<<node[node[stt].children[sstt]].type<<endl;*/
					}
				}
				break;
			}
			case 9: {//else
				zifu x=Q.front();Q.pop();
				node[t].content="";
				if(x.name=="if") {
					node[t].type="else_if";
					zifu x=Q.front();Q.pop();
					while(!Q_s.empty()) Q_s.pop();
					x=Q.front();Q.pop();
					while(x.name!=")") {
						Q_s.push(x);
						node[t].content+=x.name+" ";
						x=Q.front();Q.pop();
					}
					ll st=node[t].children_num++;
					node[t].children.push_back(0);
					ll temp_d=condition(n_x.depth+1,n_x.width);
					node[t].children[st]=temp_d;
					zifu sa=Q.front();Q.pop();
					if(sa.name==";") break ;
					else if(sa.name=="{") {
						ll stt=++Node_cnt-1;node[t].children_num++;
						node[t].children.push_back(stt);
						Node tmp;node.push_back(tmp);
						node[stt].type="else_if_body";node[stt].content="";node[stt].id=stt;
						node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
						sa=Q.front();Q.pop();
						while(sa.name!="}") {
							ll sstt=node[stt].children_num++;
							node[stt].children.push_back(0);
							ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
							node[stt].children[sstt]=temp_d;
							sa=Q.front();Q.pop();
							/*cout<<node[stt].children[sstt]<<endl;
							cout<<sa.name<<endl;
							cout<<node[node[stt].children[sstt]].type<<endl;*/
						}
					}
				}
				else {
					node[t].type="else";zifu sa=x;
					if(sa.name==";") break ;
					else if(sa.name=="{") {
						ll stt=Node_cnt++;node[t].children_num++;
						node[t].children.push_back(stt);
						Node tmp;node.push_back(tmp);
						node[stt].type="else_body";node[stt].content="";node[stt].id=stt;
						node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
						sa=Q.front();Q.pop();
						while(sa.name!="}") {
							ll sstt=node[stt].children_num++;
							node[stt].children.push_back(0);
							ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
							node[stt].children[sstt]=temp_d;
							sa=Q.front();Q.pop();
							/*cout<<node[stt].children[sstt]<<endl;
							cout<<sa.name<<endl;
							cout<<node[node[stt].children[sstt]].type<<endl;*/
						}
					}
				}
				break;
			}
			case 10: {//return
				node[t].type="return";
				node[t].content="";
				while(!Q_s.empty()) Q_s.pop();
				zifu x=Q.front();Q.pop();
				while(x.name!=";") {
					Q_s.push(x);node[t].content+=x.name+" ";
					x=Q.front();Q.pop();
				}
				ll stt=node[t].children_num++;
				node[t].children.push_back(0);
				ll temp_d=biaodashi(dep+1,wid);
				node[t].children[stt]=temp_d;
				break;
			} 
			case 11: {//while
				node[t].type="while";
				node[t].content="";
				while(!Q_s.empty()) Q_s.pop();
				zifu x=Q.front();Q.pop();
				while(x.name=="(") x=Q.front(),Q.pop();
				while(x.name!=")") {
					Q_s.push(x);
					node[t].content+=x.name+" ";
					x=Q.front();Q.pop();
				}
				ll stt=node[t].children_num++;
				node[t].children.push_back(0);
				ll temp_d=condition(dep+1,wid);
				node[t].children[stt]=temp_d;
				zifu sa=Q.front();Q.pop();
				if(sa.name==";") break ;
				else if(sa.name=="{") {
					stt=Node_cnt++;node[t].children_num++;
					node[t].children.push_back(stt);
					Node tmp;node.push_back(tmp);
					node[stt].type="else_if_body";node[stt].content="";node[stt].id=stt;
					node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
					sa=Q.front();Q.pop();
					while(sa.name!="}") {
						ll sstt=node[stt].children_num++;
						node[stt].children.push_back(0);
						ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
						node[stt].children[sstt]=temp_d;
						sa=Q.front();Q.pop();
						/*cout<<node[stt].children[sstt]<<endl;
						cout<<sa.name<<endl;
						cout<<node[node[stt].children[sstt]].type<<endl;*/
					}
				}
				break;
			}
			case 12: {//for
				node[t].type="for";
				node[t].content="";
				zifu x=Q.front();Q.pop();
				while(x.name=="(") x=Q.front(),Q.pop();
				while(x.name!=";") {
					node[t].content+=x.name+" ";
					x=Q.front();Q.pop();
				} 
				x=Q.front();Q.pop();
				while(!Q_s.empty()) Q_s.pop(); 
				while(x.name!=";") {Q_s.push(x);x=Q.front();Q.pop();}
				ll stt=node[t].children_num++;
				node[t].children.push_back(0);
				ll temp_d=condition(dep+1,wid);
				node[t].children[stt]=temp_d;
				
				x=Q.front();Q.pop();
				while(!Q_s.empty()) Q_s.pop(); 
				while(x.name!=")") {Q_s.push(x);x=Q.front();Q.pop();}
				stt=node[t].children_num++;zifu sa=Q.front();Q.pop();
				node[t].children.push_back(0);
				temp_d=biaodashi(dep+1,wid);
				node[t].children[stt]=temp_d;
				if(sa.name==";") break ;
				else if(sa.name=="{") {
					stt=Node_cnt++;node[t].children_num++;
					node[t].children.push_back(stt);
					Node tmp;node.push_back(tmp);
					node[stt].type="for_body";node[stt].content="";node[stt].id=stt;
					node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
					sa=Q.front();Q.pop();
					while(sa.name!="}") {
						ll sstt=node[stt].children_num++;
						node[stt].children.push_back(0);
						ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
						node[stt].children[sstt]=temp_d;
						sa=Q.front();Q.pop();
						/*cout<<node[stt].children[sstt]<<endl;
						cout<<sa.name<<endl;
						cout<<node[node[stt].children[sstt]].type<<endl;*/
					}
				}
				else {
					puts("ERROR");
				}
				break;
			}
			case 13: {//do
				node[t].type="do_while";
				node[t].content="";
				zifu sa=Q.front();Q.pop();
				while(sa.name!="{") sa=Q.front(),Q.pop();
				ll stt=Node_cnt++;node[t].children_num++;
				node[t].children.push_back(stt);
				Node tmp;node.push_back(tmp);
				node[stt].type="do_body";node[stt].content="";node[stt].id=stt;
				node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
				sa=Q.front();Q.pop();
				while(sa.name!="}") {
					ll sstt=node[stt].children_num++;
					node[stt].children.push_back(0);
					ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
					node[stt].children[sstt]=temp_d;
					sa=Q.front();Q.pop();
					/*cout<<node[stt].children[sstt]<<endl;
					cout<<sa.name<<endl;
					cout<<node[node[stt].children[sstt]].type<<endl;*/
				}
				sa=Q.front();Q.pop();
				while(sa.name!="(") {sa=Q.front();Q.pop();}
				while(!Q_s.empty()) Q_s.pop();
				sa=Q.front();Q.pop();
				while(sa.name!=")") {
					Q_s.push(sa);
					node[t].content+=sa.name+" ";
					sa=Q.front();Q.pop();
				}
				stt=node[t].children_num++;
				node[t].children.push_back(0);
				ll temp_d=condition(dep,wid);
				node[t].children[stt]=temp_d;
				sa=Q.front();Q.pop();
				break;
			}
			case 14: {//break
				node[t].type="break";
				node[t].content="";
				break;
			}
			case 15: {//continue
				node[t].type="continue";
				node[t].content="";
				break;
			}
			case 16: {//scanf
				node[t].type="输入";
				node[t].content="";
				zifu sa=Q.front();Q.pop();
				while(sa.name!="\"") {sa=Q.front();Q.pop();}
				sa=Q.front();Q.pop();
				while(sa.name!="\"") {
					node[t].content+=sa.name+" ";
					sa=Q.front();Q.pop();
				}
				/*scanf("%d\n",&a,&b);*/
				sa=Q.front();Q.pop();
				while(sa.name!=")") {
					if(sa.type=="BIAOSHIFU") {
						ll stt=Node_cnt++;node[t].children_num++;
						node[t].children.push_back(stt);
						Node tmp;node.push_back(tmp);
						node[stt].id=stt;node[stt].type="bianliang";
						node[stt].content=sa.name;
						node[stt].depth=dep+1;node[stt].width=wid+stt;
					}
					sa=Q.front();Q.pop();
				}
				sa=Q.front();Q.pop();
				break;
			} 
			case 17: {//printf
				node[t].type="输出";
				node[t].content="";
				zifu sa=Q.front();Q.pop();
				while(sa.name!="\"") {sa=Q.front();Q.pop();}
				sa=Q.front();Q.pop();
				while(sa.name!="\"") {
					node[t].content+=sa.name+" ";
					sa=Q.front();Q.pop();
				}
				/*scanf("%d\n",&a,&b);*/
				sa=Q.front();Q.pop();
				while(sa.name!=")") {
					if(sa.type=="BIAOSHIFU") {
						ll stt=Node_cnt++;node[t].children_num++;
						node[t].children.push_back(stt);
						Node tmp;node.push_back(tmp);
						node[stt].id=stt;node[stt].type="bianliang";
						node[stt].content=sa.name;
						node[stt].depth=dep+1;node[stt].width=wid+stt;
					}
					sa=Q.front();Q.pop();
				}
				sa=Q.front();Q.pop();
				break;
			}
			case 18: {//getchar
				node[t].type="输入char型";
				node[t].content="";
				zifu x=Q.front();Q.pop();
				x=Q.front();Q.pop();
				x=Q.front();Q.pop();
				break;
			}
		}
	}
	else if(a.type=="BIAOSHIFU") {
		node[t].type="BIAODASHI";
		node[t].content="";
		zifu x=a;
		while(x.name!=";") {
			node[t].content+=x.name+" ";
			x=Q.front();Q.pop();
		}
	}
	else {
		puts("ERROR");
	}
	return t;
}

void solve() {
	Node tmp;tmp.clear();
	while(!node.empty()) node.pop_back();
	ll t=Node_cnt++;node.push_back(tmp);
	node[t].id=t;node[t].depth=node[t].width=0;
	node[t].type=node[t].content="root";
	while(!Q.empty()) {
		Node p;
		ll st=node[t].children_num++;
		zifu a=Q.front();Q.pop();
		node[t].children.push_back(0);
		ll tempt=dfs(1,st,a);
		node[t].children[st]=tempt;
		/*writeln(node[t].children[st]);*/
		/*print(tempt);*/
	}
}

void print(ll x) {
	cout<<x<<":"<<endl;
	cout<<"id:"<<node[x].id<<endl;
	cout<<"type:"<<node[x].type<<endl;
	cout<<"content:"<<node[x].content<<endl;
	cout<<"children_num:"<<node[x].children_num<<endl;
	cout<<"children:"<<endl;
	for(re ll i=0;i<node[x].children_num;i++) {
		cout<<node[x].children[i]<<endl;
	}
}
void vis(ll x) {
	print(x);
	for(re ll i=0;i<node[x].children_num;i++) {
		vis(node[x].children[i]);
	}
}
FILE *fp=fopen("test.gv","w+");

void fpri(ll x) {
	/*a [label = "this is node a"];*/
	cout<<node[x].id<<"[shape = record , label = \""<<"{<head> "<<node[x].type<<" | "<<node[x].content<<"}\"];"<<endl;
//	fprintf(fp,"%d[label = \"{<head>%s | %s}\"];",node[x].id,node[x].type,node[x].content);
	for(re ll i=0;i<node[x].children_num;i++) fpri(node[x].children[i]);
}
void fpri2(ll x) {
	for(re ll i=0;i<node[x].children_num;i++) {
		cout<<x<<" -> "<<node[x].children[i]<<endl;
		fpri2(node[x].children[i]);
	}
}
void fprint() {
	freopen("test.gv","w+",stdout);
	cout<<"digraph graph1 {"<<endl;
	cout<<"node [fontname=\"FangSong\"];"<<endl;
	cout<<"graph [fontname=\"FangSong\"];"<<endl;
	cout<<"edge [fontname=\"FangSong\"];"<<endl;
	fpri(0);
	fpri2(0);
	cout<<"}"<<endl;
}
int main() {
  FR();
	get_Q();/*check_Q();*/
	solve();/*vis(0);*/
	fprint();
//  FC();
    return 0;
}
