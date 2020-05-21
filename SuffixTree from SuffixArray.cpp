//todo - improve code and indent
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+500;
    

vector<int> sortchar(const string& text,vector<int> &order){    
    int cnt[30]={0},i;
    
    for(i=0;i<text.size();i++){
        if(text[i]=='$')
            cnt[0]++;
        else
        cnt[text[i]-'A'+1]++;
    }
    for(i=1;i<28;i++){
        cnt[i]+=cnt[i-1];
    }
    for(i=text.length()-1;i>=0;i--){
        int k;
        if(text[i]=='$')
            k=0;
        else
            k=text[i]-'A'+1;
        
        cnt[k]--;
        order[cnt[k]]=i;

    }
    return order;
}
vector<int> computeclass(const string& text,vector<int> &order,vector<int> &cls){
    
    cls[order[0]]=0;
    for(int i=1;i<order.size();i++){
        if(text[order[i]] != text[order[i-1]]){
            cls[order[i]] = cls[order[i-1]] + 1;
        }
        else{
            cls[order[i]] = cls[order[i-1]];
        }
    }
    return cls;
}
vector<int>  updateorder(const string& text,vector<int> &order,int l,vector<int> &cls){
    vector<int> cnt(text.size(),0);
    int i,j;
    vector<int> neworder(text.size());
    for(i=0;i<text.size();i++){
        cnt[cls[i]]=cnt[cls[i]]+1;
    }
    for(i=1;i<text.size();i++){
        cnt[i]+=cnt[i-1];
    }
    for(i=text.length()-1;i>=0;i--){
        int start=order[i]+text.size()-l;
        start=(start)%(text.size());
        int cl=cls[start];
        cnt[cl]=cnt[cl]-1;
        neworder[cnt[cl]]=start;
    }
    return neworder;
}
vector<int> updateclass(vector<int> &neworder,vector<int> &cls,int l){
    int n=neworder.size();
    vector<int> newclass(n);
    newclass[neworder[0]]=0;
    for(int i=1;i<n;i++){
        int cur=neworder[i];
        int prev=neworder[i-1];
        int mid=(cur+l)%n;
        int midprev=(prev+l)%n;
        if(cls[cur]!=cls[prev] || cls[mid]!=cls[midprev]){
            newclass[cur]=newclass[prev]+1;
        }
        else{
            newclass[cur]=newclass[prev];
        }

    }
    return newclass;
}
vector<int> BuildSuffixArray(const string& text) {
    int i,j,k,n=text.length();
    vector<int> order(text.size());
    sortchar(text,order);
    vector<int> cls(text.size());
    computeclass(text,order,cls);
    int len=1;
    while(len<n){
        //for(i=0;i<order.size();i++) cout<<order[i]<<' ';
        //for(i=0;i<cls.size();i++) cout<<cls[i]<<' ';
        order=updateorder(text,order,len,cls);
        cls=updateclass(order,cls,len);
        len=len*2;
        //cout<<endl;
    }
    return order;
}
vector<int> invertSA(vector<int>& order){
    vector<int> pos(order.size());
    for(int i=0;i<order.size();i++)
        pos[order[i]]=i;
    return pos;
}
int LCPofsuffixes(const string& s,int i,int j,int equal){
    int lcp=max(0,equal);
    while(i+lcp<s.size() && j+lcp<s.size()){
        if(s[i+lcp] == s[j+lcp])
            lcp++;
        else
            break;
    }
    return lcp;
}
vector<int> ComputeLCP(const string& s, vector<int>& order){
    vector<int> lcp_array(s.size()-1);
    int lcp=0;
    vector<int> posInorder=invertSA(order);
    int suffix=order[0];
    for(int i=0;i<s.size();i++){
        int orderindex=posInorder[suffix];
        if(orderindex == s.size()-1){
            lcp=0;
            suffix = (suffix+1)%((int)s.size());
            continue;
        }
        int nextsuffix=order[orderindex+1];
        lcp=LCPofsuffixes(s,suffix,nextsuffix,lcp-1);
        lcp_array[orderindex]=lcp;
        suffix++;
        suffix%=((int)s.size());
        
    }
    return lcp_array;
}
class node{
    public:
        node* parent;
        map<char,node*> children;
        int edgestart;
        int edgeend;
        int depth;
        node(node* par,int st,int end,int suffix){
            children.clear();
            parent=par;
            edgestart=st;
            edgeend=end;
            depth=suffix;
        }
};
node* newLeaf(node* n, const string& s, int suffix){
    node* leaf = new node(n,suffix+n->depth,s.size()-1,s.size()-suffix);
    n->children[s[leaf->edgestart]]=leaf;
    return leaf;
}
node* breakedge(node* n,const string& s,int start,int offset){
    int startchar=s[start];
    int midchar=s[start+offset];
    node* midNode=new node(n,start,start+offset-1,n->depth+offset);
    midNode->children[midchar]=n->children[startchar];
    n->children[startchar]->parent=midNode;
    n->children[startchar]->edgestart+=offset;
    n->children[startchar]=midNode;
    return midNode;
}
node* STfromSA(const string& s, vector<int>& order,vector<int>& lcp){
    node* root = new node(NULL,-1,-1,0);
    int lcpprev=0;
    node* curNode=root;
    for(int i=0;i<s.size();i++){
        int suffix=order[i];
        while(curNode->depth > lcpprev){
            curNode=curNode->parent;
        }
        if(curNode->depth == lcpprev)
            curNode=newLeaf(curNode,s,suffix);
        else{
            //int edgestart=curNode->children[s[edgestart]]->edgestart;
            int edgestart=order[i-1]+curNode->depth;
            int offset=lcpprev-curNode->depth;
            node* midNode=breakedge(curNode,s,edgestart,offset);
            curNode = newLeaf(midNode,s,suffix);
            
            
        }
        if(i<s.size()-1){
            lcpprev=lcp[i];
        }
    }
    return root;
}
int ans;
void dfs(node* root){
    ans+=root->edgeend-root->edgestart;
    cout<<root->edgestart<<' '<<root->edgeend<<endl;
            
    for(auto it:root->children){
        dfs(it.second);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    string s;
    cin>>s;
    vector<int> suffix_array = BuildSuffixArray(s);
    vector<int> lcp=ComputeLCP(s,suffix_array);
    node* root = STfromSA(s,suffix_array,lcp);
    dfs(root);
    cout<<ans;
}
