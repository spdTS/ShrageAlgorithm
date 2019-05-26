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


int ShrageAlgorithm(vector<Job> tab,int *tabhelp) {
    int time = 0;
    int Cmax = 0;
    int number=0;
    int i=0;
    vector<Job> helptab,tab1;
    vector<Job> ro;

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
            ro.push_back(*it);

           Cmax=max(Cmax,time+it->returnQj());
           tabhelp[i]=it->getnumberproces();
            helptab.erase(helptab.begin());
            i++;
        }


    }
   // cout<<"Time"<<time<<endl;
    auto itpom2=ro.begin();
    sort(ro.begin(), ro.end(),[] (const Job &a,const Job &b){return a.qj > b.qj;});

    return Cmax;
}



int Schrage_pmtn(vector<Job> tab,int *tabhelp1)
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
   // carus.Cmax_Schrage_pmtn=Cmax;
    //cout << "\nCmax z przerwaniami: " << Cmax << std::endl;
    return Cmax;
}
/*
int bMax(vector<Job> tab,int Cmax){
    for(int i=0;i<tab.size()-1;i++)
    {
        if(tab[i] == Cmax && )
    }
}*/
int Carlier(vector<Job> tab, int *tabhelp, int np)
{
    int U,UB,LB;
    int tabhelp1[np];
    U=ShrageAlgorithm(tab,tabhelp);

    if(U < UB){
        UB=U;
        tabhelp=tabhelp1;
    }


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

    cout << "Wynik algorytmu to: " << ShrageAlgorithm(tab,tabhelp1) << endl;
    cout << "Wynik algorytmuPMTA to: " << Schrage_pmtn(tab,tabhelp2) << endl;

    return 0;
}
