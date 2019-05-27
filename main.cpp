#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;


class Job {
private:
    int numberofproces = 0;
    int numberofmachines = 0;

    int tp = 0; //Czas procesu (rj+pj)

public:
    int rj = 0; //Czas przygotowania
    int pj = 0; //Czas wykonania
    int qj = 0; //Czas dostarczen
    int Cq=0;
    /*Job(int R, int P, int Q)
    {
        this->R = R;
        this->P = P;
        this->Q = Q;
    }*/
    void saveParameters() {
        cout << "Podaj kolejno numerprocesu, maszyne, czas:przygotowania,wykonania,dostarczenia." << endl;
        cin >> numberofproces;
        cin >> numberofmachines;
        cin >> rj;
        cin >> pj;
        cin >> qj;
        tp = rj + pj;
    }

    void SaveRj(int i) {
        rj = i;

    }

    void SavePj(int k) {
        pj = k;
    }

    void SaveQj(int j) {
        qj = j;
    }

    int returnTimeofallprocess() {

        return tp;
    }

    void SaveNumberofProces(int i) {
        numberofproces = i;

    }

    void SaveNumberofMachines(int i) {
        numberofmachines = i;
    }

    int getnumberproces() {
        return numberofproces;
    }

    int returnRj() {
        return rj;
    }

    int returnPj() {
        return pj;
    }

    int returnQj() {
        return qj;
    }

    int getnumbermachine() {
        return numberofmachines;
    }

     bool operator<(const Job &first) const {
         return (rj < first.rj);
     }

    //friend void SortRj(vector<Job> tab);
    friend void SortQj(vector<Job> tab);

};
/*******Funkcje dla RPQ*******/
void SortRj(vector<Job> tab) {
    sort(tab.begin(),tab.end());
}

void SortQj(vector<Job> tab) {
    sort(tab.begin(), tab.end(),
         [](const Job& a, const Job& b) -> bool  {
             return a.qj < b.qj;
         });
}


int ShrageAlgorithm(vector<Job> &tab1) {
    int time = 0;
    int Cmax = 0;
    int number=0;
    int i=0;
    vector<Job>tab=tab1;
    vector<Job> permutation;
    vector<Job> helptab;

    while (!helptab.empty() || !tab.empty()) {
        auto itw=tab.begin();
        while (!tab.empty() && itw->returnRj() <= time) {
            helptab.push_back(*itw);
            tab.erase(tab.begin());
            itw=tab.begin();
        }
        if (helptab.empty()) {
            auto itpom=tab.begin();
            time =  itpom->returnRj();

        } else {

            sort(helptab.begin(), helptab.end(),[] (const Job &a,const Job &b){return a.qj > b.qj;});
            auto it = helptab.begin();
            time += it->returnPj();
            permutation.push_back(*it);
            permutation[permutation.size()-1].Cq=time + it->returnQj();
            Cmax=max(Cmax,time+it->returnQj());
//            tabhelp[i]=it->getnumberproces();
            helptab.erase(helptab.begin());
            i++;
        }


    }
   // cout<<"Time"<<time<<endl;
    tab1=permutation;

    return Cmax;
}

int Schrage_pmtn(vector<Job> tab)
{
    int Cmax = 0;
    std::vector<Job> ready;
    std::vector<Job> Permutation;
    std::vector<Job> current_job;
    std::vector<Job> temp_job;
    Job example;
    example.rj=0;
    example.qj=0;
    example.pj=0;
    current_job.push_back(example);
    temp_job.push_back(example);

    int t = 0;

    int temp = 0;
    int temp_order = 0;

    while (!ready.empty() || !tab.empty())
    {
        
        while (!tab.empty() && tab.front().returnRj() <= t)
        {

            ready.push_back(tab.front());
            temp_job.erase(temp_job.begin());
            temp_job.push_back(tab.front());
            tab.erase(tab.begin());

            if (temp_job.front().returnQj() > current_job.front().returnQj())
            {
                current_job.front().pj=(t - temp_job.front().returnRj());
                t = temp_job.front().returnRj();


                if (current_job.front().returnPj() > 0)
                    ready.push_back(current_job.front());
            }
        }

        if (ready.empty())
            t = tab.front().returnRj();
        else
        {
            if (ready.size() > 1)
            {
                for (int j = 0; j < ready.size(); j++)
                {
                    if (ready[j].returnQj() >= temp)
                    {
                        temp = ready[j].returnQj();
                        temp_order = j;
                    }
                }
            }

            Permutation.push_back(ready[temp_order]);	//add jobs to permutation
            current_job.erase(current_job.begin());
            current_job.push_back(ready[temp_order]);	//adding to current job

            ready.erase(ready.begin() + temp_order);

            t += Permutation.back().returnPj();
            Cmax = max(Cmax, t + Permutation.back().returnQj());

            temp = 0;
            temp_order = 0;
        }

    }

    return Cmax;
}

