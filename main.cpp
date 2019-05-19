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

   const int returnRj() {
        return rj;
    }

    int returnPj() {
        return pj;
    }

   const int returnQj() {
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
            time = time + it->returnPj();
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
int ShragePMTAlgorithm(vector<Job> tab,int *tabhelp1) {
    int time = 0;
    int Cmax = 0;
    int i=0;
    vector<Job> helptab,tab1;


    while (!helptab.empty() || !tab.empty()) {
        auto itw=tab.begin();
        while (!tab.empty() && itw->returnRj() <= time) {
            helptab.push_back(*itw);


            auto itw2=(itw+1);
            if(itw->returnQj() > (itw2)->returnQj())
            {
                (itw2)->pj=time-(itw->returnRj());
                time=itw->returnRj();

                if((itw2)->returnPj() >0)
                {
                    helptab.push_back(*itw2);
                }
            }

            tab.erase(tab.begin());
            itw=tab.begin();
        }

        if (helptab.empty()) {
            auto itpom=tab.begin();
            time = itpom->returnRj();

        } else {

            sort(helptab.begin(), helptab.end(),[] (const Job &a,const Job &b){return a.qj > b.qj;});
            auto it = helptab.begin();
            time = time + it->returnPj();
            Cmax=max(Cmax,time+it->returnQj());
            tabhelp1[i]=it->getnumberproces();
            i++;
            helptab.erase(helptab.begin());
        }


    }


    return Cmax;
}

int main() {
    Job object;
    vector<Job> tab;
    int nm, np, p1[100][100];
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

        tab.push_back(object);

    }


    sort(tab.begin(), tab.end(),[] (const Job &a,const Job &b){return a.rj < b.rj;});

    cout << "Wynik algorytmu to: " << ShrageAlgorithm(tab,tabhelp1) << endl;
    cout << "Wynik algorytmuPMTA to: " << ShragePMTAlgorithm(tab,tabhelp2) << endl;

    return 0;
}
