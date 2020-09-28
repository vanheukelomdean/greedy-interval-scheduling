#include<bits/stdc++.h>

using namespace std;

#include <vector>
#include <set>

struct Workshop {
    int start_time, duration, end_time;
};

struct Available_Workshops { 
    int n;
    vector<Workshop> workshop_list;
};


Available_Workshops* initialize (int start_time[], int duration[], int n) {
    int end_time;
    Available_Workshops* A = new Available_Workshops();

    A->n = n;

    for (int i = 0; i < n; ++i) {
        end_time = start_time[i] + duration[i];
        A->workshop_list.push_back(Workshop{start_time[i], duration[i], end_time});
    }
    return A;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    vector<Workshop>::iterator it, attending_it;
    int earliest_end, num_attending, att_start, att_end;

    num_attending = 0;

    while (ptr->n > 0)
    {
        // Initialise earliest ending workshop to first candidate
        attending_it = ptr->workshop_list.begin();
        earliest_end = attending_it->end_time;
        
        // Find minimum end
        for(int i = 0; i < ptr->n; ++i) {
            it = ptr->workshop_list.begin();
            advance(it, i);
            if (it->end_time < earliest_end) {
                attending_it = it;
                earliest_end = attending_it->end_time;
            }
        }

        ++ num_attending;

        // Cache intersection boundaries of earliest ending workshop of candidates
        att_start = attending_it->start_time;
        att_end = attending_it->end_time;

        ptr->workshop_list.erase(attending_it);
        ptr->n -= 1;

        if (ptr->n == 0)
            break;

        // Eliminate intersecting workshops from candidate set
        for(int i = 0; i < ptr->n; ++i) {
            it = ptr->workshop_list.begin();
            advance(it, i);
            if (it->start_time < att_end && 
                att_start < it->end_time) {
                    ptr->workshop_list.erase(it);
                    ptr->n -=  1;
                    --i;
            }
        }
    }
    return num_attending;
}

// Hackerrank testing template
int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}