#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
using namespace std;
bool scanned[100005];
int sign_up[100005];
int per_day[100005];
vector<int> books;
vector<priority_queue<pair<int,int>>> libs;
vector<pair<double,int>> rats;
int main(){
    freopen("d.txt","r",stdin);
    freopen("d_out.txt","w",stdout);
    IO;
    int bookno,libno,deadline;
    cin>>bookno>>libno>>deadline;
    books.resize(bookno);
    for(auto &x : books)cin>>x;
    libs.resize(libno);
    for(int i=0;i<libno;i++){
        int book_per_lib;
        cin>>book_per_lib>>sign_up[i]>>per_day[i];
        long long score=0;
        for(int j=0;j<book_per_lib;j++){
            int x;
            cin>>x;
            score+=books[x];
            libs[i].push({books[x],x});
        }
        double rat=0;
        rat=1.0*(score+per_day[i]);
        rat/=sign_up[i];
        rats.push_back({rat,i});
    }
    sort(rats.begin(),rats.end());
    reverse(rats.begin(),rats.end());
    int current_day=0;
    vector<pair<int,vector<int>>> sol;
    for(auto p : rats){
        int index=p.second;
        current_day+=sign_up[index];
        if(current_day>deadline)break;
        vector<int> taken_books;
        int books_to_be_taken=(deadline-current_day)*per_day[index];
        auto q= libs[index];
        while(q.size()&&books_to_be_taken){
            auto b = q.top();
            q.pop();
            if(!scanned[b.second]){
                scanned[b.second]=true;
                books_to_be_taken--;
                taken_books.push_back(b.second);
            }
        }
        if(taken_books.size())
        sol.push_back({index,taken_books});
        else current_day-=sign_up[index];
    }
    cout<<sol.size()<<"\n";
    for(auto p : sol){
        cout<<p.first<<" "<<p.second.size()<<"\n";
        for(auto x : p.second){
            cout<<x<<" ";
        }
        cout<<"\n";
    }
}