int find_max(int Cmax, int Q)
{
    return Cmax > Q ? Cmax : Q;
}
int find_max(int a, int b,int c)
{
    int max=a;
    if(b>max)
        max=b;
    if(c>max)
        max=c;
    return max;
}

int find_min(int a, int b){
    return a > b ? b : a;
}

int find_b(int np,int Cmax_Schrage, vector<Job> PI){
    int b=0;
    for(int i=np;i>0;i--){
        if(Cmax_Schrage==PI[i].Cq){
            b=i;
            break;
        }
    }
    return b;
}

int find_a(int b, vector<Job> PI,int Cmax_Schrage){

    int suma = 0;
    int a;
    for(a = 0; a < b; a++)
    {
        suma = 0;
        for (int i = a; i <= b; i++)
        {
            suma += PI[i].returnPj();
        }

        if (Cmax_Schrage == (PI[a].returnRj() + suma + PI[b].returnQj()))
        {
            return a;
        }

    }

    return a;
}

int find_c(int b, int a,  vector<Job> PI) {
    int c = - 1;

    for ( int i = b ; i >= a ; i-- ) {
        if (PI[i].returnQj() < PI[b].returnQj()) {
            c = i;
            break;
        }
    }

    return c;
}



int Carlier(vector<Job> tab, int np,int UB)
{
    int U,LB;
    int tabhelp1[np];
    U=ShrageAlgorithm(tab);

    if(U < UB){
        UB=U;
    }
    int b=find_b(np,U,tab);
    int a=find_a(b,tab,U);
    int c=find_c(b,a,tab);
  //  cout<<"B: "<<find_b(np,U,tab);
 //   cout<<"A: "<<find_a(b,tab,U);
 //   cout<<"C: "<<find_c(b,  a,  tab);
    if(c == -1)
    {
        return UB;
    }

    int rPrim=0;
    int pPrim=0;
    int qPrim=0;

    for(int i=c+1; i<=b; i++){
        rPrim=tab[i].returnRj();
        pPrim+=tab[i].returnPj();
        qPrim=tab[i].returnQj();

    }
    int hPrim=0;
    hPrim=rPrim + pPrim + qPrim;
   // cout<<"r': "<<rPrim<<" ";
  //  cout<<"p': "<<pPrim<<" ";
   // cout<<"q': "<<qPrim<<" ";
   // cout<<"h': "<<hPrim<<endl<<endl;

    int rememberR=tab[c].returnRj();
    int whereR=c;
    tab[c].SaveRj(find_max(tab[c].returnRj() , rPrim + pPrim));

    LB = Schrage_pmtn(tab);
    LB = find_max(hPrim,LB);


    if(LB < UB){
        UB=Carlier(tab,np,UB);
    }

    for (int i = 0; i < np; i++)
    {
        if(whereR == tab[i].getnumberproces()){
            tab[i].SaveRj(rememberR);
            break;
        }

    }
    int rememberQ=tab[c].returnQj();
    int whereQ=c;
    tab[c].SaveQj(find_max(tab[c].returnQj() , qPrim + pPrim));

    LB = Schrage_pmtn(tab);
    LB = find_min(hPrim,LB);

    if(LB < UB) {
        UB=Carlier(tab,np,LB);
    }
    for (int i = 0; i < np; i++)
    {
        if(whereQ == tab[i].getnumberproces()){
            tab[i].SaveQj(rememberQ);
            break;
        }

    }

    U=LB;
    return U;
}


int main() {
    Job object;
    vector<Job> tab;
    int nm, np, p1[500][500];
    ifstream data("data.txt");
    data >> np >> nm;
    int tabhelp1[np];
    int tabhelp2[np];


    for (int i = 1; i < np + 1; i++) {
        for (int j = 1; j < nm + 1; j++) {
            data >> p1[j][i];
        }
    }

    data.close();
    for (int i = 1; i < np + 1; i++) {
        int j = 1;
        object.SaveNumberofProces(i);
        object.SaveNumberofMachines(i);
        object.SaveRj(p1[j][i]);
        object.SavePj(p1[j + 1][i]);
        object.SaveQj(p1[j + 2][i]);
     //   cout<<p1[j][i];
        tab.push_back(object);

    }

   /* for(int i=0;i<np;i++)
    {
        cout<<tabhelp1[i]<<" ";
    }
    */
    sort(tab.begin(), tab.end(),[] (const Job &a,const Job &b){return a.rj < b.rj;});

   // cout << "Wynik algorytmu to: " << ShrageAlgorithm(tab) << endl;
   // cout << "Wynik algorytmuPMTA to: " << ShragePMTAlgorithm(tab,tabhelp2) << endl;
   // cout << "Wynik algorytmuPMTA to: " << Schrage_pmtn(tab) << endl;
    int UB=9999;
    cout<<"Wynik Carliera to: " <<Carlier(tab,  np,UB)<<endl;
    return 0;
}
