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

struct AST {
	ll Node_cnt;
	vector<Node>node;
	queue<zifu>Q_s;//处理内容 
	string gc= "getchar"; 
	ll biaodashi(ll dep,ll wid) {
		ll t=Node_cnt++;Node n_x;
		n_x.id=t;n_x.depth=dep;n_x.width=wid;
		node.push_back(n_x);
		node[t].type="BIAODASHI";
		queue<zifu>Q_w;while(!Q_w.empty()) Q_w.pop();
		while(!Q_s.empty()) {
			zifu x=Q_s.front();Q_s.pop();
			Q_w.push(x);
			node[t].content+=x.name+" ";
		}
		string::size_type idx;
		idx=node[t].content.find(gc);
		if(idx != string::npos) {
			node[t].type="输入char型";
			while(!Q_w.empty()) {
				zifu x=Q_w.front();Q_w.pop();
				if(x.type!="BIAOSHIFU") continue ;
				ll st=Node_cnt++;node[t].children_num++;
				node[t].children.push_back(st);
				n_x.id=st;n_x.depth=dep+1;n_x.width=wid;
				node.push_back(n_x);
				node[st].type="bianliang";
				node[st].content=x.name;
			}
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
					node[t].type="if";
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
					
					if(sa.name=="{") {
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
					sa=Q.front();
					if(sa.name == "else") {
						Q.pop();sa=Q.front();
						if(sa.name=="if") {
							Q.pop();
							ll stt=Node_cnt++;node[t].children_num++;
							node[t].children.push_back(stt);
							Node tmp;node.push_back(tmp);
							node[stt].type="else_body";node[stt].content="";node[stt].id=stt;
							node[stt].depth=node[t].depth+1;node[stt].width=node[t].width+stt;
							//stt:else_if_body节点 
							ll sstt=node[stt].children_num++;
							ll temp_d=dfs(node[stt].depth+1,node[stt].width+sstt,sa);
							node[stt].children.push_back(temp_d);
							node[stt].children[sstt]=temp_d;
						}
						
						else if(sa.name=="{") {
							Q.pop();
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
				case 9: {//else
					puts("ERROR");
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
						node[stt].type="while_body";node[stt].content="";node[stt].id=stt;
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
					zifu x=Q.front();Q.pop();
					break;
				}
				case 15: {//continue
					node[t].type="continue";
					node[t].content="";
					zifu x=Q.front();Q.pop();
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
			queue<zifu>Q_w;while(!Q_w.empty()) Q_w.pop();
			while(x.name!=";") {
				node[t].content+=x.name+" ";
				Q_w.push(x);
				x=Q.front();Q.pop();
			}
			string::size_type idx;
			idx=node[t].content.find(gc);
			if(idx != string::npos) {
				node[t].type="输入char型";
				while(!Q_w.empty()) {
					x=Q_w.front();Q_w.pop();
					if(x.type!="BIAOSHIFU") continue ;
					ll st=Node_cnt++;node[t].children_num++;
					node[t].children.push_back(st);
					n_x.id=st;n_x.depth=dep+1;n_x.width=wid;
					node.push_back(n_x);
					node[st].type="bianliang";
					node[st].content=x.name;
				}
			}
		}
		else {
			puts("ERROR");
		}
		return t;
	}

	void build_ast() {
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
	void fpri(ll x) {
		/*a [label = "this is node a"];*/
		cout<<node[x].id<<"[shape=";
		if(node[x].type=="con_dition")cout<<"diamond";
		else if(node[x].type=="输入"||node[x].type=="输出"||node[x].type=="输入char型") cout<<"parallelogram";
		else cout<<"box";
		cout<<" , label = \""<<"{ "<<node[x].type<<" | "<<node[x].content<<"}\"];"<<endl;
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
}ast;

struct testchart {
	map<string,ll>h_m,d_m;
	map<ll,ll>out_h;
	map<ll,bool>tag;
	bool check(ll x) {
//		map<ll,bool>::iterator it;
//		it=tag.find(x);
//		if(it==tag.end()) return false ;
//		return (*it).second ;
		return false ;
	}
	bool find(string x,string y) {
		string::size_type idx;
		idx=x.find(y);
		return idx != string::npos;
	}
	ll h_find(string x) {
		map<string,ll>::iterator it;
		for(it=h_m.begin();it!=h_m.end();it++) {
			if(find(x,(*it).first)) return (*it).second ;
		}
		return -1 ;
	}
	ll d_find(string x) {
		map<string,ll>::iterator it;
		for(it=d_m.begin();it!=d_m.end();it++) {
			if(find(x,(*it).first)) return (*it).second ;
		}
		return -1 ;
	}
	ll Node_cnt;
	/*a [label = "this is node a"];*/
	ll dfs(ll x,ll fro,ll c_n,ll b_n,ll g_n,ll swi) {//上一个节点是fro,进入一个x号body,返回body的最后一个节点 
		ll fx=fro;//continue和break跳转节点,程序终止节点,与上一个点的连边状态 
		ll end_=Node_cnt++;// 函数/if/循环终点节点
		cout<<end_<<"[label = \" ";
		cout<<"end";
		if(ast.node[x].type=="function_body") cout<<"_func";
		else if(ast.node[x].type=="if_body") cout<<"_if_body";
		else if(ast.node[x].type=="if") cout<<"_else_if";
		else if(ast.node[x].type=="else_body") cout<<"_else_body";
		else if(ast.node[x].type=="for_body") cout<<"_for_body";
		else if(ast.node[x].type=="do_body") cout<<"_do_body";
		else if(ast.node[x].type=="while_body") cout<<"_while_body";
		cout<<" \"];"<<endl; 
		Node sx=ast.node[x];
		if(sx.type=="function_body") g_n=end_;
		for(re ll i=0;i<sx.children_num;i++) {
			ll t=sx.children[i];Node n_t=ast.node[t];
			if(n_t.type=="if") {
				ll end_if=Node_cnt++;
				cout<<end_if<<"[shape = box , label = \" end_if \" ];"<<endl;
				if(!check(fx)) {cout<<fx<<" -> "<<t;}
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;fx=t;
				cout<<t<<"[shape = diamond , label = \" ";
				ll chc1,chc2;
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="con_dition") {
						cout<<n_jt.content;
						chc1=h_find(n_jt.content);
						chc2=d_find(n_jt.content);
						break ;
					}
				}
				cout<<" \"];"<<endl;
				if(chc1!=-1) {
					cout<<fx<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<fx<<endl;
				}
				if(chc2!=-1) {
					cout<<fx<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<fx<<endl;
				}
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="if_body") {
						ll temp_d=dfs(n_t.children[j],fx,c_n,b_n,g_n,1);
						if(!check(temp_d)) cout<<temp_d<<" -> "<<end_if<<endl;
					}
				}
				
				bool if_else=false; 
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="else_body") {
						ll temp_d=dfs(n_t.children[j],fx,c_n,b_n,g_n,-1);
						if(!check(temp_d)) cout<<temp_d<<" -> "<<end_if<<endl;
						if_else=true ;
					}
				}
				if(!if_else) {
					if(!check(fx)) cout<<fx<<" -> "<<end_if<<"[label = \" False \"];"<<endl;
				}
				fx=end_if;
			}
			
			else if(n_t.type=="create_bianliang"){
				if(!check(fx)) cout<<fx<<" -> "<<t;fx=t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;
				cout<<t<<"[shape = box , label = \"创建";
				cout<<n_t.content<<"型局部变量： ";
				cout<<ast.node[n_t.children[0]].content;
				for(re ll i=1;i<n_t.children_num;i++) {
					cout<<","<<ast.node[n_t.children[i]].content;
				}
				cout<<" \"];"<<endl; 
			}
			else if(n_t.type=="return") {
				if(!check(fx)) cout<<fx<<" -> "<<g_n;
				cout<<"[label = \" ";
				if(swi==1) {cout<<" True ,";swi=0;}
				else if(swi==-1) {cout<<" False ,";swi=0;}
				cout<<"返回 ";
				cout<<n_t.content;
				cout<<" \"];"<<endl; 
				tag.insert(mp(fx,1));
			} 
			else if(n_t.type=="continue") {
				if(!check(fx)) cout<<fx<<" -> "<<c_n;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;
				tag.insert(mp(fx,1));
			}
			else if(n_t.type=="break") {
				if(!check(fx)) cout<<fx<<" -> "<<b_n;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;
				tag.insert(mp(fx,1));
			}
			else if(n_t.type=="输入") {
				if(!check(fx)) cout<<fx<<" -> "<<t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;fx=t;
				cout<<t<<"[shape = parallelogram , label = \" 输入：";
				cout<<ast.node[n_t.children[0]].content;
				for(re ll i=1;i<n_t.children_num;i++) {
					cout<<","<<ast.node[n_t.children[i]].content;
				}
				cout<<" \"];"<<endl;
			}
			else if(n_t.type=="输出") {
				if(!check(fx)) cout<<fx<<" -> "<<t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;fx=t;
				cout<<t<<"[shape = parallelogram , label = \" 输出：";
				queue<ll>Ch1,Ch2;ll chc1,chc2;
				while(!Ch1.empty()) Ch1.pop();
				while(!Ch2.empty()) Ch2.pop();
				cout<<n_t.content<<":";
				if(n_t.children_num) {
					cout<<ast.node[n_t.children[0]].content;
					chc1=h_find(ast.node[n_t.children[0]].content);
					if(chc1!=-1) Ch1.push(chc1);
					chc2=d_find(ast.node[n_t.children[0]].content);
					if(chc2!=-1) Ch2.push(chc2);	
				}
				for(re ll i=1;i<n_t.children_num;i++) {
					cout<<","<<ast.node[n_t.children[i]].content;
					chc1=h_find(ast.node[n_t.children[i]].content);
					if(chc1!=-1) Ch1.push(chc1);
					chc2=d_find(ast.node[n_t.children[i]].content);
					if(chc2!=-1) Ch2.push(chc2);
				}
				cout<<" \"];"<<endl;
				while(!Ch1.empty()) {
					cout<<fx<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<fx<<endl;
				}
				while(!Ch2.empty()) {
					cout<<fx<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<fx<<endl;
				}
			}
			else if(n_t.type=="输入char型") {
				if(!check(fx)) cout<<fx<<" -> "<<t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;fx=t;
				cout<<t<<"[shape = parallelogram , label = \" 输入char型：";
				for(re ll i=0;i<n_t.children_num;i++) {
					cout<<ast.node[n_t.children[i]].content;
				}
				cout<<" \"];"<<endl;
			}
			else if(n_t.type=="BIAODASHI") {
				if(!check(fx)) cout<<fx<<" -> "<<t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;fx=t;
				cout<<t<<"[shape = box , label = \" ";
				cout<<n_t.content;
				cout<<" \"];"<<endl;
				ll chc1=h_find(n_t.content);
				ll chc2=d_find(n_t.content);
				if(chc1!=-1) {
					cout<<fx<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<fx<<endl;
				}
				if(chc2!=-1) {
					cout<<fx<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<fx<<endl;
				}
			}
			
			/*a [label = "this is node a"];*/
			else if(n_t.type=="for") {
				ll end_for=Node_cnt++;
				cout<<end_for<<"[shape = box , label = \" end_for \"];"<<endl;
				cout<<t<<"[shape = box , label = \"初始条件：";
				cout<<n_t.content; 
				cout<<" \"];"<<endl;
				if(!check(fx)) cout<<fx<<" -> "<<t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;fx=t;
				t=Node_cnt++;
				if(!check(fx)) cout<<fx<<" -> "<<t;
				cout<<endl;fx=t;
				cout<<t<<"[shape = diamond , label = \" ";
				ll chc1,chc2;
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="con_dition") {
						cout<<n_jt.content;
						chc1=h_find(n_jt.content);
						chc2=d_find(n_jt.content);
						break ;
					}
				}
				cout<<" \"];"<<endl;
				if(chc1!=-1) {
					cout<<fx<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<fx<<endl;
				}
				if(chc2!=-1) {
					cout<<fx<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<fx<<endl;
				}
				if(!check(t)) cout<<t<<" -> "<<end_for<<"[label = \" False \"];"<<endl;
				ll ct=Node_cnt++;c_n=ct;b_n=end_for;
				cout<<ct<<"[shape = box , label = \" ";
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="BIAODASHI") {
						cout<<n_jt.content;
						chc1=h_find(n_jt.content);
						chc2=d_find(n_jt.content);
						break ;
					}
				}
				cout<<" \"];"<<endl;
				if(chc1!=-1) {
					cout<<ct<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<ct<<endl;
				}
				if(chc2!=-1) {
					cout<<ct<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<ct<<endl;
				}
				if(!check(ct)) cout<<ct<<" -> "<<t<<endl;
				
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="for_body") {
						ll temp_d=dfs(n_t.children[j],fx,c_n,b_n,g_n,1);
						if(!check(temp_d)) cout<<temp_d<<" -> "<<ct<<endl;
						break ;
					}
				}
				fx=end_for;
			}
			
			else if(n_t.type=="do_while") {
				ll end_do=Node_cnt++;
				ll start_do=Node_cnt++;
				cout<<start_do<<"[shape = box , label = \" start_do \"];"<<endl;
				cout<<fx<<" -> "<<start_do;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;
				fx=start_do;
				cout<<end_do<<"[shape = box , label = \" end_do \"];"<<endl;
				cout<<t<<"[shape = diamond , label = \" ";
				ll chc1,chc2;
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="con_dition") {
						cout<<n_jt.content;
						chc1=h_find(n_jt.content);
						chc2=d_find(n_jt.content);
						break ;
					}
				}
				cout<<" \"];"<<endl;
				if(chc1!=-1) {
					cout<<t<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<t<<endl;
				}
				if(chc2!=-1) {
					cout<<t<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<t<<endl;
				}
				c_n=t;b_n=end_do;
				
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="do_body") {
						ll temp_d=dfs(n_t.children[j],fx,c_n,b_n,g_n,0);
						if(!check(temp_d)) cout<<temp_d<<" -> "<<t<<endl;
						break ;
					}
				}
				cout<<t<<" -> "<<start_do<<"[label = \" True \"];"<<endl;
				cout<<t<<" -> "<<end_do<<"[label = \" False \"];"<<endl;
				fx=end_do;
				
			}
			else if(n_t.type=="while") {
				
				ll end_while=Node_cnt++;
				cout<<end_while<<"[shape = box , label = \" end_while \"];"<<endl;
				cout<<t<<"[shape = diamond , label = \" ";
				ll chc1,chc2;
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="con_dition") {
						cout<<n_jt.content;
						chc1=h_find(n_jt.content);
						chc2=d_find(n_jt.content);
						break ;
					}
				}
				cout<<" \"];"<<endl;
				if(chc1!=-1) {
					cout<<t<<" -> "<<chc1<<endl;
					cout<<out_h[chc1]<<" -> "<<t<<endl;
				}
				if(chc2!=-1) {
					cout<<t<<" -> "<<chc2<<endl;
					cout<<chc2<<" -> "<<t<<endl;
				}
				c_n=t;b_n=end_while;
				cout<<fx<<" -> "<<t;fx=t;
				if(swi==1) {cout<<"[label = \" True \"];";swi=0;}
				else if(swi==-1) {cout<<"[label = \" False \"];";swi=0;}
				cout<<endl;
				for(re ll j=0;j<n_t.children_num;j++) {
					ll jt=n_t.children[j];Node n_jt=ast.node[jt];
					if(n_jt.type=="while_body") {
						ll temp_d=dfs(n_t.children[j],fx,c_n,b_n,g_n,1);
						if(!check(temp_d)) cout<<temp_d<<" -> "<<t<<endl;
						break ;
					}
				}
				cout<<t<<" -> "<<end_while<<"[label = \" False \"];"<<endl;
				fx=end_while;
				
				
				
				
				
				
				
			}
			else {
				puts("ERROR");
			}
		}
		if(!check(fx)) cout<<fx<<" -> "<<end_<<endl;
		return end_;
	}
	void create_hanshu(Node f_x) {
		ll x=f_x.children[0];
		string arr=f_x.content;
		string ar=ast.node[x].content;
		Node sx=ast.node[x];
		cout<<sx.id<<"[shape = box , label = \" 创建形参：";
		ll ts;
		if(ast.node[sx.children[0]].type!="function_body") {
			cout<<ast.node[sx.children[0]].content;
		}else ts=0;
		for(re ll i=1;i<sx.children_num;i++) {
			if(ast.node[sx.children[i]].type!="function_body") {
				cout<<","<<ast.node[sx.children[i]].content;
			}else ts=i;
		}
		cout<<"; \"];"<<endl;
		ll temp_d=dfs(sx.children[ts],sx.id,-1,-1,-1,0);
		h_m.insert(mp(ar,sx.id));
		out_h.insert(mp(sx.id,temp_d));
	}
	void build_testchart() {
		/*a [label = "this is node a"];*/
			freopen("test.gv","w+",stdout);
			cout<<"digraph graph1 {"<<endl;
			cout<<"node [fontname=\"FangSong\"];"<<endl;
			cout<<"graph [fontname=\"FangSong\"];"<<endl;
			cout<<"edge [fontname=\"FangSong\"];"<<endl;
			ll rt=0;Node_cnt=ast.Node_cnt;
			cout<<rt<<"[shape = hexagon , label = \" 开始 \"];";
			for(re ll i=0;i<ast.node[0].children_num;i++) {
				ll x=ast.node[0].children[i];
				Node sx=ast.node[x];
				if(sx.type=="include") continue ;
				else if(sx.type=="define") {
					cout<<sx.id<<"[shape = box , label= \" ";
					cout<<"define:"<<sx.content<<" \" ];"<<endl;
					string arr;arr.clear();
					for(re ll i=0;sx.content[i]!=' ';i++) {arr+=sx.content[i];}
					d_m.insert(mp(arr,sx.id));
				}
				else if(sx.type=="create_bianliang") {
					cout<<sx.id<<"[shape = box , label= \" ";
					cout<<"创建"<<sx.content<<"型全局变量：";
					cout<<ast.node[sx.children[0]].content;
					for(re ll i=1;i<sx.children_num;i++) {
						cout<<","<<ast.node[sx.children[i]].content;
					}
					cout<<" \" ];"<<endl;
					cout<<rt<<" -> "<<sx.id<<endl;
					rt=sx.id;
				}
				else if(sx.type=="create_hanshu") {
					if(ast.node[sx.children[0]].content!="main") {create_hanshu(sx);}
					else {
						x=sx.children[0];
						for(re ll i=0;i<ast.node[x].children_num;i++) {
							if(ast.node[ast.node[x].children[i]].type=="function_body") {
								x=ast.node[x].children[i];break ;
							}
						}
						ll temp_d=dfs(x,rt,-1,-1,-1,0);
						cout<<"z"<<"[shape = hexagon , label = \" end \"];";
						cout<<temp_d<<" -> "<<"z"<<endl;
					}
				}
				else {
					system("pause");
					puts("ERROR");
				}
			}
			cout<<"}"<<endl;
	}
}chart;

int main() {
  FR();
	get_Q();
//	check_Q();
	ast.build_ast();
//	ast.vis(0);
//	ast.fprint();
	chart.build_testchart();
//  FC();
    return 0;
}
